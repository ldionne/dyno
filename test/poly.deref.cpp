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
  "f"_s = dyno::function<int (dyno::T&)>
)) { };

struct Foo { };

template <>
auto const dyno::concept_map<Concept, Foo> = dyno::make_concept_map(
  "f"_s = [](Foo&) { return 111; }
);

int main() {
  Foo foo;
  dyno::poly<Concept> poly{foo};
  DYNO_CHECK(poly->*"f"_s(poly) == 111);
}
