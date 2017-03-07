// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <dyno.hpp>

#include <iostream>
#include <type_traits>
#include <vector>
using namespace dyno::literals;

namespace std { template <typename ...> using void_t = void; }


struct Drawable : decltype(dyno::requires(
  "draw"_s = dyno::function<void (dyno::T const&, std::ostream&)>
)) { };

// TODO: Workaround Clang <= 3.8 bug with variable templates and generic lambdas.
template <typename T, typename ...Args>
constexpr auto delayed_concept_map(Args ...args)
{ return dyno::make_concept_map(args...); }

template <typename T>
auto const dyno::default_concept_map<Drawable, T> = delayed_concept_map<T>(
  "draw"_s = [](auto const& t, std::ostream& out) { t.draw(out); }
);

struct drawable {
  template <typename T>
  drawable(T x) : poly_{x} { }

  void draw(std::ostream& out) const
  { poly_.virtual_("draw"_s)(poly_, out); }

private:
  dyno::poly<Drawable> poly_;
};


struct Square { /* ... */ };

template <>
auto const dyno::concept_map<Drawable, Square> = dyno::make_concept_map(
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
