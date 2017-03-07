// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <dyno/concept.hpp>
#include <dyno/detail/erase_function.hpp>

#include <boost/callable_traits.hpp>
#include <type_traits>


struct Foo { };

int main() {
  // erase_function should pass by-value arguments through
  {
    auto f = [](Foo) { };
    auto erased = dyno::detail::erase_function<void (Foo)>(f);
    erased(Foo{});

    static_assert(std::is_same<
      boost::callable_traits::function_type_t<decltype(erased)>,
      void (Foo)
    >{}, "");
  }

  // same as above, but with a function that does not return void
  // (hits a different specialization of `thunk`)
  {
    auto f = [](Foo) { return 5; };
    auto erased = dyno::detail::erase_function<int (Foo)>(f);
    erased(Foo{});

    static_assert(std::is_same<
      boost::callable_traits::function_type_t<decltype(erased)>,
      int (Foo)
    >{}, "");
  }
}
