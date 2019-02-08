// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include "testing.hpp"

#include <dyno/concept.hpp>
#include <dyno/concept_map.hpp>
#include <dyno/poly.hpp>
using namespace dyno::literals;


// This test makes sure that `dyno::poly` allows overriding the concept map used
// for a type at construction time.

struct Concept : decltype(dyno::requires_(
  "f"_s = dyno::function<int (dyno::T&)>,
  "g"_s = dyno::function<int (dyno::T&)>
)) { };

struct Foo { };

template <>
auto const dyno::concept_map<Concept, Foo> = dyno::make_concept_map(
  "f"_s = [](Foo&) { return 111; },
  "g"_s = [](Foo&) { return 888; }
);

int main() {
  {
    Foo foo;
    dyno::poly<Concept> poly{foo};
    DYNO_CHECK(poly.virtual_("f"_s)(poly) == 111);
    DYNO_CHECK(poly.virtual_("g"_s)(poly) == 888);
  }

  {
    Foo foo;
    dyno::poly<Concept> poly{foo, dyno::make_concept_map(
      "f"_s = [](Foo&) { return 222; }
    )};
    DYNO_CHECK(poly.virtual_("f"_s)(poly) == 222);
    DYNO_CHECK(poly.virtual_("g"_s)(poly) == 888);
  }
}
