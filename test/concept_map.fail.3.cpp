// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <dyno/concept.hpp>
#include <dyno/concept_map.hpp>
using namespace dyno::literals;


struct Fooable : decltype(dyno::requires_(
  "foo"_s = dyno::function<void (dyno::T&)>,
  "bar"_s = dyno::function<void (dyno::T&)>
)) { };

template <>
auto const dyno::concept_map<Fooable, int> = dyno::make_concept_map(
  "foo"_s = [](int&) { }
);

// MESSAGE[Incomplete definition of your concept map]
auto const& complete = dyno::complete_concept_map<Fooable, int>(dyno::concept_map<Fooable, int>);

int main() { }
