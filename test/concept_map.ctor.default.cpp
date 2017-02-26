// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <te/concept.hpp>
#include <te/concept_map.hpp>

#include <type_traits>
using namespace te::literals;


struct A : decltype(te::requires(
  "f"_s = te::function<void (te::T&)>
)) { };

struct Foo { };

auto map = te::complete_concept_map<A, Foo>(te::make_concept_map("f"_s = [](int&) { }));

static_assert(std::is_default_constructible<decltype(map)>{}, "");

int main() { }
