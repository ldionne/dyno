// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#ifndef DYNO_DETAIL_BIND_SIGNATURE_HPP
#define DYNO_DETAIL_BIND_SIGNATURE_HPP

#include <dyno/detail/dsl.hpp>
#include <dyno/detail/transform_signature.hpp>


namespace dyno { namespace detail {

template <typename Old, typename New, typename T>
struct replace_impl { using type = T; };

template <typename Old, typename New>
struct replace_impl<Old, New, Old> { using type = New; };
template <typename Old, typename New>
struct replace_impl<Old, New, Old&> { using type = New&; };
template <typename Old, typename New>
struct replace_impl<Old, New, Old&&> { using type = New&&; };
template <typename Old, typename New>
struct replace_impl<Old, New, Old*> { using type = New*; };

template <typename Old, typename New>
struct replace_impl<Old, New, Old const> { using type = New const; };
template <typename Old, typename New>
struct replace_impl<Old, New, Old const&> { using type = New const&; };
template <typename Old, typename New>
struct replace_impl<Old, New, Old const&&> { using type = New const&&; };
template <typename Old, typename New>
struct replace_impl<Old, New, Old const*> { using type = New const*; };

template <typename Old, typename New>
struct replace {
  template <typename T>
  using apply = replace_impl<Old, New, T>;
};

// Takes a placeholder signature and replaces instances of `dyno::T` by the given
// type.
//
// Basically, this will turn stuff like `void (dyno::T const&, int, dyno::T*)`
// into `void (T const&, int, T*)`, where `T` is the type we are _binding_
// the signature to.
//
// This is used to make sure that the functions provided in a concept map
// have the right signature.
template <typename Signature, typename T>
using bind_signature = detail::transform_signature<
  Signature, detail::replace<dyno::T, T>::template apply
>;

}} // end namespace dyno::detail

#endif // DYNO_DETAIL_BIND_SIGNATURE_HPP
