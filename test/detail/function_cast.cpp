// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <te/detail/function_cast.hpp>
#include <te/dsl.hpp>

#include <type_traits>


static_assert(std::is_same<
  te::detail::sig_replace<void (te::T&)>::type,
  void (*)(void*)
>{}, "");

int main() { }
