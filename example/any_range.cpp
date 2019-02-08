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
struct Range : decltype(dyno::requires_(
  "begin"_s = dyno::function<any_iterator<Value, Category> (dyno::T&)>,
  "end"_s = dyno::function<any_iterator<Value, Category> (dyno::T&)>,
  "cbegin"_s = dyno::function<any_iterator<Value const, Category> (dyno::T const&)>,
  "cend"_s = dyno::function<any_iterator<Value const, Category> (dyno::T const&)>
)) { };

template <typename Value, typename Category, typename R>
auto const dyno::default_concept_map<Range<Value, Category>, R> = dyno::make_concept_map(
  "begin"_s = [](R& range) -> any_iterator<Value, Category> {
    return any_iterator<Value, Category>{range.begin()};
  },
  "end"_s = [](R& range) -> any_iterator<Value, Category> {
    return any_iterator<Value, Category>{range.end()};
  },
  "cbegin"_s = [](R const& range) -> any_iterator<Value const, Category> {
    return any_iterator<Value const, Category>{range.cbegin()};
  },
  "cend"_s = [](R const& range) -> any_iterator<Value const, Category> {
    return any_iterator<Value const, Category>{range.cend()};
  }
);

template <typename Value, typename Category>
struct any_range {
  template <typename Range>
  any_range(Range&& r) : poly_{std::forward<Range>(r)} { }

  auto begin()        { return poly_.virtual_("begin"_s)(poly_); }
  auto end()          { return poly_.virtual_("end"_s)(poly_); }
  auto begin() const  { return cbegin(); }
  auto end() const    { return cend(); }

  auto cbegin() const { return poly_.virtual_("cbegin"_s)(poly_); }
  auto cend() const   { return poly_.virtual_("cend"_s)(poly_); }

private:
  dyno::poly<Range<Value, Category>> poly_;
};

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
