// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <dyno/concept.hpp>

#include <boost/hana/equal.hpp>
#include <boost/hana/map.hpp>
#include <boost/hana/type.hpp>
using namespace dyno::literals;
namespace hana = boost::hana;


struct A : decltype(dyno::requires(
  "f"_s = dyno::function<void (dyno::T&)>
)) { };

struct B : decltype(dyno::requires(
  A{},
  "g"_s = dyno::function<int (dyno::T&)>,
  "h"_s = dyno::function<double (dyno::T&, int)>
)) { };

struct C : decltype(dyno::requires(
  B{}
)) { };

static_assert(dyno::clauses(A{}) ==
              hana::make_map(
                "f"_s = dyno::function<void (dyno::T&)>
              ), "");

static_assert(dyno::clauses(B{}) ==
              hana::make_map(
                "f"_s = dyno::function<void (dyno::T&)>,
                "g"_s = dyno::function<int (dyno::T&)>,
                "h"_s = dyno::function<double (dyno::T&, int)>
              ), "");

static_assert(dyno::clauses(C{}) ==
              hana::make_map(
                "f"_s = dyno::function<void (dyno::T&)>,
                "g"_s = dyno::function<int (dyno::T&)>,
                "h"_s = dyno::function<double (dyno::T&, int)>
              ), "");

int main() { }
