// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#ifndef DYNO_STORAGE_HPP
#define DYNO_STORAGE_HPP

#include <dyno/builtin.hpp>
#include <dyno/detail/dsl.hpp>

#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <memory>
#include <type_traits>
#include <utility>


namespace dyno {

// concept PolymorphicStorage
//
// The PolymorphicStorage concept represents storage that can be used to store
// an object of an arbitrary type. In a sense, it is like a special-purpose
// allocator that could only ever allocate a single object.
//
// The nice thing about these PolymorphicStorage classes is that they have a
// single type and their ABI does not change even when the type of what they
// hold changes. However, they provide this functionality at the cost of
// "forgetting" the type information of what they hold, which is why they
// must be passed a vtable to perform most operations.
//
// A type `Storage` satisfying the `PolymorphicStorage` concept must provide
// the following functions as part of its interface:
//
// template <typename T> explicit Storage(T&&);
//  Semantics: Construct an object of type `std::decay_t<T>` in the polymorphic
//             storage, forward the argument to the constructor of the object
//             being created. A particular `Storage` class is not expected to
//             support being constructed from any such `T`; for example, `T`
//             could be too large to fit in a predefined buffer size, in which
//             case this call would not compile.
//
// template <typename VTable> Storage(Storage const&, VTable const&);
//  Semantics: Copy-construct the contents of the polymorphic storage,
//             assuming the contents of the source storage can be
//             manipulated using the provided vtable.
//
// template <typename VTable> Storage(Storage&&, VTable const&);
//  Semantics: Move-construct the contents of the polymorphic storage,
//             assuming the contents of the source storage can be
//             manipulated using the provided vtable.
//
// template <typename MyVTable, typename OtherVTable>
// void swap(MyVTable const&, Storage&, OtherVTable const&);
//  Semantics: Swap the contents of the two polymorphic storages, assuming
//             `*this` can be manipulated using `MyVTable` and the other
//             storage can be manipulated using `OtherVTable`.
//
// template <typename VTable> void destruct(VTable const&);
//  Semantics: Destruct the object held inside the polymorphic storage, assuming
//             that object can be manipulated using the provided vtable. This
//             must also free any resource required for storing the object.
//             However, this is not the same as destructing the polymorphic
//             storage itself (the wrapper), for which the destructor must
//             still be called.
//
//             WARNING: Since this is not using the usual destructor mechanism,
//             it is of utmost importance that users of these storage classes
//             call the `destruct` method explicitly in their destructor.
//             Furthermore, it should be noted that if an exception is thrown
//             in the constructor of a class (say `any_iterator`) using a
//             storage class defined here, the cleanup will NOT be done
//             automatically because the destructor of `any_iterator` will
//             not be called.
//
// template <typename T = void> T* get();
//  Semantics: Return a pointer of type `T` to the object inside the polymorphic
//             storage. If `T` is not the actual type of the object stored
//             inside the polymorphic storage, the behavior is undefined.
//
// template <typename T = void> T const* get() const;
//  Semantics: Return a pointer of type `T` to the object inside the polymorphic
//             storage. If `T` is not the actual type of the object stored
//             inside the polymorphic storage, the behavior is undefined.
//
// static constexpr bool can_store(dyno::storage_info);
//  Semantics: Return whether the polymorphic storage can store an object with
//             the specified type information.

// Class implementing the small buffer optimization (SBO).
//
// This class represents a value of an unknown type that is stored either on
// the heap, or on the stack if it fits in the specific small buffer size.
//
// TODO: - Consider having ptr_ always point to either sb_ or the heap.
//       - Alternatively, if we had a way to access the vtable here, we could
//         retrieve the size of the type from it and get rid of `uses_heap_`.
//       - We could also use the low bits of the pointer to the vtable for
//         `uses_heap_`.
template <std::size_t Size, std::size_t Align = -1u>
class sbo_storage {
  static constexpr std::size_t SBSize = Size < sizeof(void*) ? sizeof(void*) : Size;
  static constexpr std::size_t SBAlign = Align == -1u ? alignof(std::aligned_storage_t<SBSize>) : Align;
  using SBStorage = std::aligned_storage_t<SBSize, SBAlign>;

  union {
    void* ptr_;
    SBStorage sb_;
  };
  // TODO: It might be possible to pack this bool inside the union somehow.
  bool uses_heap_;

public:
  sbo_storage() = delete;
  sbo_storage(sbo_storage const&) = delete;
  sbo_storage(sbo_storage&&) = delete;
  sbo_storage& operator=(sbo_storage&&) = delete;
  sbo_storage& operator=(sbo_storage const&) = delete;

