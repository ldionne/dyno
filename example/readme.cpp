// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <dyno.hpp>

#include <iostream>
#include <type_traits>
#include <vector>
using namespace dyno::literals;


struct Drawable : decltype(dyno::requires_(
  "draw"_s = dyno::method<void (std::ostream&) const>
)) { };

template <typename T>
auto const dyno::default_concept_map<Drawable, T> = dyno::make_concept_map(
  "draw"_s = [](auto const& self, std::ostream& out) { self.draw(out); }
);

struct drawable {
  template <typename T>
  drawable(T x) : poly_{x} { }

  void draw(std::ostream& out) const
  { poly_.virtual_("draw"_s)(out); }

private:
  dyno::poly<Drawable> poly_;
};


struct Square { /* ... */ };

template <>
auto const dyno::concept_map<Drawable, Square> = dyno::make_concept_map(
  "draw"_s = [](Square const& /*square*/, std::ostream& out) {
    out << "square" << std::endl;
  }
);


struct Circle {
  void draw(std::ostream& out) const {
    out << "circle" << std::endl;
  }
};


template <typename T>
auto const dyno::concept_map<Drawable, std::vector<T>, std::void_t<decltype(
  std::cout << std::declval<T>()
)>> = dyno::make_concept_map(
  "draw"_s = [](std::vector<T> const& v, std::ostream& out) {
    for (auto const& x : v)
      out << x << ' ';
  }
);

void f(drawable d) {
  d.draw(std::cout);
}

int main() {
  f(Square{});                  // prints "square"
  f(Circle{});                  // prints "circle"
  f(std::vector<int>{1, 2, 3}); // prints "1 2 3 "
}
