// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#ifndef TE_DETAIL_SMALL_POINTER_HPP
#define TE_DETAIL_SMALL_POINTER_HPP

#include <cstddef>
#include <cstdint>


namespace te { namespace detail {

template <typename Int>
constexpr std::size_t log2(Int i) {
  std::size_t log = 0;
  for (; i > 1; i /= 2)
    ++log;
  return log;
}

template <typename T>
struct free_low_bits;

template <typename T>
struct free_low_bits<T*> { static constexpr std::size_t value = detail::log2(alignof(T)); };

template <>
struct free_low_bits<void*> { static constexpr std::size_t value = 0; };


template <typename T>
struct small_pointer;

template <typename T>
struct small_pointer<T*> {
private:
  static constexpr std::size_t FreeLowBits = detail::free_low_bits<T*>::value;

  // Mask to get the bits that come from the pointer.
  static constexpr std::uintptr_t PointerMask =
    ~(std::uintptr_t)(((std::intptr_t)1 << FreeLowBits) - 1);

  std::intptr_t ptr_;

public:
  constexpr small_pointer() : ptr_{0} { }
  constexpr small_pointer(small_pointer const&) = default;
  constexpr small_pointer(small_pointer&&) = default;
  constexpr small_pointer& operator=(small_pointer const&) = default;
  constexpr small_pointer& operator=(small_pointer&&) = default;

  small_pointer(T* p)
    : ptr_{reinterpret_cast<std::intptr_t>(p) & PointerMask}
  { }

  T& operator*() const
  { return *reinterpret_cast<T*>(ptr_ & PointerMask); }

  T* operator->() const
  { return reinterpret_cast<T*>(ptr_ & PointerMask); }

  operator T* const
  { return reinterpret_cast<T*>(ptr_ & PointerMask); }

  small_pointer& operator=(T* p) {
    std::intptr_t const p_value = reinterpret_cast<std::intptr_t>(p) & PointerMask;
    std::intptr_t const bits = ptr_ & ~PointerBitMask;
    ptr_ = p_value | bits;
    return *this;
  }
};

}} // end namespace te::detail

#endif // TE_DETAIL_SMALL_POINTER_HPP
