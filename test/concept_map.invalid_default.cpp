// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include "testing.hpp"

#include <dyno/concept.hpp>
#include <dyno/concept_map.hpp>
using namespace dyno::literals;


struct Concept : decltype(dyno::requires_(
  "f"_s = dyno::function<int (dyno::T&)>,
  "g"_s = dyno::function<int (dyno::T&)>
)) { };

// Since the definition of `f` would be invalid, we need to use a generic
// lambda to delay the instantiation of the body. This test makes sure that
// this "workaround" works.

template <typename T>
auto const dyno::default_concept_map<Concept, T> = dyno::make_concept_map(
  "f"_s = [](auto& t) { t.invalid(); return 222; },
  "g"_s = [](auto& t) { t.valid(); return 333; }
);

struct Foo {
  void invalid() = delete;
  void valid() { }
};

template <>
auto const dyno::concept_map<Concept, Foo> = dyno::make_concept_map(
  "f"_s = [](Foo&) { return 444; }
);

int main() {
  Foo foo;
  auto complete = dyno::complete_concept_map<Concept, Foo>(dyno::concept_map<Concept, Foo>);
  DYNO_CHECK(complete["f"_s](foo) == 444);
  DYNO_CHECK(complete["g"_s](foo) == 333);
}
