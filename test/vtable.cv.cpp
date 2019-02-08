// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include "testing.hpp"

#include <dyno/concept.hpp>
#include <dyno/concept_map.hpp>
#include <dyno/vtable.hpp>
using namespace dyno::literals;


//
// This test makes sure that it's possible to provide a concept map function
// that is more cv-qualified than the corresponding function in the concept.
//

struct Concept : decltype(dyno::requires_(
  "f1"_s = dyno::function<int (dyno::T&)>,
  "f2"_s = dyno::function<int (dyno::T*)>,
  "f3"_s = dyno::function<int (dyno::T&)>,
  "f4"_s = dyno::function<int (dyno::T*)>,
  "f5"_s = dyno::function<int (dyno::T&)>,
  "f6"_s = dyno::function<int (dyno::T*)>,
  "f7"_s = dyno::function<int (dyno::T&, int&)>
)) { };

struct Foo { };

template <>
auto const dyno::concept_map<Concept, Foo> = dyno::make_concept_map(
  "f1"_s = [](Foo const&) { return 111; },
  "f2"_s = [](Foo const*) { return 222; },
  "f3"_s = [](Foo volatile&) { return 333; },
  "f4"_s = [](Foo volatile*) { return 444; },
  "f5"_s = [](Foo const volatile&) { return 555; },
  "f6"_s = [](Foo const volatile*) { return 666; },
  "f7"_s = [](Foo&, int const&) { return 777; }
);

int main() {
  auto complete = dyno::complete_concept_map<Concept, Foo>(dyno::concept_map<Concept, Foo>);
  dyno::vtable<dyno::local<dyno::everything>>::apply<Concept> vtable{complete};

  Foo foo;
  int i = 0;
  DYNO_CHECK(vtable["f1"_s](&foo) == 111); // erased as a void*
  DYNO_CHECK(vtable["f2"_s](&foo) == 222); // erased as a void*
  DYNO_CHECK(vtable["f3"_s](&foo) == 333); // erased as a void*
  DYNO_CHECK(vtable["f4"_s](&foo) == 444); // erased as a void*
  DYNO_CHECK(vtable["f5"_s](&foo) == 555); // erased as a void*
  DYNO_CHECK(vtable["f6"_s](&foo) == 666); // erased as a void*
  DYNO_CHECK(vtable["f7"_s](&foo, i) == 777);
}
