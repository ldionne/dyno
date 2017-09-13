// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#ifndef DYNO_DETAIL_IS_PLACEHOLDER_HPP
#define DYNO_DETAIL_IS_PLACEHOLDER_HPP

#include <dyno/detail/dsl.hpp>

#include <type_traits>


namespace dyno { namespace detail {

// Metafunction returning whether a type is a possibly const/ref-qualified
// placeholder, or a pointer to one.
template <typename T>
struct is_placeholder : std::false_type { };

template <> struct is_placeholder<dyno::T&> : std::true_type { };
template <> struct is_placeholder<dyno::T&&> : std::true_type { };
template <> struct is_placeholder<dyno::T*> : std::true_type { };

template <> struct is_placeholder<dyno::T const&> : std::true_type { };
template <> struct is_placeholder<dyno::T const&&> : std::true_type { };
template <> struct is_placeholder<dyno::T const*> : std::true_type { };

}} // end namespace dyno::detail

#endif // DYNO_DETAIL_IS_PLACEHOLDER_HPP
