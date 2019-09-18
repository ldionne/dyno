// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include "testing.hpp"

#include <dyno/concept.hpp>
#include <dyno/concept_map.hpp>
#include <dyno/poly.hpp>
using namespace dyno::literals;


// This test makes sure that `dyno::poly::operator->*` is equivalent to
// `dyno::poly::virtual_`.

struct Concept : decltype(dyno::requires_(
  "f"_s = dyno::function<int (dyno::T&)>,
  "g"_s = dyno::function<double (dyno::T&, double)>,
  "h"_s = dyno::function<double (dyno::T const&, double)>
)) { };

struct Foo { };

template <>
auto const dyno::concept_map<Concept, Foo> = dyno::make_concept_map(
  "f"_s = [](Foo&) { return 111; },
  "g"_s = [](Foo&, double d) { return d; },
  "h"_s = [](Foo const&, double d) { return d; }
);

int main() {
  Foo foo;
  dyno::poly<Concept> poly{foo};
  DYNO_CHECK(poly->*"f"_s() == 111);
  DYNO_CHECK(poly->*"g"_s(3.3) == 3.3);

  dyno::poly<Concept> const& const_ref = poly;
  DYNO_CHECK(const_ref->*"h"_s(3.3) == 3.3);
}
