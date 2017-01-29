// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <te/concept.hpp>
#include <te/concept_map.hpp>
#include <te/dsl.hpp>
#include <te/vtable.hpp>
using namespace te::literals;


struct Fooable : decltype(te::requires(
  "foo"_s = te::function<void (te::T&)>
)) { };

template <>
auto te::concept_map<Fooable, int> = te::make_concept_map<Fooable, int>(
  "foo"_s = [](int& x) { ++x; }
);

int main() {
  te::vtable<Fooable> vtable{te::concept_map<Fooable, int>};

  // "bar" is not defined in the vtable
  auto bar = vtable["bar"_s];
}
