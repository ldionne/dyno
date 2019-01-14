// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <type_traits>
#include <dyno/concept.hpp>
#include <dyno/poly.hpp>
#include <dyno/storage.hpp>
#include "testing.hpp"

struct Concept : decltype(dyno::requires()) { };
struct Foo { };

int main() {
  using P = dyno::poly<Concept, dyno::non_owning_storage>;
  static_assert(std::is_trivially_copyable<P>{}, "!");

  Foo f;
  P p1(f);
  DYNO_CHECK(p1.unsafe_get<Foo>() == &f);
  P p2 = p1; 
  DYNO_CHECK(p1.unsafe_get<Foo>() == &f);
  DYNO_CHECK(p2.unsafe_get<Foo>() == &f);
  P p3 = std::move(p1);
  DYNO_CHECK(p1.unsafe_get<Foo>() == &f);
  DYNO_CHECK(p3.unsafe_get<Foo>() == &f);
}
