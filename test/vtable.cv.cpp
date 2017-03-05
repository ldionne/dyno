// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include "testing.hpp"

#include <te/concept.hpp>
#include <te/concept_map.hpp>
#include <te/vtable.hpp>
using namespace te::literals;


//
// This test makes sure that it's possible to provide a concept map function
// that is more cv-qualified than the corresponding function in the concept.
//

struct Concept : decltype(te::requires(
  "f"_s = te::function<int (te::T&)>,
  "g"_s = te::function<int (te::T*)>
)) { };

struct Foo { };

template <>
auto const te::concept_map<Concept, Foo> = te::make_concept_map(
  "f"_s = [](Foo const&) { return 111; },
  "g"_s = [](Foo const*) { return 222; }
);

int main() {
  auto complete = te::complete_concept_map<Concept, Foo>(te::concept_map<Concept, Foo>);
  te::vtable<te::local<te::everything>>::apply<Concept> vtable{complete};

  Foo foo;
  TE_CHECK(vtable["f"_s](&foo) == 111); // erased as a void*
  TE_CHECK(vtable["g"_s](&foo) == 222); // erased as a void*
}
