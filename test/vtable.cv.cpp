// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include "testing.hpp"

#include <dyno/concept.hpp>
#include <dyno/concept_map.hpp>
#include <dyno/vtable.hpp>
using namespace dyno::literals;


//
// This test makes sure that it's possible to provide a concept map function
// that is more cv-qualified than the corresponding function in the concept.
//

struct Concept : decltype(dyno::requires(
  "f"_s = dyno::function<int (dyno::T&)>,
  "g"_s = dyno::function<int (dyno::T*)>
)) { };

struct Foo { };

template <>
auto const dyno::concept_map<Concept, Foo> = dyno::make_concept_map(
  "f"_s = [](Foo const&) { return 111; },
  "g"_s = [](Foo const*) { return 222; }
);

int main() {
  auto complete = dyno::complete_concept_map<Concept, Foo>(dyno::concept_map<Concept, Foo>);
  dyno::vtable<dyno::local<dyno::everything>>::apply<Concept> vtable{complete};

  Foo foo;
  DYNO_CHECK(vtable["f"_s](&foo) == 111); // erased as a void*
  DYNO_CHECK(vtable["g"_s](&foo) == 222); // erased as a void*
}
