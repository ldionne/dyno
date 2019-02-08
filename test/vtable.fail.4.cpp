// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <dyno/concept.hpp>
#include <dyno/concept_map.hpp>
#include <dyno/vtable.hpp>
using namespace dyno::literals;


struct Concept : decltype(dyno::requires_(
  "f"_s = dyno::function<void (dyno::T const&)>
)) { };

struct Foo { };

template <>
auto const dyno::concept_map<Concept, Foo> = dyno::make_concept_map(
  "f"_s = [](Foo&) { }
);

int main() {
  auto complete = dyno::complete_concept_map<Concept, Foo>(dyno::concept_map<Concept, Foo>);

  // MESSAGE[Some functions specified in this selector are not part of the concept to which the selector was applied]
  dyno::vtable<
    dyno::local<dyno::only<decltype("nonexistent"_s)>>,
    dyno::remote<dyno::everything_else>
  >::apply<Concept> vtable{complete};
}
