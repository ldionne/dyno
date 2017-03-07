// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <dyno/concept.hpp>
#include <dyno/detail/erase_signature.hpp>

#include <type_traits>


static_assert(std::is_same<
  dyno::detail::erase_signature<char ()>::type,
  char ()
>{}, "");

static_assert(std::is_same<
  dyno::detail::erase_signature<char (void)>::type,
  char (void)
>{}, "");

static_assert(std::is_same<
  dyno::detail::erase_signature<char (int)>::type,
  char (int)
>{}, "");

static_assert(std::is_same<
  dyno::detail::erase_signature<dyno::T& (int)>::type,
  void* (int)
>{}, "");

static_assert(std::is_same<
  dyno::detail::erase_signature<void (dyno::T&)>::type,
  void (void*)
>{}, "");

static_assert(std::is_same<
  dyno::detail::erase_signature<dyno::T&& (dyno::T&)>::type,
  void* (void*)
>{}, "");

// Check with C-style varargs
static_assert(std::is_same<
  dyno::detail::erase_signature<char (int, ...)>::type,
  char (int, ...)
>{}, "");

static_assert(std::is_same<
  dyno::detail::erase_signature<char (dyno::T&, ...)>::type,
  char (void*, ...)
>{}, "");

static_assert(std::is_same<
  dyno::detail::erase_signature<dyno::T& (dyno::T&, ...)>::type,
  void* (void*, ...)
>{}, "");

static_assert(std::is_same<
  dyno::detail::erase_signature<void (dyno::T&, ...)>::type,
  void (void*, ...)
>{}, "");

int main() { }
