// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#ifndef DYNO_DETAIL_ERASER_TRAITS_HPP
#define DYNO_DETAIL_ERASER_TRAITS_HPP

#include <dyno/detail/dsl.hpp>

#include <type_traits>
#include <utility>


namespace dyno { namespace detail {

// Traits for types that can be used to erase other types. The following traits
// should be provided:
//
//  template <typename Eraser, typename Placeholder>
//  struct erase_placeholder;
//
//    Metafunction transforming the type of a possibly cv and ref-qualified
//    placeholder (a `dyno::T`) into a representation suitable for passing
//    around as a parameter to an erased function. Basically, this turns a
//    type like `dyno::T&` into a `void*`, and similarly for other types of
//    possibly, const or ref-qualified `dyno::T`s, but it can be customized
//    for custom eraser types.
//
//  template <typename Eraser, typename Placeholder, typename Actual>
//  static constexpr erase_placeholder<Eraser, Placeholder>::type
//    erase<Eraser, Placeholder>::apply(Actual);
//
//    Function transforming an object to the generic representation for the
//    given placeholder for that eraser. This is used to obtain a representation
//    of the object that can be passed to an erased function stored in a vtable.
//    For example, in the case of the `void` eraser, this function just takes a
//    reference or a pointer to an actual type and passes it as a `void*`, with
//    the proper cv qualifiers. Note that an eraser is not expected to support
//    erasure of arbitrary types. For example, it is perfectly fine to give an
//    error if one tries to erase an `int` as a `dyno::T&`, since that makes no
//    sense. However, it is probably a good idea to support inexact casts that
//    do make sense, such as erasing `int&` to `dyno::T const&` (even though the
//    cv-qualifiers don't match). This is left to the implementation of the
//    specific eraser.
//
//  template <typename Eraser, typename Placeholder, typename Actual>
//  static constexpr Actual
//    unerase<Eraser, Placeholder, Actual>
//      ::apply(erase_placeholder<Eraser, Placeholder>::type)
//
//    This is the inverse operation to `erase`. It takes an object that was
//    erased and interprets it as an object of the specified `Actual` type.
//    The eraser can assume that the object that was erased is indeed of the
//    requested type. This function is used to transform an object with an
//    erased representation into an object that can be passed to a function
//    stored in a concept map.

template <typename Eraser, typename Placeholder>
struct erase_placeholder {
  static_assert(!std::is_same<Placeholder, dyno::T>{},
    "dyno::T may not be passed by value; it is only a placeholder");
  using type = Placeholder;
};

template <typename Eraser, typename Placeholder>
struct erase {
  template <typename Arg>
  static constexpr decltype(auto) apply(Arg&& arg) {
    return std::forward<Arg>(arg);
  }
};

template <typename Eraser, typename Placeholder, typename Actual>
struct unerase {
  template <typename Arg>
  static constexpr decltype(auto) apply(Arg&& arg)
  { return std::forward<Arg>(arg); }
};

// Specialization for the `void` Eraser, which uses `void*` to erase types.
template <> struct erase_placeholder<void, dyno::T const&> { using type = void const*; };
template <> struct erase_placeholder<void, dyno::T&>       { using type = void*; };
template <> struct erase_placeholder<void, dyno::T&&>      { using type = void*; };
template <> struct erase_placeholder<void, dyno::T*>       { using type = void*; };
template <> struct erase_placeholder<void, dyno::T const*> { using type = void const*; };

template <>
struct erase<void, dyno::T const&> {
  template <typename Arg>
  static constexpr void const* apply(Arg const& arg)
  { return &arg; }
};
template <>
struct erase<void, dyno::T&> {
  template <typename Arg>
  static constexpr void* apply(Arg& arg)
  { return &arg; }
};
template <>
struct erase<void, dyno::T&&> {
  template <typename Arg>
  static constexpr void* apply(Arg&& arg) {
    static_assert(std::is_rvalue_reference<Arg&&>::value, "will move from non-rvalue");
    return &arg;
  }
};
template <>
struct erase<void, dyno::T const*> {
  template <typename Arg>
  static constexpr void const* apply(Arg const* arg)
  { return arg; }
};
template <>
struct erase<void, dyno::T*> {
  template <typename Arg>
  static constexpr void* apply(Arg* arg)
  { return arg; }
};

template <typename Actual>
struct unerase<void, dyno::T&, Actual&> {
  static constexpr Actual& apply(void* arg)
  { return *static_cast<Actual*>(arg); }
};
template <typename Actual>
struct unerase<void, dyno::T const&, Actual const&> {
  static constexpr Actual const& apply(void const* arg)
  { return *static_cast<Actual const*>(arg); }
};
template <typename Actual>
struct unerase<void, dyno::T&&, Actual&&> {
  static constexpr Actual&& apply(void* arg)
  { return std::move(*static_cast<Actual*>(arg)); }
};
template <typename Actual>
struct unerase<void, dyno::T*, Actual*> {
  static constexpr Actual* apply(void* arg)
  { return static_cast<Actual*>(arg); }
};
template <typename Actual>
struct unerase<void, dyno::T const*, Actual const*> {
  static constexpr Actual const* apply(void const* arg)
  { return static_cast<Actual const*>(arg); }
};

}} // end namespace dyno::detail

#endif // DYNO_DETAIL_ERASER_TRAITS_HPP
