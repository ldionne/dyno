// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <dyno/detail/dsl.hpp>

#include <type_traits>


// Only bring in `dyno::literals` after using the macro to validate it does
// not use it under the hood.
static auto foobar = DYNO_STRING("foobar");

using namespace dyno::literals;
static_assert(std::is_same<decltype(foobar), decltype("foobar"_s)>{}, "");

int main() {
  (void)foobar;
}
