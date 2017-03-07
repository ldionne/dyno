// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <dyno/detail/transform_signature.hpp>

#include <type_traits>


static_assert(std::is_same<
  dyno::detail::transform_signature<char (), std::add_pointer>::type,
  char* ()
>{}, "");

static_assert(std::is_same<
  dyno::detail::transform_signature<char (void), std::add_pointer>::type,
  char* (void)
>{}, "");

static_assert(std::is_same<
  dyno::detail::transform_signature<char (int), std::add_pointer>::type,
  char* (int*)
>{}, "");


// Check with C-style varargs
static_assert(std::is_same<
  dyno::detail::transform_signature<char (...), std::add_pointer>::type,
  char* (...)
>{}, "");

static_assert(std::is_same<
  dyno::detail::transform_signature<char (int, ...), std::add_pointer>::type,
  char* (int*, ...)
>{}, "");

int main() { }
