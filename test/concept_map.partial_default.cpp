// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include "testing.hpp"

#include <te/concept.hpp>
#include <te/concept_map.hpp>
using namespace te::literals;


struct Concept : decltype(te::requires(
  "f"_s = te::function<int (te::T&)>,
  "g"_s = te::function<int (te::T&)>
)) { };

template <typename T>
static auto const te::default_concept_map<Concept, T> = te::make_default_concept_map<Concept, T>(
  "f"_s = [](T&) { return 222; }
);

struct Foo { };
template <>
auto const te::concept_map<Concept, Foo> = te::make_concept_map<Concept, Foo>(
  "g"_s = [](Foo&) { return 333; }
);

struct Bar { };
template <>
auto const te::concept_map<Concept, Bar> = te::make_concept_map<Concept, Bar>(
  "f"_s = [](Bar&) { return 444; },
  "g"_s = [](Bar&) { return 555; }
);

int main() {
  Foo foo;
  TE_CHECK(te::concept_map<Concept, Foo>["f"_s](foo) == 222);
  TE_CHECK(te::concept_map<Concept, Foo>["g"_s](foo) == 333);

  Bar bar;
  TE_CHECK(te::concept_map<Concept, Bar>["f"_s](bar) == 444);
  TE_CHECK(te::concept_map<Concept, Bar>["g"_s](bar) == 555);
}
