// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include "../test/testing.hpp"

#include <dyno.hpp>

#include <cassert>
#include <iterator>
#include <utility>
#include <vector>
using namespace dyno::literals;


// This example shows how vtable traits can be used to customize the way
// dynamic dispatch is done, and in particular how one can control which
// function pointers are stored where. In this specific example, the goal
// is to store functions that are called often in the object itself, but
// other functions (e.g. the destructor) in a remote vtable.

template <typename Reference>
struct Iterator : decltype(dyno::requires_(
  dyno::DefaultConstructible{},
  dyno::CopyConstructible{},
  dyno::CopyAssignable{},
  dyno::Destructible{},
  dyno::Swappable{},
  dyno::EqualityComparable{},
  "increment"_s = dyno::function<void (dyno::T&)>,
  "decrement"_s = dyno::function<void (dyno::T&)>,
  "dereference"_s = dyno::function<Reference (dyno::T&)>,
  "advance"_s = dyno::function<void (dyno::T&, std::ptrdiff_t)>,
  "distance"_s = dyno::function<std::ptrdiff_t (dyno::T const&, dyno::T const&)>
)) { };

template <typename Ref, typename T>
auto const dyno::default_concept_map<Iterator<Ref>, T> = dyno::make_concept_map(
  "increment"_s = [](T& self) { ++self; },
  "decrement"_s = [](T& self) -> void { --self; },
  "dereference"_s = [](T& self) -> Ref { return *self; },
  "advance"_s = [](T& self, std::ptrdiff_t diff) -> void {
    std::advance(self, diff);
  },
  "distance"_s = [](T const& first, T const& last) -> std::ptrdiff_t {
    return std::distance(first, last);
  }
);

template <typename Value, typename Reference = Value&>
struct any_iterator {
  using iterator_category = std::random_access_iterator_tag;
  using value_type = Value;
  using reference = Reference;
  using pointer = value_type*;
  using difference_type = std::ptrdiff_t;

private:
  using Concept = Iterator<reference>;
  using Storage = dyno::remote_storage;
  using VTable = dyno::vtable<
    dyno::local<dyno::only<
      decltype("increment"_s), decltype("equal"_s), decltype("dereference"_s)
    >>,
    dyno::remote<dyno::everything_else>
  >;
  dyno::poly<Concept, Storage, VTable> poly_;

public:
  template <typename It>
  explicit any_iterator(It it)
    : poly_{std::move(it)}
  { }

  any_iterator(any_iterator const& other) = default;
  any_iterator(any_iterator&& other) = default;
  any_iterator& operator=(any_iterator const& other) = default;
  any_iterator& operator=(any_iterator&& other) = default;
  ~any_iterator() = default;

  void swap(any_iterator& other) {
    using std::swap;
    swap(this->poly_, other.poly_);
  }

  friend void swap(any_iterator& a, any_iterator& b) { a.swap(b); }

  any_iterator& operator++() {
    poly_.virtual_("increment"_s)(poly_);
    return *this;
  }

  any_iterator& operator--() {
    poly_.virtual_("decrement"_s)(poly_);
    return *this;
  }

  reference operator*() {
    return poly_.virtual_("dereference"_s)(poly_);
  }

  friend bool operator==(any_iterator const& a, any_iterator const& b) {
    return a.poly_.virtual_("equal"_s)(a.poly_, b.poly_);
  }

  friend bool operator!=(any_iterator const& a, any_iterator const& b) {
    return !(a == b);
  }
};

int main() {
  using Iterator = any_iterator<int>;
  std::vector<int> input = {1, 2, 3, 4};
  std::vector<int> result;
  Iterator first{input.begin()}, last{input.end()};

  for (; first != last; ++first) {
    result.push_back(*first);
  }
  DYNO_CHECK(result == input);
}
