// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include "../test/testing.hpp"

#include <dyno.hpp>

#include <cstddef>
#include <functional>
#include <string>
#include <utility>
using namespace dyno::literals;


//
// Example of creating a naive equivalent to `std::function` using the library.
//

template <typename Signature>
struct Callable;

template <typename R, typename ...Args>
struct Callable<R(Args...)> : decltype(dyno::requires_(
  dyno::CopyConstructible{},
  dyno::MoveConstructible{},
  dyno::Destructible{},
  "call"_s = dyno::function<R (dyno::T const&, Args...)>
)) { };

template <typename R, typename ...Args, typename F>
auto const dyno::default_concept_map<Callable<R(Args...)>, F> = dyno::make_concept_map(
  "call"_s = [](F const& f, Args ...args) -> R {
    return f(std::forward<Args>(args)...);
  }
);

template <typename Signature, typename StoragePolicy>
struct basic_function;

template <typename R, typename ...Args, typename StoragePolicy>
struct basic_function<R(Args...), StoragePolicy> {
  template <typename F = R(Args...)>
  basic_function(F&& f) : poly_{std::forward<F>(f)} { }

  R operator()(Args ...args) const
  { return poly_.virtual_("call"_s)(poly_, std::forward<Args>(args)...); }

private:
  dyno::poly<Callable<R(Args...)>, StoragePolicy> poly_;
};

template <typename Signature>
using function = basic_function<Signature, dyno::sbo_storage<16>>;

template <typename Signature>
using function_view = basic_function<Signature, dyno::non_owning_storage>;

template <typename Signature> // could also templatize the size
using inplace_function = basic_function<Signature, dyno::local_storage<16>>;


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

template <template <typename> class Function>
void test() {
  // store a free function
  {
    function<std::string(int)> tostring = std::to_string;
    DYNO_CHECK(tostring(1) == "1");
    DYNO_CHECK(tostring(2) == "2");
    DYNO_CHECK(tostring(3) == "3");
    DYNO_CHECK(tostring(-10) == "-10");
  }

  // store a lambda
  {
    auto lambda = [](std::string const& s) {
      return s.size();
    };
    function<int(std::string const&)> size = lambda;

    DYNO_CHECK(size("") == 0);
    DYNO_CHECK(size("a") == 1);
    DYNO_CHECK(size("ab") == 2);
    DYNO_CHECK(size("abc") == 3);
    DYNO_CHECK(size("abcdef") == 6);
  }

  // store the result of a call to std::bind
  {
    auto bind = std::bind(static_cast<std::string(*)(int)>(std::to_string), 31337);
    function<std::string()> tostring = bind;
    DYNO_CHECK(tostring() == "31337");
  }

  // store a call to a member function and object
  {
    ToStringAdd const adder{314159};
    auto bind = std::bind(&ToStringAdd::to_string_add, adder, std::placeholders::_1);
    function<std::string(int)> f = bind;
    DYNO_CHECK(f(1) == "314160");
    DYNO_CHECK(f(2) == "314161");
    DYNO_CHECK(f(3) == "314162");
    DYNO_CHECK(f(-10) == "314149");
  }

  // store a call to a member function and object ptr
  {
    ToStringAdd const adder{314159};
    auto bind = std::bind(&ToStringAdd::to_string_add, &adder, std::placeholders::_1);
    function<std::string(int)> f = bind;
    DYNO_CHECK(f(1) == "314160");
    DYNO_CHECK(f(2) == "314161");
    DYNO_CHECK(f(3) == "314162");
    DYNO_CHECK(f(-10) == "314149");
  }

  // store a call to a function object
  {
    ToString f{};
    function<std::string(int)> tostring = f;
    DYNO_CHECK(tostring(1) == "1");
    DYNO_CHECK(tostring(2) == "2");
    DYNO_CHECK(tostring(3) == "3");
    DYNO_CHECK(tostring(18) == "18");
  }
}

int main() {
  test<function>();
  test<function_view>();
  test<inplace_function>();
}