  static constexpr bool can_store(dyno::storage_info info) {
    return info.size <= sizeof(SBStorage) && alignof(SBStorage) % info.alignment == 0;
  }

  template <typename T, typename RawT = std::decay_t<T>>
  explicit sbo_storage(T&& t) {
    // TODO: We could also construct the object at an aligned address within
    // the buffer, which would require computing the right address everytime
    // we access the buffer as a T, but would allow more Ts to fit in the SBO.
    if constexpr (can_store(dyno::storage_info_for<RawT>)) {
      uses_heap_ = false;
      new (&sb_) RawT(std::forward<T>(t));
    } else {
      uses_heap_ = true;
      ptr_ = std::malloc(sizeof(RawT));
      // TODO: Allocating and then calling the constructor is not
      //       exception-safe if the constructor throws.
      // TODO: That's not a really nice way to handle this
      assert(ptr_ != nullptr && "std::malloc failed, we're doomed");
      new (ptr_) RawT(std::forward<T>(t));
    }
  }

  template <typename VTable>
  sbo_storage(sbo_storage const& other, VTable const& vtable) {
    if (other.uses_heap()) {
      auto info = vtable["storage_info"_s]();
      uses_heap_ = true;
      ptr_ = std::malloc(info.size);
      // TODO: That's not a really nice way to handle this
      assert(ptr_ != nullptr && "std::malloc failed, we're doomed");
      vtable["copy-construct"_s](ptr_, other.get());
    } else {
      uses_heap_ = false;
      vtable["copy-construct"_s](&sb_, other.get());
    }
  }

  template <typename VTable>
  sbo_storage(sbo_storage&& other, VTable const& vtable)
    : uses_heap_{other.uses_heap()}
  {
    if (uses_heap()) {
      this->ptr_ = other.ptr_;
      other.ptr_ = nullptr;
    } else {
      vtable["move-construct"_s](this->get(), other.get());
    }
  }

  template <typename MyVTable, typename OtherVTable>
  void swap(MyVTable const& this_vtable, sbo_storage& other, OtherVTable const& other_vtable) {
    if (this == &other)
      return;

    if (this->uses_heap()) {
      if (other.uses_heap()) {
        std::swap(this->ptr_, other.ptr_);

      } else {
        void *ptr = this->ptr_;

        // Bring `other`'s contents to `*this`, destructively
        other_vtable["move-construct"_s](&this->sb_, &other.sb_);
        other_vtable["destruct"_s](&other.sb_);
        this->uses_heap_ = false;

        // Bring `*this`'s stuff to `other`
        other.ptr_ = ptr;
        other.uses_heap_ = true;
      }
    } else {
      if (other.uses_heap()) {
        void *ptr = other.ptr_;

        // Bring `*this`'s contents to `other`, destructively
        this_vtable["move-construct"_s](&other.sb_, &this->sb_);
        this_vtable["destruct"_s](&this->sb_);
        other.uses_heap_ = false;

        // Bring `other`'s stuff to `*this`
        this->ptr_ = ptr;
        this->uses_heap_ = true;

      } else {
        // Move `other` into temporary local storage, destructively.
        SBStorage tmp;
        other_vtable["move-construct"_s](&tmp, &other.sb_);
        other_vtable["destruct"_s](&other.sb_);

        // Move `*this` into `other`, destructively.
        this_vtable["move-construct"_s](&other.sb_, &this->sb_);
        this_vtable["destruct"_s](&this->sb_);

        // Now, bring `tmp` into `*this`, destructively.
        other_vtable["move-construct"_s](&this->sb_, &tmp);
        other_vtable["destruct"_s](&tmp);
      }
    }
  }

  template <typename VTable>
  void destruct(VTable const& vtable) {
    if (uses_heap()) {
      // If we've been moved from, don't do anything.
      if (ptr_ == nullptr)
        return;

      vtable["destruct"_s](ptr_);
      std::free(ptr_);
    } else {
      vtable["destruct"_s](&sb_);
    }
  }

  template <typename T = void>
  T* get() {
    return static_cast<T*>(uses_heap() ? ptr_ : &sb_);
  }

  template <typename T = void>
  T const* get() const {
    return static_cast<T const*>(uses_heap() ? ptr_ : &sb_);
  }

private:
  bool uses_heap() const { return uses_heap_; }
};

// Class implementing storage on the heap. Just like the `sbo_storage`, it
// only handles allocation and deallocation; construction and destruction
// must be handled externally.
struct remote_storage {
  remote_storage() = delete;
  remote_storage(remote_storage const&) = delete;
  remote_storage(remote_storage&&) = delete;
  remote_storage& operator=(remote_storage&&) = delete;
  remote_storage& operator=(remote_storage const&) = delete;

