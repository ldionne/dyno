// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <te/builtin.hpp>
#include <te/concept.hpp>
#include <te/poly.hpp>

#include <utility>


struct NoCopy {
  NoCopy() = default;
  NoCopy(NoCopy const&) = delete;
  NoCopy(NoCopy&&) = default;
  ~NoCopy() = default;
};

int main() {
  // Make sure the copy constructor and friends don't get instantiated
  // all the time.
  {
    using C = decltype(te::requires(te::MoveConstructible{}, te::Destructible{}));

    te::poly<C> a{NoCopy{}};
    te::poly<C> b{std::move(a)};
  }
}
