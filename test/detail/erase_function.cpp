// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include "../testing.hpp"

#include <te/detail/erase_function.hpp>
#include <te/dsl.hpp>


int main() {
  // erase_function should work with stateless lambdas
  {
    int i = 3;
    auto lambda = [](int& x) { ++x; };
    auto inc = te::detail::erase_function<void (te::T&)>(lambda);
    inc(static_cast<void*>(&i));
    TE_CHECK(i == 4);
  }

  // erase_function should work with stateless function objects
  {
    int i = 3;
    struct lambda { void operator()(int& x) const { ++x; } };
    auto inc = te::detail::erase_function<void (te::T&)>(lambda{});
    inc(static_cast<void*>(&i));
    TE_CHECK(i == 4);
  }

  // an erased function should return the right thing
  {
    int i = 3;
    auto inc = te::detail::erase_function<int (te::T&)>([](int& x) { return ++x; });
    int result = inc(static_cast<void*>(&i));
    TE_CHECK(result == 4);
    TE_CHECK(i == 4);
  }

  // same as before, but the function returns a reference
  {
    int i = 3;
    auto inc = te::detail::erase_function<int& (te::T&)>([](int& x) -> int& { return ++x; });
    int& result = inc(static_cast<void*>(&i));
    TE_CHECK(&result == &i);
    TE_CHECK(result == 4);
    TE_CHECK(i == 4);
  }
}
