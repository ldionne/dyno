// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <te.hpp>

#include <iostream>
#include <type_traits>
#include <vector>
using namespace te::literals;

namespace std { template <typename ...> using void_t = void; }


struct Drawable : decltype(te::requires(
  "draw"_s = te::function<void (te::T const&, std::ostream&)>
)) { };

template <typename T>
auto te::default_concept_map<Drawable, T> = te::make_default_concept_map<Drawable, T>(
  "draw"_s = [](auto const& t, std::ostream& out) { t.draw(out); }
);

struct drawable {
  template <typename T>
  drawable(T x) : poly_{x} { }

  void draw(std::ostream& out) const
  { poly_.virtual_("draw"_s)(poly_.get(), out); }

private:
  te::poly<Drawable> poly_;
};


struct Square { /* ... */ };

template <>
auto te::concept_map<Drawable, Square> = te::make_concept_map<Drawable, Square>(
  "draw"_s = [](Square const& square, std::ostream& out) {
    out << "square" << std::endl;
  }
);


struct Circle {
  void draw(std::ostream& out) const {
    out << "circle" << std::endl;
  }
};


template <typename T>
auto te::concept_map<Drawable, std::vector<T>, std::void_t<decltype(
  std::cout << std::declval<T>()
)>> = te::make_concept_map<Drawable, std::vector<T>>(
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
