// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include "testing.hpp"

#include <te/concept.hpp>
#include <te/concept_map.hpp>
#include <te/poly.hpp>
using namespace te::literals;


// This test makes sure that `te::poly` allows overriding the concept map used
// for a type at construction time.

struct Concept : decltype(te::requires(
  "f"_s = te::function<int (te::T&)>,
  "g"_s = te::function<int (te::T&)>
)) { };

struct Foo { };

template <>
auto const te::concept_map<Concept, Foo> = te::make_concept_map(
  "f"_s = [](Foo&) { return 111; },
  "g"_s = [](Foo&) { return 888; }
);

int main() {
  {
    Foo foo;
    te::poly<Concept> poly{foo};
    TE_CHECK(poly.virtual_("f"_s)(poly) == 111);
    TE_CHECK(poly.virtual_("g"_s)(poly) == 888);
  }

  {
    Foo foo;
    te::poly<Concept> poly{foo, te::make_concept_map(
      "f"_s = [](Foo&) { return 222; }
    )};
    TE_CHECK(poly.virtual_("f"_s)(poly) == 222);
    TE_CHECK(poly.virtual_("g"_s)(poly) == 888);
  }
}