  template <typename T, typename RawT = std::decay_t<T>>
  explicit remote_storage(T&& t)
    : ptr_{std::malloc(sizeof(RawT))}
  {
    // TODO: That's not a really nice way to handle this
    assert(ptr_ != nullptr && "std::malloc failed, we're doomed");

    new (ptr_) RawT(std::forward<T>(t));
  }

  template <typename VTable>
  remote_storage(remote_storage const& other, VTable const& vtable)
    : ptr_{std::malloc(vtable["storage_info"_s]().size)}
  {
    // TODO: That's not a really nice way to handle this
    assert(ptr_ != nullptr && "std::malloc failed, we're doomed");

    vtable["copy-construct"_s](this->get(), other.get());
  }

  template <typename VTable>
  remote_storage(remote_storage&& other, VTable const&)
    : ptr_{other.ptr_}
  {
    other.ptr_ = nullptr;
  }

  template <typename MyVTable, typename OtherVTable>
  void swap(MyVTable const&, remote_storage& other, OtherVTable const&) {
    std::swap(this->ptr_, other.ptr_);
  }

  template <typename VTable>
  void destruct(VTable const& vtable) {
    // If we've been moved from, don't do anything.
    if (ptr_ == nullptr)
      return;

    vtable["destruct"_s](ptr_);
    std::free(ptr_);
  }

  template <typename T = void>
  T* get() {
    return static_cast<T*>(ptr_);
  }

  template <typename T = void>
  T const* get() const {
    return static_cast<T const*>(ptr_);
  }

  static constexpr bool can_store(dyno::storage_info) {
    return true;
  }

private:
  void* ptr_;
};

// Class implementing shared remote storage.
//
// This is basically the same as using a `std::shared_ptr` to store the
// polymorphic object.
//
// TODO:
// - Using `std::shared_ptr` in the implementation is suboptimal, because it
//   reimplements type erasure for the deleter, but we could really reuse our
//   vtable instead.
// - For remote storage policies, should it be possible to specify whether the
//   pointed-to storage is const?
struct shared_remote_storage {
  shared_remote_storage() = delete;
  shared_remote_storage(shared_remote_storage const&) = delete;
  shared_remote_storage(shared_remote_storage&&) = delete;
  shared_remote_storage& operator=(shared_remote_storage&&) = delete;
  shared_remote_storage& operator=(shared_remote_storage const&) = delete;

  template <typename T, typename RawT = std::decay_t<T>>
  explicit shared_remote_storage(T&& t)
    : ptr_{std::make_shared<RawT>(std::forward<T>(t))}
  { }

  template <typename VTable>
  shared_remote_storage(shared_remote_storage const& other, VTable const&)
    : ptr_{other.ptr_}
  { }

  template <typename VTable>
  shared_remote_storage(shared_remote_storage&& other, VTable const&)
    : ptr_{std::move(other.ptr_)}
  { }

  template <typename MyVTable, typename OtherVTable>
  void swap(MyVTable const&, shared_remote_storage& other, OtherVTable const&) {
    using std::swap;
    swap(this->ptr_, other.ptr_);
  }

  template <typename VTable>
  void destruct(VTable const&) {
    ptr_.reset();
  }

  template <typename T = void>
  T* get() {
    return static_cast<T*>(ptr_.get());
  }

  template <typename T = void>
  T const* get() const {
    return static_cast<T const*>(ptr_.get());
  }

  static constexpr bool can_store(dyno::storage_info) {
    return true;
  }

private:
  std::shared_ptr<void> ptr_;
};

// Class implementing unconditional storage in a local buffer.
//
// This is like a small buffer optimization, except the behavior is undefined
// when the object can't fit inside the buffer. Since we know the object always
// sits inside the local buffer, we can get rid of a branch when accessing the
// object.
template <std::size_t Size, std::size_t Align = static_cast<std::size_t>(-1)>
class local_storage {
  static constexpr std::size_t SBAlign = Align == static_cast<std::size_t>(-1)
                                            ? alignof(std::aligned_storage_t<Size>)
                                            : Align;
  using SBStorage = std::aligned_storage_t<Size, SBAlign>;
  SBStorage buffer_;

public:
  local_storage() = delete;
  local_storage(local_storage const&) = delete;
  local_storage(local_storage&&) = delete;
  local_storage& operator=(local_storage&&) = delete;
  local_storage& operator=(local_storage const&) = delete;

