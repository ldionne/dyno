// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include "../test/testing.hpp"

#include "any_iterator.hpp"

#include <array>
#include <cassert>
#include <iterator>
#include <utility>
#include <vector>


int main() {
  ////////////////////////////////////////////////////////////////////////////
  // Iteration
  ////////////////////////////////////////////////////////////////////////////
  {
    using Iterator = any_iterator<int, std::forward_iterator_tag>;
    std::vector<int> input{1, 2, 3, 4};
    std::vector<int> result;

    Iterator first{input.begin()}, last{input.end()};
    for (; first != last; ++first) {
      result.push_back(*first);
    }
    DYNO_CHECK(result == input);
  }

  {
    using Iterator = any_iterator<int, std::bidirectional_iterator_tag>;
    std::array<int, 4> input{{1, 2, 3, 4}};
    std::array<int, 4> result;
    std::reverse_iterator<Iterator> first{Iterator{input.end()}},
                                    last{Iterator{input.begin()}};
    Iterator out{result.begin()};

    for (; first != last; ++first, ++out) {
      *out = *first;
    }
    std::array<int, 4> expected{{4, 3, 2, 1}};
    DYNO_CHECK(result == expected);
  }

  {
    using Iterator = any_iterator<int, std::random_access_iterator_tag>;
    std::array<int, 4> input{{1, 2, 3, 4}};
    std::array<int, 4> result;
    Iterator first{input.begin()}, last{input.end()}, out{result.begin()};

    for (; first != last; ++first, ++out) {
      *out = *first;
    }
    DYNO_CHECK(result == input);
  }

  ////////////////////////////////////////////////////////////////////////////
  // Copy-construction
  ////////////////////////////////////////////////////////////////////////////
  {
    using Iterator = any_iterator<int, std::random_access_iterator_tag>;
    std::vector<int> input{1, 2, 3, 4};
    Iterator first{input.begin()}, last{input.end()};
    Iterator cfirst(first), clast(last);
    DYNO_CHECK(first == cfirst);
    DYNO_CHECK(last == clast);
  }

  ////////////////////////////////////////////////////////////////////////////
  // Move-construction
  ////////////////////////////////////////////////////////////////////////////
  {
    using Iterator = any_iterator<int, std::random_access_iterator_tag>;
    std::vector<int> input{1, 2, 3, 4};
    std::vector<int> result;

    Iterator first{input.begin()}, last{input.end()};
    Iterator cfirst(std::move(first)), clast(std::move(last));
    for (; cfirst != clast; ++cfirst) {
      result.push_back(*cfirst);
    }
    DYNO_CHECK(result == input);
  }

  ////////////////////////////////////////////////////////////////////////////
  // Copy-assignment
  ////////////////////////////////////////////////////////////////////////////
  {
    using Iterator = any_iterator<int, std::random_access_iterator_tag>;
    std::vector<int> input{1, 2, 3, 4};
    Iterator first{input.begin()}, mid{input.begin() + 2};
    DYNO_CHECK(*first == 1);
    first = mid;
    DYNO_CHECK(*first == 3);
  }

  ////////////////////////////////////////////////////////////////////////////
  // Move-assignment
  ////////////////////////////////////////////////////////////////////////////
  {
    using Iterator = any_iterator<int, std::random_access_iterator_tag>;
    std::vector<int> input{1, 2, 3, 4};
    Iterator first{input.begin()}, mid{input.begin() + 2};
    DYNO_CHECK(*first == 1);
    first = std::move(mid);
    DYNO_CHECK(*first == 3);
  }

  ////////////////////////////////////////////////////////////////////////////
  // Swap
  ////////////////////////////////////////////////////////////////////////////
  {
    using Iterator = any_iterator<int, std::random_access_iterator_tag>;
    std::vector<int> input{1, 2, 3, 4};
    Iterator first{input.begin()}, last{input.end()};
    using std::swap;
    swap(first, last);
    DYNO_CHECK(*last == 1);
    ++last;
    DYNO_CHECK(*last == 2);
    DYNO_CHECK(first == Iterator{input.end()});
  }
}
