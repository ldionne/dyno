// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <dyno/concept.hpp>
#include <dyno/detail/erase_function.hpp>

#include <awful.hpp>
#include <boost/callable_traits.hpp>
#include <type_traits>
#include <utility>


int main() {
  // erase_function should pass rvalues through as rvalues
  {
    awful::noncopyable x{};
    auto f = [](awful::noncopyable&&) { };
    auto erased = dyno::detail::erase_function<void (dyno::T&&)>(f);
    erased(static_cast<void*>(&x));

    static_assert(std::is_same<
      boost::callable_traits::function_type_t<decltype(erased)>,
      void (void*)
    >{}, "");
  }

  // same as above, but with a function that does not return void
  // (hits a different specialization of `thunk`)
  {
    awful::noncopyable x{};
    auto f = [](awful::noncopyable&&) { return 0; };
    auto erased = dyno::detail::erase_function<int (dyno::T&&)>(f);
    erased(static_cast<void*>(&x));

    static_assert(std::is_same<
      boost::callable_traits::function_type_t<decltype(erased)>,
      int (void*)
    >{}, "");
  }

  // same as above, but make sure we pass through non-erased arguments too
  {
    awful::noncopyable x{};
    auto f = [](awful::noncopyable&&) { };
    auto erased = dyno::detail::erase_function<void (awful::noncopyable&&)>(f);
    erased(std::move(x));

    static_assert(std::is_same<
      boost::callable_traits::function_type_t<decltype(erased)>,
      void (awful::noncopyable&&)
    >{}, "");
  }

  // same as above, but do not return void
  {
    awful::noncopyable x{};
    auto f = [](awful::noncopyable&&) { return 0; };
    auto erased = dyno::detail::erase_function<int (awful::noncopyable&&)>(f);
    erased(std::move(x));

    static_assert(std::is_same<
      boost::callable_traits::function_type_t<decltype(erased)>,
      int (awful::noncopyable&&)
    >{}, "");
  }
}
