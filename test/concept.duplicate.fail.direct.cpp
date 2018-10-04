// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <dyno/concept.hpp>
using namespace dyno::literals;


// MESSAGE[dyno::concept: It looks like you have multiple clauses with the same name in your concept definition]
struct Concept : decltype(dyno::requires(
  "f"_dyno = dyno::function<void ()>,
  "f"_dyno = dyno::function<void (int)>
)) { };

int main() { }
