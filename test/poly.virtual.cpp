// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include "testing.hpp"

#include <dyno/concept.hpp>
#include <dyno/concept_map.hpp>
#include <dyno/poly.hpp>
using namespace dyno::literals;


// This test makes sure that `dyno::poly` does the right thing when calling
// virtual functions with placeholders. The expected behavior is that we
// pass a `dyno::poly`, and it gets translated to a `void*` internally.

struct Concept : decltype(dyno::requires(
  "a"_dyno = dyno::function<int (dyno::T&)>,
  "b"_dyno = dyno::function<int (dyno::T&&)>,
  "c"_dyno = dyno::function<int (dyno::T*)>,
  "d"_dyno = dyno::function<int (dyno::T const&)>,
  "e"_dyno = dyno::function<int (dyno::T const*)>
)) { };

struct Foo { };

template <>
auto const dyno::concept_map<Concept, Foo> = dyno::make_concept_map(
  "a"_dyno = [](Foo&) { return 111; },
  "b"_dyno = [](Foo&&) { return 222; },
  "c"_dyno = [](Foo*) { return 333; },
  "d"_dyno = [](Foo const&) { return 444; },
  "e"_dyno = [](Foo const*) { return 555; }
);

int main() {
  {
    Foo foo;
    dyno::poly<Concept> poly{foo};
    DYNO_CHECK(poly.virtual_("a"_dyno)(poly) == 111);
  }
  {
    Foo foo;
    dyno::poly<Concept> poly{foo};
    DYNO_CHECK(poly.virtual_("b"_dyno)(std::move(poly)) == 222);
  }
  {
    Foo foo;
    dyno::poly<Concept> poly{foo};
    DYNO_CHECK(poly.virtual_("c"_dyno)(&poly) == 333);
  }
  {
    Foo foo;
    dyno::poly<Concept> const poly{foo};
    DYNO_CHECK(poly.virtual_("d"_dyno)(poly) == 444);
  }
  {
    Foo foo;
    dyno::poly<Concept> const poly{foo};
    DYNO_CHECK(poly.virtual_("e"_dyno)(&poly) == 555);
  }
}
