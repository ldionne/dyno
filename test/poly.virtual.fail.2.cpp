// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include "testing.hpp"

#include <dyno/concept.hpp>
#include <dyno/concept_map.hpp>
#include <dyno/poly.hpp>
using namespace dyno::literals;


struct Concept : decltype(dyno::requires_(
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
  // MESSAGE[dyno::poly::virtual_: Passing a non-poly object as an argument]
  DYNO_CHECK(poly.virtual_("f"_s)(foo) == 111);
}
