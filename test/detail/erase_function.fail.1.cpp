// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <dyno/detail/dsl.hpp>
#include <dyno/detail/erase_function.hpp>


int main() {
  auto f = [](int& i) -> int& { return i; };
  // Fails because `dyno::T&&` can't be fulfilled by `int&`.
  auto erased = dyno::detail::erase_function<dyno::T&& (int&)>(f);
}
