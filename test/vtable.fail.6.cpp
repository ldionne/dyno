// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <dyno/concept.hpp>
#include <dyno/concept_map.hpp>
#include <dyno/vtable.hpp>
using namespace dyno::literals;


struct Fooable : decltype(dyno::requires_(
  "f"_s = dyno::function<void (dyno::T&)>
)) { };

template <>
auto dyno::concept_map<Fooable, int> = dyno::make_concept_map(
  "f"_s = [](int&) { }
);

int main() {
  dyno::vtable<dyno::local<dyno::everything>>::apply<Fooable> vtable{
    dyno::complete_concept_map<Fooable, int>(dyno::concept_map<Fooable, int>)
  };

  // MESSAGE[Request for a virtual function that is not in the vtable]
  auto fail = vtable["inexistent"_s];
}
