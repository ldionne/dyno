// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include "../testing.hpp"

#include <dyno/detail/empty_object.hpp>

#include <type_traits>


int main() {
  {
    auto lambda = []() { return 99; };
    using Empty = dyno::detail::empty_object<decltype(lambda)>;
    static_assert(std::is_standard_layout<Empty::T1>{}, "");
    static_assert(std::is_standard_layout<Empty::T2>{}, "");

    auto f = Empty::get();
    DYNO_CHECK(f() == 99);
  }
  {
    auto lambda = [](int x) { return x; };
    using Empty = dyno::detail::empty_object<decltype(lambda)>;
    static_assert(std::is_standard_layout<Empty::T1>{}, "");
    static_assert(std::is_standard_layout<Empty::T2>{}, "");

    auto f = Empty::get();
    DYNO_CHECK(f(88) == 88);
  }
  {
    auto lambda = [](int x, int y) { return x + y; };
    using Empty = dyno::detail::empty_object<decltype(lambda)>;
    static_assert(std::is_standard_layout<Empty::T1>{}, "");
    static_assert(std::is_standard_layout<Empty::T2>{}, "");

    auto f = Empty::get();
    DYNO_CHECK(f(66, 77) == 66 + 77);
  }

  // Check with an empty function object.
  {
    struct lambda {
      lambda() = delete;
      int operator()() const { return 99; }
    };

    using Empty = dyno::detail::empty_object<lambda>;
    static_assert(std::is_standard_layout<Empty::T1>{}, "");
    static_assert(std::is_standard_layout<Empty::T2>{}, "");

    auto f = Empty::get();
    DYNO_CHECK(f() == 99);
  }
}
