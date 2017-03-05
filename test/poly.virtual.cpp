// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include "testing.hpp"

#include <te/concept.hpp>
#include <te/concept_map.hpp>
#include <te/poly.hpp>
using namespace te::literals;


// This test makes sure that `te::poly` does the right thing when calling
// virtual functions with placeholders. The expected behavior is that we
// pass a `te::poly`, and it gets translated to a `void*` internally.

struct Concept : decltype(te::requires(
  "a"_s = te::function<int (te::T&)>,
  "b"_s = te::function<int (te::T&&)>,
  "c"_s = te::function<int (te::T*)>,
  "d"_s = te::function<int (te::T const&)>,
  "e"_s = te::function<int (te::T const*)>
)) { };

struct Foo { };

template <>
auto const te::concept_map<Concept, Foo> = te::make_concept_map(
  "a"_s = [](Foo&) { return 111; },
  "b"_s = [](Foo&&) { return 222; },
  "c"_s = [](Foo*) { return 333; },
  "d"_s = [](Foo const&) { return 444; },
  "e"_s = [](Foo const*) { return 555; }
);

int main() {
  {
    Foo foo;
    te::poly<Concept> poly{foo};
    TE_CHECK(poly.virtual_("a"_s)(poly) == 111);
  }
  {
    Foo foo;
    te::poly<Concept> poly{foo};
    TE_CHECK(poly.virtual_("b"_s)(std::move(poly)) == 222);
  }
  {
    Foo foo;
    te::poly<Concept> poly{foo};
    TE_CHECK(poly.virtual_("c"_s)(&poly) == 333);
  }
  {
    Foo foo;
    te::poly<Concept> const poly{foo};
    TE_CHECK(poly.virtual_("d"_s)(poly) == 444);
  }
  {
    Foo foo;
    te::poly<Concept> const poly{foo};
    TE_CHECK(poly.virtual_("e"_s)(&poly) == 555);
  }
}
