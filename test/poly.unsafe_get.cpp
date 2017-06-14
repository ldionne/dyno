// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include "testing.hpp"

#include <dyno/builtin.hpp>
#include <dyno/poly.hpp>

#include <string>
using namespace dyno::literals;


int main() {
  std::string foobar{"foobar"};

  {
    // non-const version
    dyno::poly<dyno::CopyConstructible> poly{foobar};
    std::string* s = poly.unsafe_get<std::string>();
    DYNO_CHECK(*s == foobar);

    // make sure the pointer we got is to the underlying storage of the poly
    *s += "baz";
    std::string* s2 = poly.unsafe_get<std::string>();
    DYNO_CHECK(*s2 == "foobarbaz");
    DYNO_CHECK(*s2 == *s);
  }

  {
    // const version
    dyno::poly<dyno::CopyConstructible> const poly{foobar};
    std::string const* s = poly.unsafe_get<std::string>();
    DYNO_CHECK(*s == foobar);
  }
}
