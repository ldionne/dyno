// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <vector>


volatile long long COUNTER = 100000000;

int main() {
  using Iterator = std::vector<int>::iterator;
  std::vector<int> input; input.resize(COUNTER);
  std::vector<int> result; result.reserve(COUNTER);

  Iterator first{input.begin()}, last{input.end()};
  for (; first != last; ++first) {
    result.push_back(*first);
  }
}
