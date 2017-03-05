// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include "../testing.hpp"

#include <te/concept.hpp>
#include <te/detail/erase_function.hpp>


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

  // erase_function should work when returning a placeholder
  {
    int i = 3;
    auto inc = te::detail::erase_function<te::T& (te::T&)>([](int& x) -> int& { return ++x; });
    void* result = inc(static_cast<void*>(&i));
    int& casted = *static_cast<int*>(result);
    TE_CHECK(&casted == &i);
    TE_CHECK(casted == 4);
    TE_CHECK(i == 4);
  }

  // erase_function should be able to erase a function that is more cv-qualified
  {
    {
      int i = 3;
      auto f = te::detail::erase_function<int (te::T&)>([](int const& x) { return x; });
      int result = f(static_cast<void*>(&i));
      TE_CHECK(result == 3);
    }
    {
      int i = 3;
      auto f = te::detail::erase_function<int (te::T*)>([](int const* x) { return *x; });
      int result = f(static_cast<void*>(&i));
      TE_CHECK(result == 3);
    }
  }
}
