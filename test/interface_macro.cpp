// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <dyno/interface_macro.hpp>

#include <string>
#include <tuple>
#include <utility>
#include <vector>


DYNO_INTERFACE(Concept,
  (f1, void(int) const),
  (f2, char(std::pair<long, double>) const),
  (f3, std::tuple<int, char> (std::string const&))
);

struct Model1 {
  void f1(int) const { }
  char f2(std::pair<long, double>) const { return 'x'; }
  std::tuple<int, char> f3(std::string const&) { return {}; }
};

struct Model2 {
  void f1(int) const { }
  char f2(std::pair<long, double>) const { return 'x'; }
  std::tuple<int, char> f3(std::string const&) { return {}; }
};

int main() {
  std::vector<Concept> vec;
  Model1 m1;
  Model2 m2;
  vec.push_back(m1);
  vec.push_back(m2);
  for (Concept& c : vec) {
    c.f1(30);
    char f2_res = c.f2(std::make_pair(99l, 87.4)); (void)f2_res;
    std::tuple<int, char> f3_res = c.f3("foobar"); (void)f3_res;
  }
}
