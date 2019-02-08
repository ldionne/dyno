// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include "../test/testing.hpp"


//////////////////////////////////////////////////////////////////////////////
// Important: Keep this file in sync with the 'Erasing non-member functions'
//            section of the README
//////////////////////////////////////////////////////////////////////////////
#include <dyno.hpp>
#include <iostream>
using namespace dyno::literals;

// Define the interface of something that can be drawn
struct Drawable : decltype(dyno::requires_(
  "draw"_s = dyno::function<void (std::ostream&, dyno::T const&)>
)) { };

// Define how concrete types can fulfill that interface
template <typename T>
auto const dyno::default_concept_map<Drawable, T> = dyno::make_concept_map(
  "draw"_s = [](std::ostream& out, T const& self) { self.draw(out); }
  //            ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ matches the concept definition
);

// Define an object that can hold anything that can be drawn.
struct drawable {
  template <typename T>
  drawable(T x) : poly_{x} { }

  void draw(std::ostream& out) const
  { poly_.virtual_("draw"_s)(out, poly_); }
  //                              ^^^^^ passing the poly explicitly

private:
  dyno::poly<Drawable> poly_;
};

struct Square {
  void draw(std::ostream& out) const { out << "Square"; }
};

struct Circle {
  void draw(std::ostream& out) const { out << "Circle"; }
};

void f(drawable const& d) {
  d.draw(std::cout);
}

int main() {
  f(Square{}); // prints Square
  f(Circle{}); // prints Circle
}
//////////////////////////////////////////////////////////////////////////////
