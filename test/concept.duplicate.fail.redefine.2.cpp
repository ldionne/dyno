// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <dyno/concept.hpp>
using namespace dyno::literals;


struct Base0 : decltype(dyno::requires(
  "f"_dyno = dyno::function<void ()>,
  "g"_dyno = dyno::function<void ()>
)) { };

struct Base1 : decltype(dyno::requires(
  Base0{}
)) { };

// MESSAGE[dyno::concept: It looks like you are redefining a clause that is already defined in a base concept]
struct Derived : decltype(dyno::requires(
  Base1{},
  "f"_dyno = dyno::function<void ()>
)) { };

int main() { }
