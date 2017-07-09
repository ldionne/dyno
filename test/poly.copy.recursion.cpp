// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include "testing.hpp"

#include <dyno/builtin.hpp>
#include <dyno/concept.hpp>
#include <dyno/poly.hpp>

#include <utility>


// This test checks that we do not hit infinite recursion when trying to make
// a copy of a type-erased wrapper built on top of `dyno::poly`, which once
// happened.

struct wrapper {
  template <typename T>
  wrapper(T&& x)
    : poly_{std::forward<T>(x)}
  { }

  wrapper(wrapper const&) = default;
  wrapper(wrapper&&) = default;

private:
  dyno::poly<dyno::CopyConstructible> poly_;
};

struct Foo { };

int main() {
  wrapper w = Foo{};
  wrapper implicit_copy = w;
  wrapper explicit_copy{w};
}
