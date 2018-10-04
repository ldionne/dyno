// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <dyno/concept.hpp>

#include <boost/hana/core/to.hpp>
#include <boost/hana/equal.hpp>
#include <boost/hana/set.hpp>
#include <boost/hana/tuple.hpp>
#include <boost/hana/type.hpp>
using namespace dyno::literals;
namespace hana = boost::hana;


struct A : decltype(dyno::requires(
  "f"_dyno = dyno::function<void (dyno::T&)>
)) { };

struct B : decltype(dyno::requires(
  A{},
  "g"_dyno = dyno::function<int (dyno::T&)>,
  "h"_dyno = dyno::function<double (dyno::T&, int)>
)) { };

struct C : decltype(dyno::requires(
  B{}
)) { };

static_assert(hana::to_set(dyno::clauses(A{})) ==
              hana::to_set(hana::make_tuple(
                "f"_dyno = dyno::function<void (dyno::T&)>
              )), "");

static_assert(hana::to_set(dyno::clauses(B{})) ==
              hana::to_set(hana::make_tuple(
                "f"_dyno = dyno::function<void (dyno::T&)>,
                "g"_dyno = dyno::function<int (dyno::T&)>,
                "h"_dyno = dyno::function<double (dyno::T&, int)>
              )), "");

static_assert(hana::to_set(dyno::clauses(C{})) ==
              hana::to_set(hana::make_tuple(
                "f"_dyno = dyno::function<void (dyno::T&)>,
                "g"_dyno = dyno::function<int (dyno::T&)>,
                "h"_dyno = dyno::function<double (dyno::T&, int)>
              )), "");

int main() { }