  static constexpr bool can_store(dyno::storage_info info) {
    return info.size <= sizeof(SBStorage) && alignof(SBStorage) % info.alignment == 0;
  }

  template <typename T, typename RawT = std::decay_t<T>>
  explicit local_storage(T&& t) {
    // TODO: We could also construct the object at an aligned address within
    // the buffer, which would require computing the right address everytime
    // we access the buffer as a T, but would allow more Ts to fit inside it.
    static_assert(can_store(dyno::storage_info_for<RawT>),
      "dyno::local_storage: Trying to construct from an object that won't fit "
      "in the local storage.");

    new (&buffer_) RawT(std::forward<T>(t));
  }

  template <typename VTable>
  local_storage(local_storage const& other, VTable const& vtable) {
    assert(can_store(vtable["storage_info"_s]()) &&
      "dyno::local_storage: Trying to copy-construct using a vtable that "
      "describes an object that won't fit in the storage.");

    vtable["copy-construct"_s](this->get(), other.get());
  }

  template <typename VTable>
  local_storage(local_storage&& other, VTable const& vtable) {
    assert(can_store(vtable["storage_info"_s]()) &&
      "dyno::local_storage: Trying to move-construct using a vtable that "
      "describes an object that won't fit in the storage.");

    vtable["move-construct"_s](this->get(), other.get());
  }

  template <typename MyVTable, typename OtherVTable>
  void swap(MyVTable const& this_vtable, local_storage& other, OtherVTable const& other_vtable) {
    if (this == &other)
      return;

    // Move `other` into temporary local storage, destructively.
    SBStorage tmp;
    other_vtable["move-construct"_s](&tmp, &other.buffer_);
    other_vtable["destruct"_s](&other.buffer_);

    // Move `*this` into `other`, destructively.
    this_vtable["move-construct"_s](&other.buffer_, &this->buffer_);
    this_vtable["destruct"_s](&this->buffer_);

    // Now, bring `tmp` into `*this`, destructively.
    other_vtable["move-construct"_s](&this->buffer_, &tmp);
    other_vtable["destruct"_s](&tmp);
  }

  template <typename VTable>
  void destruct(VTable const& vtable) {
    vtable["destruct"_s](&buffer_);
  }

  template <typename T = void>
  T* get() {
    return static_cast<T*>(static_cast<void*>(&buffer_));
  }

  template <typename T = void>
  T const* get() const {
    return static_cast<T const*>(static_cast<void const*>(&buffer_));
  }
};

// Class implementing a non-owning polymorphic reference. Unlike the other
// storage classes, this one does not own the object it holds, and hence it
// does not construct or destruct it. The referenced object must outlive the
// polymorphic storage that references it, otherwise the behavior is undefined.
struct non_owning_storage {
  non_owning_storage() = delete;
  non_owning_storage(non_owning_storage const&) = delete;
  non_owning_storage(non_owning_storage&&) = delete;
  non_owning_storage& operator=(non_owning_storage&&) = delete;
  non_owning_storage& operator=(non_owning_storage const&) = delete;

  template <typename T>
  explicit non_owning_storage(T& t)
    : ptr_{&t}
  { }

  template <typename VTable>
  non_owning_storage(non_owning_storage const& other, VTable const&)
    : ptr_{other.ptr_}
  { }

  template <typename VTable>
  non_owning_storage(non_owning_storage&& other, VTable const&)
    : ptr_{other.ptr_}
  { }

  template <typename MyVTable, typename OtherVTable>
  void swap(MyVTable const&, non_owning_storage& other, OtherVTable const&) {
    std::swap(this->ptr_, other.ptr_);
  }

  template <typename VTable>
  void destruct(VTable const&) { }

  template <typename T = void>
  T* get() {
    return static_cast<T*>(ptr_);
  }

  template <typename T = void>
  T const* get() const {
    return static_cast<T const*>(ptr_);
  }

