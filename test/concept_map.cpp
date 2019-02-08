// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include "testing.hpp"

#include <dyno/concept.hpp>
#include <dyno/concept_map.hpp>
using namespace dyno::literals;


struct A : decltype(dyno::requires_(
  "f"_s = dyno::function<int (dyno::T&)>
)) { };

struct B : decltype(dyno::requires_(
  A{},
  "g"_s = dyno::function<int (dyno::T&)>
)) { };

struct C : decltype(dyno::requires_(B{})) { };

struct Foo { };

template <>
auto const dyno::concept_map<A, Foo> = dyno::make_concept_map(
  "f"_s = [](Foo&) { return 222; }
);

template <>
auto const dyno::concept_map<B, Foo> = dyno::make_concept_map(
  "g"_s = [](Foo&) { return 333; }
);

int main() {
  Foo foo;

  {
    auto complete = dyno::complete_concept_map<C, Foo>(dyno::concept_map<C, Foo>);
    DYNO_CHECK(complete["f"_s](foo) == 222);
    DYNO_CHECK(complete["g"_s](foo) == 333);
  }
  {
    auto complete = dyno::complete_concept_map<B, Foo>(dyno::concept_map<B, Foo>);
    DYNO_CHECK(complete["f"_s](foo) == 222);
    DYNO_CHECK(complete["g"_s](foo) == 333);
  }
  {
    auto complete = dyno::complete_concept_map<A, Foo>(dyno::concept_map<A, Foo>);
    DYNO_CHECK(complete["f"_s](foo) == 222);
  }
}
