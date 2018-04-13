// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <dyno.hpp>

#include <iostream>
#include <type_traits>
#include <vector>
using namespace dyno::literals;


namespace dyno {
  template <typename Interface, std::size_t N = 0>
  struct map final {
    friend auto __get_value_impl(map);
    template <typename Key, typename Value>
    struct set {
      friend hana::type<std::pair<Key, Value>> __get_value_impl(map) { return {}; }
    };
  };


  template <typename Interface, typename Key>
  constexpr bool map_has_key() { /* TODO */ }

  template <typename Interface, typename Key, std::size_t N>
  constexpr bool map_has_key_impl(...) { return false; }

  template <typename Interface, typename Key, std::size_t N, typename Result = decltype(__get_value_impl(map<Interface, N>{})>
  constexpr bool map_has_key_impl(int)
  { return std::is_same<Result::first, Key>{} || map_has_key_impl<Interface, Key, N+1>(int{}); }


  // Then we implement map_size(), and map_get_value(), and we use this as a front-end for Dyno.


  template <typename Interface, typename Name, typename Signature, typename F>
  void register_virtual() {
    map<Interface>::set<Name, F>{};
  }
}

struct Drawable {
  void draw(std::ostream& out) const {
    dyno::register_virtual<Drawable>(
      "draw"_s,
      dyno::method<void (std::ostream&) const>,
      [](auto const& self, std::ostream& out) { self.draw(out); }
    );
  }
};

using VTable = dyno::vtable_for<Drawable>;


struct Circle {
  void draw(std::ostream& out) const {
    out << "circle" << std::endl;
  }
};

void f(dyno::poly<Drawable> d) {
  d.draw(std::cout);
}

int main() {
  f(Square{});                  // prints "square"
  f(Circle{});                  // prints "circle"
  f(std::vector<int>{1, 2, 3}); // prints "1 2 3 "
}
