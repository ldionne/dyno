// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include "../test/testing.hpp"

#include <dyno.hpp>

#include <algorithm>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>
using namespace dyno::literals;


//
// Example of creating a std::function-like utility that has additional support
// for calling the function in batch. This allows turning what would normally
// be N calls with N virtual dispatches into N calls with 1 virtual dispatch.
//

template <typename Signature>
struct function;

template <typename R, typename Arg>
struct function<R(Arg)> {
  dyno::poly<decltype(dyno::requires(
    dyno::CopyConstructible{},
    "operator()"_s = dyno::function<R (dyno::T const&, Arg)>,
    "std::transform"_s = dyno::function<R* (dyno::T const&, Arg* /*first*/, Arg* /*last*/, R* /*out*/)>
  ))> poly_;

  template <typename F = R(Arg), typename RawF = std::decay_t<F>,
    typename = std::enable_if_t<!std::is_same<RawF, function>{}>
  >
  function(F&& f)
    : poly_{std::forward<F>(f), dyno::make_concept_map(
      "operator()"_s = [](RawF const& fun, Arg arg) -> R {
        return fun(std::forward<Arg>(arg));
      },
      "std::transform"_s = [](RawF const& fun, Arg* first, Arg* last, R* out) {
        return std::transform(first, last, out, fun);
      }
    )}
  { }

  function(function const&) = default;
  function(function&&) = default;

  R operator()(Arg arg) const {
    return poly_.virtual_("operator()"_s)(poly_, std::forward<Arg>(arg));
  }
};

// Base implementation that requires `std::distance(first, last)` virtual dispatches
template <typename InputIt, typename OutputIt, typename F>
OutputIt my_transform(InputIt first, InputIt last, OutputIt out, F f) {
  return std::transform(first, last, out, f);
}

// Devirtualized implementation that requires only 1 virtual dispatch, but only
// works with a fixed set of types.
template <typename R, typename Arg>
R* my_transform(Arg* first, Arg* last, R* out, function<R(Arg)> const& f) {
  return f.poly_.virtual_("std::transform"_s)(f.poly_, first, last, out);
}

//
// Tests
//

int main() {
  // Use the devirtualized version
  {
    function<std::string(int)> to_s = std::to_string;
    std::vector<int> ints = {1, 2, 3, 4, 5, 6};
    std::vector<std::string> results{ints.size()}; // note the resize here
    my_transform(ints.data(), ints.data() + ints.size(), results.data(), to_s);
    DYNO_CHECK(results == std::vector<std::string>{"1", "2", "3", "4", "5", "6"});
  }

  // Use the normal version
  {
    function<std::string(int)> to_s = std::to_string;
    std::vector<int> ints = {1, 2, 3, 4, 5, 6};
    std::vector<std::string> results;
    my_transform(ints.begin(), ints.end(), std::back_inserter(results), to_s);
    DYNO_CHECK(results == std::vector<std::string>{"1", "2", "3", "4", "5", "6"});
  }
}
