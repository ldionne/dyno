// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

//////////////////////////////////////////////////////////////////////////////
// Important: Keep this file in sync with the Overview in the README
//////////////////////////////////////////////////////////////////////////////
#include <te.hpp>
#include <iostream>
using namespace te::literals;

// Define the interface of something that can be drawn
struct Drawable : decltype(te::requires(
  "draw"_s = te::function<void (te::T const&, std::ostream&)>
)) { };

// Provide a default implementation of that interface
template <typename T>
auto const te::default_concept_map<Drawable, T> = te::make_concept_map(
  "draw"_s = [](T const& self, std::ostream& out) { self.draw(out); }
);

// Define an object that can hold anything that can be drawn.
struct drawable {
  template <typename T>
  drawable(T x) : poly_{x} { }

  void draw(std::ostream& out) const
  { poly_.virtual_("draw"_s)(poly_.get(), out); }

private:
  te::poly<Drawable> poly_;
};

struct Square {
  void draw(std::ostream& out) const { /* ... */ }
};

struct Circle {
  void draw(std::ostream& out) const { /* ... */ }
};

void f(drawable const& d) {
  d.draw(std::cout);
}
//////////////////////////////////////////////////////////////////////////////

int main() {
  f(Square{});
  f(Circle{});
}
