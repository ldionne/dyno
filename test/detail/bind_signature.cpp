// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <dyno/concept.hpp>
#include <dyno/detail/bind_signature.hpp>

#include <type_traits>


struct T;

static_assert(std::is_same<
  dyno::detail::bind_signature<char (), T>::type,
  char ()
>{}, "");

static_assert(std::is_same<
  dyno::detail::bind_signature<char (void), T>::type,
  char (void)
>{}, "");

static_assert(std::is_same<
  dyno::detail::bind_signature<char (int), T>::type,
  char (int)
>{}, "");

static_assert(std::is_same<
  dyno::detail::bind_signature<dyno::T& (int), T>::type,
  T& (int)
>{}, "");

static_assert(std::is_same<
  dyno::detail::bind_signature<void (dyno::T&), T>::type,
  void (T&)
>{}, "");

static_assert(std::is_same<
  dyno::detail::bind_signature<dyno::T&& (dyno::T&), T>::type,
  T&& (T&)
>{}, "");

static_assert(std::is_same<
  dyno::detail::bind_signature<dyno::T const* (dyno::T const&), T>::type,
  T const* (T const&)
>{}, "");

static_assert(std::is_same<
  dyno::detail::bind_signature<void (dyno::T const, dyno::T), T>::type,
  void (T const, T)
>{}, "");

// Check with C-style varargs
static_assert(std::is_same<
  dyno::detail::bind_signature<char (int, ...), T>::type,
  char (int, ...)
>{}, "");

static_assert(std::is_same<
  dyno::detail::bind_signature<char (dyno::T&, ...), T>::type,
  char (T&, ...)
>{}, "");

static_assert(std::is_same<
  dyno::detail::bind_signature<dyno::T& (dyno::T&, ...), T>::type,
  T& (T&, ...)
>{}, "");

static_assert(std::is_same<
  dyno::detail::bind_signature<void (dyno::T&, ...), T>::type,
  void (T&, ...)
>{}, "");

int main() { }
