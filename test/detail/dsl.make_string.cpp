// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <dyno/detail/dsl.hpp>

#include <type_traits>


int main() {
  {
    static constexpr char const s[] = "";
    static_assert(std::is_same<decltype(dyno::detail::make_string<s>()),
                               dyno::detail::string<>>{});
  }

  {
    static constexpr char const s[] = "a";
    static_assert(std::is_same<decltype(dyno::detail::make_string<s>()),
                               dyno::detail::string<'a'>>{});
  }

  {
    static constexpr char const s[] = "abc";
    static_assert(std::is_same<decltype(dyno::detail::make_string<s>()),
                               dyno::detail::string<'a', 'b', 'c'>>{});
  }
}
