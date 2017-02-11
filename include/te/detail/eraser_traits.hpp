// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#ifndef TE_DETAIL_ERASER_TRAITS_HPP
#define TE_DETAIL_ERASER_TRAITS_HPP

#include <te/detail/dsl.hpp>

#include <type_traits>
#include <utility>


namespace te { namespace detail {

// Traits for types that can be used to erase other types. These traits should
// provide the following:
//
//  template <typename Placeholder>
//  struct erase_placeholder;
//
//    Metafunction transforming the type of a possibly cv and ref-qualified
//    placeholder (a `te::T`) into a representation suitable for passing
//    around as a parameter to an erased function. Basically, this turns a
//    type like `te::T&` into a `void*`, and similarly for other types of
//    possibly, const or ref-qualified `te::T`s, but it can be customized
//    for custom eraser types.
//
//  template <typename Placeholder, typename Actual>
//  static constexpr erase_placeholder<Placeholder>::type erase(Actual);
//
//    Function transforming an object to the generic representation for the
//    given placeholder for that eraser. This is used to obtain a representation
//    of the object that can be passed to an erased function stored in a vtable.
//    For example, in the case of the `void` eraser, this function just takes a
//    reference or a pointer to an actual type and passes it as a `void*`, with
//    the proper cv qualifiers. Note that an eraser is not expected to support
//    erasure of arbitrary types. For example, it is perfectly fine to give an
//    error if one tries to erase an `int` as a `te::T&`, since that makes no
//    sense. However, it is probably a good idea to support inexact casts that
//    do make sense, such as erasing `int&` to `te::T const&` (even though the
//    cv-qualifiers don't match). This is left to the implementation of the
//    specific eraser.
//
//  template <typename Placeholder, typename Actual, typename Erased>
//  static constexpr Actual unerase(Erased);
//
//    This is the inverse operation to `erase`. It takes an object that was
//    erased and interprets it as an object of the specified `Actual` type.
//    The eraser can assume that the object that was erased is indeed of the
//    requested type. This function is used to transform an object with an
//    erased representation into an object that can be passed to a function
//    stored in a concept map.
template <typename Eraser>
struct eraser_traits;


// Specialization for the `void` Eraser, which uses `void*` to erase types.
template <typename T>
struct void_erase_placeholder {
  static_assert(!std::is_same<T, te::T>{},
    "te::T may not be passed by value; it is only a placeholder");
  using type = T;
};
template <> struct void_erase_placeholder<te::T const&>  { using type = void const*; };
template <> struct void_erase_placeholder<te::T &>       { using type = void*; };
template <> struct void_erase_placeholder<te::T &&>      { using type = void*; };
template <> struct void_erase_placeholder<te::T *>       { using type = void*; };
template <> struct void_erase_placeholder<te::T const *> { using type = void const*; };

template <typename Pl, typename Actual>
struct void_erase_impl {
  template <typename Arg>
  static constexpr decltype(auto) apply(Arg&& arg)
  { return std::forward<Arg>(arg); }
};
template <typename Actual>
struct void_erase_impl<te::T const&, Actual const&> {
  static constexpr void const* apply(Actual const& arg)
  { return &arg; }
};
template <typename Actual>
struct void_erase_impl<te::T&, Actual&> {
  static constexpr void* apply(Actual& arg)
  { return &arg; }
};
template <typename Actual>
struct void_erase_impl<te::T&&, Actual&&> {
  static constexpr void* apply(Actual&& arg)
  { return &arg; }
};
template <typename Actual>
struct void_erase_impl<te::T*, Actual*> {
  static constexpr void* apply(Actual* arg)
  { return arg; }
};
template <typename Actual>
struct void_erase_impl<te::T const*, Actual const&> {
  static constexpr void const* apply(Actual const* arg)
  { return arg; }
};

template <typename Pl, typename Actual>
struct void_unerase_impl {
  template <typename Arg>
  static constexpr decltype(auto) apply(Arg&& arg)
  { return std::forward<Arg>(arg); }
};
template <typename Actual>
struct void_unerase_impl<te::T&, Actual&> {
  static constexpr Actual& apply(void* arg)
  { return *static_cast<Actual*>(arg); }
};
template <typename Actual>
struct void_unerase_impl<te::T const&, Actual const&> {
  static constexpr Actual const& apply(void const* arg)
  { return *static_cast<Actual const*>(arg); }
};
template <typename Actual>
struct void_unerase_impl<te::T&&, Actual&&> {
  static constexpr Actual&& apply(void* arg)
  { return std::move(*static_cast<Actual*>(arg)); }
};
template <typename Actual>
struct void_unerase_impl<te::T*, Actual*> {
  static constexpr Actual* apply(void* arg)
  { return static_cast<Actual*>(arg); }
};
template <typename Actual>
struct void_unerase_impl<te::T const*, Actual const*> {
  static constexpr Actual const* apply(void const* arg)
  { return static_cast<Actual const*>(arg); }
};

template <>
struct eraser_traits<void> {
  template <typename T>
  using erase_placeholder = void_erase_placeholder<T>;

  template <typename Placeholder, typename Actual>
  static constexpr typename erase_placeholder<Placeholder>::type erase(Actual&& arg) {
    return void_erase_impl<Placeholder, Actual>::apply(std::forward<Actual>(arg));
  }

  template <typename Placeholder, typename Actual, typename Erased>
  static constexpr Actual unerase(Erased&& erased) {
    return void_unerase_impl<Placeholder, Actual>::apply(std::forward<Erased>(erased));
  }
};

}} // end namespace te::detail

#endif // TE_DETAIL_ERASER_TRAITS_HPP
