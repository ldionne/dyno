// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#ifndef TE_STORAGE_HPP
#define TE_STORAGE_HPP

#include <te/dsl.hpp>

#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <type_traits>
#include <utility>


namespace te {

// Encapsulates the minimal amount of information required to allocate
// storage for an object of a given type.
//
// This should never be created explicitly; always use `te::type_info_for`.
//
// TODO: Rename this to `storage_info` or something along those lines, which
// is more tailored to storage only.
struct type_info {
  std::size_t size;
  std::size_t alignment;
};

template <typename T>
struct static_type_info {
  static constexpr std::size_t size = sizeof(T);
  static constexpr std::size_t alignment = alignof(T);
  constexpr operator type_info() const { return {size, alignment}; }
};

template <typename T>
constexpr static_type_info<T> type_info_for{};

// concept PolymorphicStorage
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
//             must also free any resource associated to the storage. This is
//             effectively a destructor, but destructors can't be passed
//             arguments so this needs to be called explicitly.
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
//  Semantics: Return a pointer to the object inside the polymorphic storage.
//
// template <typename T = void> T const* get() const;
//  Semantics: Return a pointer to the object inside the polymorphic storage.
//


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
template <std::size_t Size, std::size_t Align = static_cast<std::size_t>(-1)>
class small_buffer {
  static constexpr std::size_t SBSize = Size < sizeof(void*) ? sizeof(void*) : Size;
  static constexpr std::size_t SBAlign = Align == -1 ? alignof(std::aligned_storage_t<SBSize>) : Align;
  using SBStorage = std::aligned_storage_t<SBSize, SBAlign>;

  template <typename TypeInfo>
  static constexpr bool can_use_sbo(TypeInfo info) {
    return info.size <= sizeof(SBStorage) && alignof(SBStorage) % info.alignment == 0;
  }

  union {
    void* ptr_;
    SBStorage sb_;
  };
  // TODO: It might be possible to pack this bool inside the union somehow.
  bool uses_heap_;

public:
  small_buffer() = delete;
  small_buffer(small_buffer const&) = delete;
  small_buffer(small_buffer&&) = delete;
  small_buffer& operator=(small_buffer&&) = delete;
  small_buffer& operator=(small_buffer const&) = delete;

  template <typename T, typename RawT = std::decay_t<T>>
  explicit small_buffer(T&& t) {
    // TODO: We could also construct the object at an aligned address within
    // the buffer, which would require computing the right address everytime
    // we access the buffer as a T, but would allow more Ts to fit in the SBO.
    if (can_use_sbo(te::type_info_for<RawT>)) {
      uses_heap_ = false;
      new (&sb_) RawT(std::forward<T>(t));
    } else {
      uses_heap_ = true;
      ptr_ = std::malloc(sizeof(RawT));
      // TODO: That's not a really nice way to handle this
      assert(ptr_ != nullptr && "std::malloc failed, we're doomed");
      new (ptr_) RawT(std::forward<T>(t));
    }
  }

  template <typename VTable>
  small_buffer(small_buffer const& other, VTable const& vtable)
    : small_buffer{vtable["type_info"_s]()}
  {
    vtable["copy-construct"_s](this->get(), other.get());
  }

  template <typename VTable>
  small_buffer(small_buffer&& other, VTable const& vtable)
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
  void swap(MyVTable const& this_vtable, small_buffer& other, OtherVTable const& other_vtable) {
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

// Class implementing storage on the heap. Just like the `small_buffer`, it
// only handles allocation and deallocation; construction and destruction
// must be handled externally.
struct heap_storage {
  heap_storage() = delete;
  heap_storage(heap_storage const&) = delete;
  heap_storage(heap_storage&&) = delete;
  heap_storage& operator=(heap_storage&&) = delete;
  heap_storage& operator=(heap_storage const&) = delete;

  template <typename T, typename RawT = std::decay_t<T>>
  explicit heap_storage(T&& t)
    : ptr_{std::malloc(sizeof(RawT))}
  {
    // TODO: That's not a really nice way to handle this
    assert(ptr_ != nullptr && "std::malloc failed, we're doomed");

    new (ptr_) RawT(std::forward<T>(t));
  }

  template <typename VTable>
  heap_storage(heap_storage const& other, VTable const& vtable)
    : ptr_{std::malloc(vtable["type_info"_s]().size)}
  {
    // TODO: That's not a really nice way to handle this
    assert(ptr_ != nullptr && "std::malloc failed, we're doomed");

    vtable["copy-construct"_s](this->get(), other.get());
  }

  template <typename VTable>
  heap_storage(heap_storage&& other, VTable const&)
    : ptr_{other.ptr_}
  {
    other.ptr_ = nullptr;
  }

  template <typename MyVTable, typename OtherVTable>
  void swap(MyVTable const&, heap_storage& other, OtherVTable const&) {
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

private:
  void* ptr_;
};

// Class implementing unconditional storage in a local buffer.
//
// This is like a small buffer optimization, except the behavior is undefined
// when the object can't fit inside the buffer. Since we know the object always
// sits inside the local buffer, we can get rid of a branch when accessing the
// object.
template <std::size_t Size, std::size_t Align = static_cast<std::size_t>(-1)>
class local_storage {
  // TODO: This is actually copied from the small_buffer implementation, and
  // it would be nice to share some of this.
  static constexpr std::size_t SBAlign = Align == -1 ? alignof(std::aligned_storage_t<Size>) : Align;
  using SBStorage = std::aligned_storage_t<Size, SBAlign>;

  template <typename TypeInfo>
  static constexpr bool can_use_sbo(TypeInfo info) {
    return info.size <= sizeof(SBStorage) && alignof(SBStorage) % info.alignment == 0;
  }

  SBStorage buffer_;

public:
  local_storage() = delete;
  local_storage(local_storage const&) = delete;
  local_storage(local_storage&&) = delete;
  local_storage& operator=(local_storage&&) = delete;
  local_storage& operator=(local_storage const&) = delete;

  template <typename T, typename RawT = std::decay_t<T>>
  explicit local_storage(T&& t) {
    static_assert(can_use_sbo(te::type_info_for<RawT>),
      "te::local_storage: Trying to construct from an object that won't fit "
      "in the local storage.");

    new (&buffer_) RawT(std::forward<T>(t));
  }

  template <typename VTable>
  local_storage(local_storage const& other, VTable const& vtable) {
    assert(can_use_sbo(vtable["type_info"_s]()) &&
      "te::local_storage: Trying to copy-construct using a vtable that "
      "describes an object that won't fit in the storage.");

    vtable["copy-construct"_s](this->get(), other.get());
  }

  template <typename VTable>
  local_storage(local_storage&& other, VTable const& vtable) {
    assert(can_use_sbo(vtable["type_info"_s]()) &&
      "te::local_storage: Trying to move-construct using a vtable that "
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
    return static_cast<T*>(&buffer_);
  }

  template <typename T = void>
  T const* get() const {
    return static_cast<T const*>(&buffer_);
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
  non_owning_storage(non_owning_storage const& other, VTable const& vtable)
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

private:
  void* ptr_;
};

} // end namespace te

#endif // TE_STORAGE_HPP
