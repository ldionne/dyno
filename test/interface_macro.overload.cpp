// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include "testing.hpp"

#include <dyno/interface_macro.hpp>


DYNO_INTERFACE(Concept,
  (function, int(int) const),
  (function, int(double) const),
  (function, int(double))
);

struct Model1 {
  int function(int) const { return 1; }
  int function(double) const { return 2; }
  int function(double) { return 3; }
};

struct Model2 {
  int function(int) const { return 91; }
  int function(double) const { return 92; }
  int function(double) { return 93; }
};

int main() {
  Concept c1{m1};
  DYNO_CHECK(c1.function(int{}) == 1);
  DYNO_CHECK(static_cast<Concept const&>(c1).function(double{}) == 2);
  DYNO_CHECK(c1.function(double{}) == 3);

  Concept c2{m2};
  DYNO_CHECK(c2.function(int{}) == 91);
  DYNO_CHECK(static_cast<Concept const&>(c2).function(double{}) == 92);
  DYNO_CHECK(c2.function(double{}) == 93);
}
