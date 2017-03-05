// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include "../test/testing.hpp"

#include <te.hpp>

#include <string>
#include <utility>
using namespace te::literals;


//
// Example of creating a naive equivalent to `std::function` using the library.
//

template <typename Signature>
struct Callable;

template <typename R, typename ...Args>
struct Callable<R(Args...)> : decltype(te::requires(
  "call"_s = te::function<R (te::T const&, Args...)>
)) { };

template <typename R, typename ...Args, typename F>
auto const te::default_concept_map<Callable<R(Args...)>, F> = te::make_concept_map(
  "call"_s = [](F const& f, Args ...args) -> R {
    return f(std::forward<Args>(args)...);
  }
);

template <typename Signature>
struct function;

template <typename R, typename ...Args>
struct function<R(Args...)> {
  template <typename F>
  function(F&& f) : poly_{std::forward<F>(f)} { }

  R operator()(Args ...args) const {
    return poly_.virtual_("call"_s)(poly_, std::forward<Args>(args)...);
  }

private:
  te::poly<Callable<R(Args...)>> poly_;
};

int main() {
  function<int(std::string const&)> size = [](std::string const& s) {
    return s.size();
  };

  TE_CHECK(size("") == 0);
  TE_CHECK(size("a") == 1);
  TE_CHECK(size("ab") == 2);
  TE_CHECK(size("abc") == 3);
  TE_CHECK(size("abcdef") == 6);
}
