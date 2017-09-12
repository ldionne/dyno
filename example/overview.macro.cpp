// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include "../test/testing.hpp"


//////////////////////////////////////////////////////////////////////////////
// Important: Keep this file in sync with the Overview in the README
//////////////////////////////////////////////////////////////////////////////
#include <dyno.hpp>
#include <iostream>

// Define the interface of something that can be drawn
DYNO_INTERFACE(Drawable,
  (draw, void (std::ostream&) const)
);

struct Square {
  void draw(std::ostream& out) const { out << "Square"; }
};

struct Circle {
  void draw(std::ostream& out) const { out << "Circle"; }
};

void f(Drawable const& d) {
  d.draw(std::cout);
}

int main() {
  f(Square{}); // prints Square
  f(Circle{}); // prints Circle
}
//////////////////////////////////////////////////////////////////////////////
