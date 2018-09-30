// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <dyno/detail/dsl.hpp>
#include <dyno/detail/eraser_traits.hpp>


struct Foo { };

int main() {
  Foo foo;

  // MESSAGE[will move from non-rvalue]
  dyno::detail::erase<void, dyno::T&&>::apply(foo);
}