  static constexpr bool can_store(dyno::storage_info) {
    return true;
  }

private:
  void* ptr_;
};

// Class implementing polymorphic storage with a primary storage and a
// fallback one.
//
// When the primary storage can be used to store a type, it is used. When it
// can't, however, the secondary storage is used instead. This can be used
// to implement a small buffer optimization, by using `dyno::local_storage` as
// the primary storage, and `dyno::remote_storage` as the secondary.
//
// TODO:
// - Consider implementing this by storing a pointer to the active object.
// - Alternatively, if we had a way to access the vtable here, we could
//   retrieve the size of the type from it and know whether we are in the
//   primary or the secondary storage like that.
// - If we were to store the vtable inside storage classes, we could also
//   encode which storage is active using the low bits of the pointer.
// - Technically, this could be used to implement `sbo_storage`. However,
//   benchmarks show that `sbo_storage` is significantly more efficient.
//   We should try to optimize `fallback_storage` so that it can replace sbo.
template <typename First, typename Second>
class fallback_storage {
  union { First first_; Second second_; };
  bool in_first_;

  bool in_first() const { return in_first_; }

public:
  fallback_storage() = delete;
  fallback_storage(fallback_storage const&) = delete;
  fallback_storage(fallback_storage&&) = delete;
  fallback_storage& operator=(fallback_storage&&) = delete;
  fallback_storage& operator=(fallback_storage const&) = delete;

  template <typename T, typename RawT = std::decay_t<T>,
            typename = std::enable_if_t<First::can_store(dyno::storage_info_for<RawT>)>>
  explicit fallback_storage(T&& t) : in_first_{true}
  { new (&first_) First{std::forward<T>(t)}; }

  template <typename T, typename RawT = std::decay_t<T>, typename = void,
            typename = std::enable_if_t<!First::can_store(dyno::storage_info_for<RawT>)>>
  explicit fallback_storage(T&& t) : in_first_{false} {
    static_assert(can_store(dyno::storage_info_for<RawT>),
      "dyno::fallback_storage<First, Second>: Trying to construct from a type "
      "that can neither be stored in the primary nor in the secondary storage.");

    new (&second_) Second{std::forward<T>(t)};
  }

  template <typename VTable>
  fallback_storage(fallback_storage const& other, VTable const& vtable)
    : in_first_{other.in_first_}
  {
    if (in_first())
      new (&first_) First{other.first_, vtable};
    else
      new (&second_) Second{other.second_, vtable};
  }

  template <typename VTable>
  fallback_storage(fallback_storage&& other, VTable const& vtable)
    : in_first_{other.in_first_}
  {
    if (in_first())
      new (&first_) First{std::move(other.first_), vtable};
    else
      new (&second_) Second{std::move(other.second_), vtable};
  }

  // TODO: With a destructive move, we could avoid all the calls to `destruct` below.
  template <typename MyVTable, typename OtherVTable>
  void swap(MyVTable const& this_vtable, fallback_storage& other, OtherVTable const& other_vtable) {
    if (this->in_first()) {
      if (other.in_first()) {
        this->first_.swap(this_vtable, other.first_, other_vtable);
      } else {
        // Move `this->first` into a temporary, destructively.
        First tmp{std::move(this->first_), this_vtable};
        this->first_.destruct(this_vtable);
        this->first_.~First();

        // Move `other.second` into `this->second`, destructively.
        new (&this->second_) Second{std::move(other.second_), other_vtable};
        this->in_first_ = false;
        other.second_.destruct(other_vtable);
        other.second_.~Second();

        // Move `tmp` into `other.first`.
        new (&other.first_) First{std::move(tmp), this_vtable};
        other.in_first_ = true;
      }
    } else {
      if (other.in_first()) {
        // Move `this->second` into a temporary, destructively.
        Second tmp{std::move(this->second_), this_vtable};
        this->second_.destruct(this_vtable);
        this->second_.~Second();

        // Move `other.first` into `this->first`, destructively.
        new (&this->first_) First{std::move(other.first_), other_vtable};
        this->in_first_ = true;
        other.first_.destruct(other_vtable);
        other.first_.~First();

        // Move `tmp` into `other.second`.
        new (&other.second_) Second{std::move(tmp), this_vtable};
        other.in_first_ = false;
      } else {
        this->second_.swap(this_vtable, other.second_, other_vtable);
      }
    }
  }

  template <typename VTable>
  void destruct(VTable const& vtable) {
    if (in_first())
      first_.destruct(vtable);
    else
      second_.destruct(vtable);
  }

  template <typename T = void>
  T* get() {
    return static_cast<T*>(in_first() ? first_.template get<T>()
                                      : second_.template get<T>());
  }

  template <typename T = void>
  T const* get() const {
    return static_cast<T const*>(in_first() ? first_.template get<T>()
                                            : second_.template get<T>());
  }

  static constexpr bool can_store(dyno::storage_info info) {
    return First::can_store(info) || Second::can_store(info);
  }
};

} // end namespace dyno

#endif // DYNO_STORAGE_HPP
