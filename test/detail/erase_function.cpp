// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include "../testing.hpp"

#include <dyno/concept.hpp>
#include <dyno/detail/erase_function.hpp>

#include <utility>


int main() {
  // erase_function should work with stateless lambdas
  {
    int i = 3;
    auto lambda = [](int& x) { ++x; };
    auto inc = dyno::detail::erase_function<void (dyno::T&)>(lambda);
    inc(static_cast<void*>(&i));
    DYNO_CHECK(i == 4);
  }

  // erase_function should work with stateless function objects
  {
    int i = 3;
    struct lambda { void operator()(int& x) const { ++x; } };
    auto inc = dyno::detail::erase_function<void (dyno::T&)>(lambda{});
    inc(static_cast<void*>(&i));
    DYNO_CHECK(i == 4);
  }

  // an erased function should return the right thing
  {
    int i = 3;
    auto inc = dyno::detail::erase_function<int (dyno::T&)>([](int& x) { return ++x; });
    int result = inc(static_cast<void*>(&i));
    DYNO_CHECK(result == 4);
    DYNO_CHECK(i == 4);
  }

  // same as before, but the function returns a reference
  {
    int i = 3;
    auto inc = dyno::detail::erase_function<int& (dyno::T&)>([](int& x) -> int& { return ++x; });
    int& result = inc(static_cast<void*>(&i));
    DYNO_CHECK(&result == &i);
    DYNO_CHECK(result == 4);
    DYNO_CHECK(i == 4);
  }

  // erase_function should work when returning a placeholder
  {
    int i = 3;
    auto inc = dyno::detail::erase_function<dyno::T& (dyno::T&)>([](int& x) -> int& { return ++x; });
    void* result = inc(static_cast<void*>(&i));
    int& casted = *static_cast<int*>(result);
    DYNO_CHECK(&casted == &i);
    DYNO_CHECK(casted == 4);
    DYNO_CHECK(i == 4);
  }

  // erase_function should be able to erase a function that is more cv-qualified
  {
    {
      int i = 3;
      auto f = dyno::detail::erase_function<int (dyno::T&)>([](int const& x) { return x; });
      int result = f(static_cast<void*>(&i));
      DYNO_CHECK(result == 3);
    }
    {
      int i = 3;
      auto f = dyno::detail::erase_function<int (dyno::T*)>([](int const* x) { return *x; });
      int result = f(static_cast<void*>(&i));
      DYNO_CHECK(result == 3);
    }
  }

  // erase_function should be able to erase a function returning an rvalue reference
  {
    static int i = 3;
    auto f = dyno::detail::erase_function<dyno::T&& ()>([]() -> int&& {
      return std::move(i);
    });
    void* result = f();
    int* casted = static_cast<int*>(result);
    DYNO_CHECK(casted == &i);
    DYNO_CHECK(*casted == 3);
  }
}
