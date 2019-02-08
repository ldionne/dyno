// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include "testing.hpp"

#include <dyno/builtin.hpp>
#include <dyno/poly.hpp>

#include <typeinfo>
using namespace dyno::literals;


// This test makes sure that we do not double-wrap `poly`s due to the implicit
// constructors, despite the fact that the poly models the concept that it
// itself requires (and hence would be a valid candidate for the implicit
// converting constructors).

struct Foo { };

struct Concept
  : decltype(dyno::requires_(dyno::CopyConstructible{}, dyno::TypeId{}))
{ };

int main() {
  Foo foo;
  dyno::poly<Concept> poly{foo};

  // We expect the objects below to be a copy of the above `poly` (and thus
  // `poly`s holding a `Foo`), not `poly`s holding a `poly`.
  dyno::poly<Concept> explicit_copy{poly};
  DYNO_CHECK(explicit_copy.virtual_("typeid"_s)() == typeid(Foo));

  dyno::poly<Concept> implicit_copy = poly;
  DYNO_CHECK(implicit_copy.virtual_("typeid"_s)() == typeid(Foo));
}
