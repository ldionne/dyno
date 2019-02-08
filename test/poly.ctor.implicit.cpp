// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include "testing.hpp"

#include <dyno/concept.hpp>
#include <dyno/concept_map.hpp>
#include <dyno/poly.hpp>
using namespace dyno::literals;


// This test makes sure that we can implicitly construct a `dyno::poly` from
// anything that satisfies the concept in the poly. We also check that we can't
// construct from something that does not model the concept.

struct Concept : decltype(dyno::requires_(
  "f"_s = dyno::function<int (dyno::T&)>,
  "g"_s = dyno::function<int (dyno::T&)>
)) { };

struct Foo { };
struct Bar { };

template <>
auto const dyno::concept_map<Concept, Foo> = dyno::make_concept_map(
  "f"_s = [](Foo&) { return 111; },
  "g"_s = [](Foo&) { return 888; }
);

template <>
auto const dyno::concept_map<Concept, Bar> = dyno::make_concept_map(
  "f"_s = [](Foo&) { return 111; }
  // missing `g` to model the concept
);

static_assert(std::is_convertible<Foo, dyno::poly<Concept>>{}, "");
static_assert(!std::is_convertible<Bar, dyno::poly<Concept>>{}, "");

void f(dyno::poly<Concept> poly) {
  DYNO_CHECK(poly.virtual_("f"_s)(poly) == 111);
  DYNO_CHECK(poly.virtual_("g"_s)(poly) == 888);
}

int main() {
  {
    // Implicit move-constructor
    f(Foo{});
  }

  {
    // Implicit copy-constructor
    Foo foo;
    f(foo);
  }
}
