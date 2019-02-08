// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <dyno/concept.hpp>
#include <dyno/concept_map.hpp>
using namespace dyno::literals;


struct Concept : decltype(dyno::requires_(
  "f"_s = dyno::function<void ()>
)) { };

// MESSAGE[dyno::make_concept_map: It looks like you have multiple entries with the same name in your concept map]
template <>
auto dyno::concept_map<Concept, int> = dyno::make_concept_map(
  "f"_s = []() { },
  "f"_s = [](int) { }
);

int main() { }
