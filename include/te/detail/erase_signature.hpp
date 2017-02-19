// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#ifndef TE_DETAIL_ERASE_SIGNATURE_HPP
#define TE_DETAIL_ERASE_SIGNATURE_HPP

#include <te/detail/eraser_traits.hpp>
#include <te/detail/transform_signature.hpp>


namespace te { namespace detail {

// Transforms a signature potentially containing placeholders into a signature
// containing no placeholders, and which would be suitable for storing as a
// function pointer.
//
// Basically, this turns types like `te::T&` into `void*` (or what's specified
// by the given `Eraser`) at the top-level of the signature. This is used when
// we need to generate a vtable from a concept definition. The concept defines
// signatures with placeholders, and we need to generate a concrete function
// type that can be stored in a vtable. That concrete type is the result of
// `erase_signature`.
//
// Note that this returns a function type, not a function pointer type.
// For actually storing an object of this type, one needs to add a pointer
// qualifier to it.
template <typename Signature, typename Eraser = void>
using erase_signature = detail::transform_signature<
  Signature, detail::eraser_traits<Eraser>::template erase_placeholder
>;

}} // end namespace te::detail

#endif // TE_DETAIL_ERASE_SIGNATURE_HPP
