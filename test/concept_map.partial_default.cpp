// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include "testing.hpp"

#include <dyno/concept.hpp>
#include <dyno/concept_map.hpp>
using namespace dyno::literals;


struct Concept : decltype(dyno::requires(
  "f"_dyno = dyno::function<int (dyno::T&)>,
  "g"_dyno = dyno::function<int (dyno::T&)>
)) { };

template <typename T>
auto const dyno::default_concept_map<Concept, T> = dyno::make_concept_map(
  "f"_dyno = [](T&) { return 222; }
);

struct Foo { };
template <>
auto const dyno::concept_map<Concept, Foo> = dyno::make_concept_map(
  "g"_dyno = [](Foo&) { return 333; }
);

struct Bar { };
template <>
auto const dyno::concept_map<Concept, Bar> = dyno::make_concept_map(
  "f"_dyno = [](Bar&) { return 444; },
  "g"_dyno = [](Bar&) { return 555; }
);

int main() {
  {
    Foo foo;
    auto complete = dyno::complete_concept_map<Concept, Foo>(dyno::concept_map<Concept, Foo>);
    DYNO_CHECK(complete["f"_dyno](foo) == 222);
    DYNO_CHECK(complete["g"_dyno](foo) == 333);
  }

  {
    Bar bar;
    auto complete = dyno::complete_concept_map<Concept, Bar>(dyno::concept_map<Concept, Bar>);
    DYNO_CHECK(complete["f"_dyno](bar) == 444);
    DYNO_CHECK(complete["g"_dyno](bar) == 555);
  }
}
