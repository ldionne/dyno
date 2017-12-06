// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <dyno/detail/has_duplicates.hpp>

#include <boost/hana/integral_constant.hpp>
#include <boost/hana/not.hpp>
#include <boost/hana/tuple.hpp>
namespace hana = boost::hana;


static_assert(!dyno::detail::has_duplicates(hana::make_tuple()));
static_assert(!dyno::detail::has_duplicates(hana::make_tuple(hana::int_c<0>)));

static_assert(!dyno::detail::has_duplicates(hana::make_tuple(hana::int_c<0>, hana::int_c<1>)));
static_assert(dyno::detail::has_duplicates(hana::make_tuple(hana::int_c<1>, hana::int_c<1>)));

static_assert(!dyno::detail::has_duplicates(hana::make_tuple(hana::int_c<0>, hana::int_c<1>, hana::int_c<2>)));
static_assert(dyno::detail::has_duplicates(hana::make_tuple(hana::int_c<0>, hana::int_c<1>, hana::int_c<0>)));
static_assert(dyno::detail::has_duplicates(hana::make_tuple(hana::int_c<0>, hana::int_c<0>, hana::int_c<2>)));

static_assert(!dyno::detail::has_duplicates(hana::make_tuple(hana::int_c<0>, hana::int_c<1>, hana::int_c<2>, hana::int_c<3>)));
static_assert(dyno::detail::has_duplicates(hana::make_tuple(hana::int_c<0>, hana::int_c<1>, hana::int_c<2>, hana::int_c<0>)));
static_assert(dyno::detail::has_duplicates(hana::make_tuple(hana::int_c<0>, hana::int_c<1>, hana::int_c<0>, hana::int_c<0>)));
static_assert(dyno::detail::has_duplicates(hana::make_tuple(hana::int_c<0>, hana::int_c<1>, hana::int_c<0>, hana::int_c<0>)));
static_assert(dyno::detail::has_duplicates(hana::make_tuple(hana::int_c<0>, hana::int_c<0>, hana::int_c<2>, hana::int_c<3>)));
static_assert(dyno::detail::has_duplicates(hana::make_tuple(hana::int_c<0>, hana::int_c<0>, hana::int_c<0>, hana::int_c<0>)));

int main() { }
