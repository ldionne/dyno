// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <dyno/concept.hpp>
#include <dyno/poly.hpp>
#include <dyno/storage.hpp>


// This test makes sure that we get a compiler error if we try to construct a
// `dyno::poly` using non-owning storage from a temporary.

struct Concept : decltype(dyno::requires_()) { };

struct Foo { };

int main() {
  dyno::poly<Concept, dyno::non_owning_storage> poly{Foo{}};
}
