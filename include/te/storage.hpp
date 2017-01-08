// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#ifndef TE_STORAGE_HPP
#define TE_STORAGE_HPP

#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <type_traits>


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

// Class implementing the small buffer optimization (SBO).
//
// This class represents a value of an unknown type that is stored either on
// the heap, or on the stack if it fits in the specific small buffer size.
//
// This class is a building block for other, more complex utilities. It handles
// only the logic related to the storage of the object, but __nothing__ else.
// In particular, the object stored in this class is never constructed and
// never destroyed (but we do reclaim heap storage if it was allocated).
//
// Indeed, properly handling construction and destruction would require the
// `small_buffer` to remember the constructor/destructor that must be called,
// which is beyond its scope. Instead, the user of `small_buffer` is expected
// to set up some virtual dispatching mechanism on its own, which should
// include virtual construction/destruction if desirable.
//
// General usage goes like this:
// ```
// small_buffer<8> buf{te::type_info_for<std::string>};
// // `buf` is able to hold a string, maybe in the small buffer or maybe on
// // the heap. However, `buf` does not contain anything at this point and
// // it does not remember the type that it can contain. Constructing and
// // destroying are the responsibility of the user.
// new (buf.get()) std::string{"abcdef"};  // may be on the heap or on the stack
// std::string* p = buf.get<std::string>();
// buf.get<std::string>()->~std::string(); // must be called manually too
// ```
//
// The nice thing about `small_buffer` is that it has a single type and its
// ABI does not change even if the type of what it holds changes. However, it
// provides this at the cost of "forgetting" this information, and type erasure
// techniques must be used on top of `small_buffer` to do anything useful.
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

  explicit small_buffer(te::type_info info) {
    // TODO: We could also construct the object at an aligned address within
    // the buffer, which would require computing the right address everytime
    // we access the buffer as a T, but would allow more Ts to fit in the SBO.
    if (can_use_sbo(info)) {
      uses_heap_ = false;
    } else {
      uses_heap_ = true;
      ptr_ = std::malloc(info.size);
      // TODO: That's not a really nice way to handle this
      assert(ptr_ != nullptr && "std::malloc failed, we're doomed");
    }
  }

  ~small_buffer() {
    if (uses_heap())
      std::free(ptr_);
  }

  bool uses_heap() const { return uses_heap_; }

  template <typename T = void>
  T* get() {
    return static_cast<T*>(uses_heap() ? ptr_ : &sb_);
  }

  template <typename T = void>
  T const* get() const {
    return static_cast<T const*>(uses_heap() ? ptr_ : &sb_);
  }
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

  explicit heap_storage(te::type_info info)
    : ptr_{std::malloc(info.size)}
  {
    // TODO: That's not a really nice way to handle this
    assert(ptr_ != nullptr && "std::malloc failed, we're doomed");
  }

  ~heap_storage() {
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

  // When we try to assign from something that's statically known, we
  // can do some compile-time checks.
  template <typename T>
  explicit local_storage(static_type_info<T>) {
    static_assert(can_use_sbo(static_type_info<T>{}),
      "trying to use te::local_storage with an object that won't fit in the local storage");
  }

  explicit local_storage(te::type_info info) {
    assert(can_use_sbo(info) &&
      "trying to use te::local_storage with an object that won't fit in the local storage");
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

} // end namespace te

#endif // TE_STORAGE_HPP
