// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include "testing.hpp"

#include <te/concept.hpp>
#include <te/concept_map.hpp>
using namespace te::literals;


// This test makes sure that any function defined in a concept map will override
// that of a default concept map.

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
  "f"_s = [](Foo&) { return 555; },
  "g"_s = [](Foo&) { return 333; }
);

int main() {
  Foo foo;
  TE_CHECK(te::concept_map<Concept, Foo>["f"_s](foo) == 555);
  TE_CHECK(te::concept_map<Concept, Foo>["g"_s](foo) == 333);
}
