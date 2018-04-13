// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include "../test/testing.hpp"
#include "any_iterator.hpp"

#include <dyno.hpp>

#include <algorithm>
#include <iterator>
#include <list>
#include <utility>
#include <vector>
using namespace dyno::literals;


//
// Example of creating an erased range type for holding anything that has
// begin() and end() functions.
//

template <typename Value, typename Category>
struct Range {
  virtual any_iterator<Value, Category>       begin();
  virtual any_iterator<Value, Category>       end();
          any_iterator<Value const, Category> begin() const { return cbegin(); }
          any_iterator<Value const, Category> end() const { return cend(); }

  virtual any_iterator<Value const, Category> cbegin() const;
  virtual any_iterator<Value const, Category> cend() const;
};

constexpr std::meta::type vtable_layout_impl(std::meta::type interface) {
  auto vtable = reflexpr(struct { });
  for (auto method : interface.methods()) {
    if (method.is_virtual()) {
      // signature of the method, with void* as first argument
      auto signature = method.signature().insert_argument(0, reflexpr(void*));
      vtable.add_public_member(method.name(), method.add_ptr());
    }
  }
  return vtable;
}

//
// Tests
//

int main() {
  using Range = any_range<int, std::forward_iterator_tag>;
  {
    Range vector = std::vector<int>{1, 2, 3, 4, 5};
    Range list = std::list<int>{1, 2, 3, 4, 5};
    DYNO_CHECK(std::equal(vector.begin(), vector.end(), list.begin(), list.end()));
  }
  {
    Range const cvector = std::vector<int>{1, 2, 3, 4, 5};
    Range const clist = std::list<int>{1, 2, 3, 4, 5};
    DYNO_CHECK(std::equal(cvector.begin(), cvector.end(), clist.begin(), clist.end()));
  }
  {
    Range vector = std::vector<int>{1, 2, 3, 4, 5};
    Range list = std::list<int>{1, 2, 3, 4, 5};
    DYNO_CHECK(std::equal(vector.cbegin(), vector.cend(), list.cbegin(), list.cend()));
  }
}
