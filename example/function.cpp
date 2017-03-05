// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include "../test/testing.hpp"

#include <te.hpp>

#include <functional>
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
  template <typename F = R(Args...)>
  function(F&& f) : poly_{std::forward<F>(f)} { }

  R operator()(Args ...args) const {
    return poly_.virtual_("call"_s)(poly_, std::forward<Args>(args)...);
  }

private:
  te::poly<Callable<R(Args...)>> poly_;
};


//
// Tests
//

struct ToStringAdd {
  ToStringAdd(int num) : num_(num) { }
  std::string to_string_add(int i) const { return std::to_string(num_ + i); }
  int num_;
};

struct ToString {
  std::string operator()(int i) const { return std::to_string(i); }
};

int main() {
  // store a free function
  {
    function<std::string(int)> tostring = std::to_string;
    TE_CHECK(tostring(1) == "1");
    TE_CHECK(tostring(2) == "2");
    TE_CHECK(tostring(3) == "3");
    TE_CHECK(tostring(-10) == "-10");
  }

  // store a lambda
  {
    function<int(std::string const&)> size = [](std::string const& s) {
      return s.size();
    };

    TE_CHECK(size("") == 0);
    TE_CHECK(size("a") == 1);
    TE_CHECK(size("ab") == 2);
    TE_CHECK(size("abc") == 3);
    TE_CHECK(size("abcdef") == 6);
  }

  // store the result of a call to std::bind
  {
    function<std::string()> tostring = std::bind(static_cast<std::string(*)(int)>(std::to_string), 31337);
    TE_CHECK(tostring() == "31337");
  }

  // store a call to a member function and object
  {
    ToStringAdd const adder{314159};
    function<std::string(int)> f = std::bind(&ToStringAdd::to_string_add, adder, std::placeholders::_1);
    TE_CHECK(f(1) == "314160");
    TE_CHECK(f(2) == "314161");
    TE_CHECK(f(3) == "314162");
    TE_CHECK(f(-10) == "314149");
  }

  // store a call to a member function and object ptr
  {
    ToStringAdd const adder{314159};
    function<std::string(int)> f = std::bind(&ToStringAdd::to_string_add, &adder, std::placeholders::_1);
    TE_CHECK(f(1) == "314160");
    TE_CHECK(f(2) == "314161");
    TE_CHECK(f(3) == "314162");
    TE_CHECK(f(-10) == "314149");
  }

  // store a call to a function object
  {
    function<std::string(int)> tostring = ToString{};
    TE_CHECK(tostring(1) == "1");
    TE_CHECK(tostring(2) == "2");
    TE_CHECK(tostring(3) == "3");
    TE_CHECK(tostring(18) == "18");
  }
}
