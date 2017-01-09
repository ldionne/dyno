// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#ifndef TE_DETAIL_ERASE_SIGNATURE_HPP
#define TE_DETAIL_ERASE_SIGNATURE_HPP

#include <te/dsl.hpp>

#include <type_traits>


namespace te { namespace detail {

// Transforms the type of a placeholder into a representation suitable for
// passing around generically as function parameters. Basically, this turns
// a type like `te::T&` into a `void*`, and similarly for other types of
// possibly const or ref-qualified `te::T`s.
template <typename T>
struct erase_placeholder {
  static_assert(!std::is_same<T, te::T>{},
    "te::T may not be passed by value; it is only a placeholder");
  using type = T;
};

template <>
struct erase_placeholder<te::T const&> {
  using type = void const*;
};

template <>
struct erase_placeholder<te::T &> {
  using type = void*;
};

template <>
struct erase_placeholder<te::T &&> {
  using type = void*;
};

template <>
struct erase_placeholder<te::T *> {
  using type = void*;
};

template <>
struct erase_placeholder<te::T const *> {
  using type = void const*;
};

// Transforms a signature potentially containing placeholders into a signature
// containing no placeholders, and which would be suitable for storing as a
// function pointer.
//
// Basically, this turns types like `te::T&` into `void*` at the top-level of
// the signature. This is used when we need to generate a vtable from a concept
// definition. The concept definition provides signatures with placeholders,
// and we need to generate a concrete type that can be stored in a vtable.
// That concrete type is the result of `erase_signature`.
//
// Note that this returns a function signature, not a function pointer type.
// For actually storing an object of this type, one needs to add a pointer
// qualifier to it.
template <typename T>
struct erase_signature;

template <typename R, typename ...Args>
struct erase_signature<R (Args...)> {
  using type = typename erase_placeholder<R>::type (typename erase_placeholder<Args>::type...);
};

template <typename R, typename ...Args>
struct erase_signature<R (Args..., ...)> {
  using type = typename erase_placeholder<R>::type (typename erase_placeholder<Args>::type..., ...);
};

}} // end namespace te::detail

#endif // TE_DETAIL_ERASE_SIGNATURE_HPP
