// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include "testing.hpp"

#include <dyno/concept.hpp>
#include <dyno/concept_map.hpp>
#include <dyno/poly.hpp>
using namespace dyno::literals;


// This test makes sure that `dyno::poly` adds an implicit first argument
// when a function in a concept is defined using `method` instead of
// `function`.

struct Concept : decltype(dyno::requires(
  "a"_dyno = dyno::method<int (int)>,
  "b"_dyno = dyno::method<int (int) &>,
  "c"_dyno = dyno::method<int (int) &&>,
  "d"_dyno = dyno::method<int (int) const>,
  "e"_dyno = dyno::method<int (int) const&>
)) { };

struct Foo { };

template <>
auto const dyno::concept_map<Concept, Foo> = dyno::make_concept_map(
  "a"_dyno = [](Foo&, int) { return 111; },
  "b"_dyno = [](Foo&, int) { return 222; },
  "c"_dyno = [](Foo&&, int) { return 333; },
  "d"_dyno = [](Foo const&, int) { return 444; },
  "e"_dyno = [](Foo const&, int) { return 555; }
);

int main() {
  {
    Foo foo;
    dyno::poly<Concept> poly{foo};
    DYNO_CHECK(poly.virtual_("a"_dyno)(int{}) == 111);
  }
  {
    Foo foo;
    dyno::poly<Concept> poly{foo};
    DYNO_CHECK(poly.virtual_("b"_dyno)(int{}) == 222);
  }
  {
    Foo foo;
    dyno::poly<Concept> poly{foo};
    DYNO_CHECK(std::move(poly).virtual_("c"_dyno)(int{}) == 333);
  }
  {
    Foo foo;
    dyno::poly<Concept> const poly{foo};
    DYNO_CHECK(poly.virtual_("d"_dyno)(int{}) == 444);
  }
  {
    Foo foo;
    dyno::poly<Concept> const poly{foo};
    DYNO_CHECK(poly.virtual_("e"_dyno)(int{}) == 555);
  }
}
