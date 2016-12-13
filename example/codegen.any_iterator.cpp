// Copyright Louis Dionne 2016
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include "any_iterator.hpp"

#include <iterator>
#include <vector>


volatile long long COUNTER = 100000000;

int main() {
  using Iterator = any_iterator<int, std::random_access_iterator_tag>;
  std::vector<int> input; input.resize(COUNTER);
  std::vector<int> result; result.reserve(COUNTER);

  Iterator first{input.begin()}, last{input.end()};
  for (; first != last; ++first) {
    result.push_back(*first);
  }
}
