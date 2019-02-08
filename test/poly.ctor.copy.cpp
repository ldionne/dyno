// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <dyno/builtin.hpp>
#include <dyno/concept.hpp>
#include <dyno/poly.hpp>

#include <awful.hpp>

#include <utility>


int main() {
  // Make sure the copy constructor is not instantiated unless requested.
  {
    using NonCopyable = decltype(dyno::requires_(dyno::MoveConstructible{},
                                                dyno::Destructible{}));
    dyno::poly<NonCopyable> a{awful::noncopyable{}};
    dyno::poly<NonCopyable> b{std::move(a)};
  }
}
