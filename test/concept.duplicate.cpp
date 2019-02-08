// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <dyno/concept.hpp>
using namespace dyno::literals;


// This test makes sure that we don't issue a "duplicate clause error" when a
// seemingly duplicate function is in fact defined in a concept that is common
// to two concepts that we derive from.

struct CommonBase : decltype(dyno::requires_(
  "f"_s = dyno::function<void ()>
)) { };

struct Base1 : decltype(dyno::requires_(
  CommonBase{}
)) { };

struct Base2 : decltype(dyno::requires_(
  CommonBase{}
)) { };

struct Derived : decltype(dyno::requires_(
  Base1{},
  Base2{}
)) { };

int main() { }
