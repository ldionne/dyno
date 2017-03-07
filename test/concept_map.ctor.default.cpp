// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <dyno/concept.hpp>
#include <dyno/concept_map.hpp>

#include <type_traits>
using namespace dyno::literals;


struct A : decltype(dyno::requires(
  "f"_s = dyno::function<void (dyno::T&)>
)) { };

struct Foo { };

auto map = dyno::complete_concept_map<A, Foo>(dyno::make_concept_map("f"_s = [](int&) { }));

static_assert(std::is_default_constructible<decltype(map)>{}, "");

int main() { }
