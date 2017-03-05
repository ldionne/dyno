// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <te/concept.hpp>
#include <te/concept_map.hpp>
#include <te/vtable.hpp>
using namespace te::literals;


struct Concept : decltype(te::requires(
  "f"_s = te::function<void (te::T const&)>
)) { };

struct Foo { };

template <>
auto const te::concept_map<Concept, Foo> = te::make_concept_map(
  "f"_s = [](Foo&) { }
);

int main() {
  auto complete = te::complete_concept_map<Concept, Foo>(te::concept_map<Concept, Foo>);

  // When populating the vtable with that concept map, we'll notice the mismatch
  // between `Foo&` and `te::T const&`.
  te::vtable<te::local<te::everything>>::apply<Concept> vtable{complete};
}
