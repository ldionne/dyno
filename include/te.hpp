// Copyright Louis Dionne 2016
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#ifndef TE_HPP
#define TE_HPP

#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <type_traits>
#include <utility>


namespace te {
// Class implementing the small buffer optimization (SBO).
//
// This class represents a value of an unknown type that is stored either on
// the heap, or on the stack if it fits in the specific small buffer size.
//
// This class is a building block for other, more complex utilities. It handles
// only the logic related to the storage and construction of the object, but
// __nothing__ else. In particular, the object stored in this class is never
// destroyed (but we do reclaim heap storage if it was allocated). Indeed,
// properly handling destruction would require the `small_buffer` to remember
// the destructor that must be called, which is beyond its scope. Instead, the
// user of `small_buffer` is expected to set up some virtual dispatching
// mechanism on its own, which should include virtual destruction if desirable.
//
// General usage goes like this:
//
//    small_buffer<8> buf{std::string{"abcdef"}};
//    // `buf` holds a string, maybe in the small buffer or maybe on the heap.
//    // However, `buf` does not "remember" the type of the object it contains;
//    // this is the responsibility of the user.
//    std::string* p = buf.get<std::string>();
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
  template <typename T>
  static constexpr bool can_use_sbo = sizeof(T) <= sizeof(SBStorage) &&
                                      alignof(SBStorage) % alignof(T) == 0;

  union {
    void* ptr_;
    SBStorage sb_;
  };
  // TODO: It might be possible to pack this bool inside the union somehow.
  bool uses_heap_;

public:
  small_buffer() = delete;
  small_buffer& operator=(small_buffer const&) = delete;

  template <typename T, typename Decayed = std::decay_t<T>>
  explicit small_buffer(T&& t) {
    // TODO: We could also construct the object at an aligned address within
    // the buffer, which would require computing the right address everytime
    // we access the buffer as a T, but would allow more Ts to fit in the SBO.
    if (can_use_sbo<Decayed>) {
      uses_heap_ = false;
      new (&sb_) Decayed(std::forward<T>(t));
    }
    else {
      uses_heap_ = true;
      ptr_ = std::malloc(sizeof(Decayed));
      // TODO: That's not a really nice way to handle this
      assert(ptr_ != nullptr && "std::malloc failed, we're doomed");
      new (ptr_) Decayed(std::forward<T>(t));
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

} // end namespace te

#include <boost/hana/at_key.hpp>
#include <boost/hana/first.hpp>
#include <boost/hana/map.hpp>
#include <boost/hana/pair.hpp>
#include <boost/hana/second.hpp>

#include <type_traits>
#include <utility>


namespace te {
// Class implementing a simple vtable.
template <typename ...Method>
struct vtable {
  template <typename VTable>
  constexpr explicit vtable(VTable vtable)
    : vtbl_{boost::hana::make_map(
      [&](){
        Method m;
        auto name = boost::hana::first(m);
        using Signature = typename decltype(+boost::hana::second(m))::type;
        using StoredFptr = std::decay_t<Signature>;
        return boost::hana::make_pair(name, static_cast<StoredFptr>(vtable[name]));
      }()...
    )}
  { }

  template <typename Name>
  constexpr auto operator[](Name name) const {
    return vtbl_[name];
  }

private:
  boost::hana::map<
    boost::hana::pair<
      std::decay_t<decltype(boost::hana::first(std::declval<Method>()))>,
      std::decay_t<typename decltype(+boost::hana::second(std::declval<Method>()))::type>
    >...
  > vtbl_;
};

} // end namespace te

#endif // TE_HPP
