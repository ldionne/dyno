// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <te/concept.hpp>
#include <te/concept_map.hpp>
using namespace te::literals;


struct Fooable : decltype(te::requires(
  "foo"_s = te::function<void (te::T&)>
)) { };

int main() {
  // MESSAGE[Incomplete definition of your concept map]
  auto const& map = te::complete_concept_map<Fooable, int>(te::concept_map<Fooable, int>);
}
