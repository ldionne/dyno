// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <dyno/concept.hpp>
#include <dyno/vtable.hpp>

#include <type_traits>
using namespace dyno::literals;


// This test makes sure that we compress empty vtable as we apply selectors.
// This is especially important for ensuring that vtables are as small and
// easy to optimize as possible.

struct Concept : decltype(dyno::requires_(
  "f"_s = dyno::function<void (dyno::T const&)>
)) { };

struct Foo { };

using GeneratedVTable = dyno::vtable<
  dyno::local<dyno::only<>>, // matches nothing; should be compressed
  dyno::remote<dyno::everything_else>
>::apply<Concept>;

using RemoteOnly = dyno::remote_vtable<dyno::local_vtable<
  decltype("f"_s = dyno::function<void (dyno::T const&)>)
>>;

static_assert(std::is_same<GeneratedVTable, RemoteOnly>{});

int main() { }
