// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <te/detail/dsl.hpp>
#include <te/detail/erase_function.hpp>


int main() {
  auto f = [](int& i) -> int& { return i; };
  auto erased = te::detail::erase_function<te::T&& (int&)>(f);
}
