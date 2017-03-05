// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <te/detail/dsl.hpp>
#include <te/detail/erase_function.hpp>


int main() {
  auto f = [](int& i) { };
  // Fails because `te::T const&` can't be fulfilled by `int&`.
  auto erased = te::detail::erase_function<void (te::T const&)>(f);
}
