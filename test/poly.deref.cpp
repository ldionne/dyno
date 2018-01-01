// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include "testing.hpp"

#include <dyno/concept.hpp>
#include <dyno/concept_map.hpp>
#include <dyno/poly.hpp>
using namespace dyno::literals;


// This test makes sure that `dyno::poly::operator->*` is equivalent to
// `dyno::poly::virtual_`.

struct Concept : decltype(dyno::requires(
  "f"_dyno = dyno::function<int (dyno::T&)>,
  "g"_dyno = dyno::function<double (dyno::T&, double)>
)) { };

struct Foo { };

template <>
auto const dyno::concept_map<Concept, Foo> = dyno::make_concept_map(
  "f"_dyno = [](Foo&) { return 111; },
  "g"_dyno = [](Foo&, double d) { return d; }
);

int main() {
  Foo foo;
  dyno::poly<Concept> poly{foo};
  DYNO_CHECK(poly->*"f"_dyno() == 111);
  DYNO_CHECK(poly->*"g"_dyno(3.3) == 3.3);
}
