// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <dyno/concept.hpp>
#include <dyno/poly.hpp>
using namespace dyno::literals;


// This test makes sure that the size of a `dyno::poly` with a remote storage
// policy and a remote vtable is the size of 2 pointers. There was once a bug
// where the size was more than that.

struct Concept : decltype(dyno::requires_(
  "f"_s = dyno::function<void (dyno::T&)>
)) { };

using Storage = dyno::remote_storage;
using VTable = dyno::vtable<dyno::remote<dyno::everything>>;
using Poly = dyno::poly<Concept, Storage, VTable>;
static_assert(sizeof(Poly) == 2 * sizeof(void*));

int main() { }
