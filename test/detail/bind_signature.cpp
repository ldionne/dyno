// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <te/concept.hpp>
#include <te/detail/bind_signature.hpp>

#include <type_traits>


struct T;

static_assert(std::is_same<
  te::detail::bind_signature<char (), T>::type,
  char ()
>{}, "");

static_assert(std::is_same<
  te::detail::bind_signature<char (void), T>::type,
  char (void)
>{}, "");

static_assert(std::is_same<
  te::detail::bind_signature<char (int), T>::type,
  char (int)
>{}, "");

static_assert(std::is_same<
  te::detail::bind_signature<te::T& (int), T>::type,
  T& (int)
>{}, "");

static_assert(std::is_same<
  te::detail::bind_signature<void (te::T&), T>::type,
  void (T&)
>{}, "");

static_assert(std::is_same<
  te::detail::bind_signature<te::T&& (te::T&), T>::type,
  T&& (T&)
>{}, "");

static_assert(std::is_same<
  te::detail::bind_signature<te::T const* (te::T const&), T>::type,
  T const* (T const&)
>{}, "");

static_assert(std::is_same<
  te::detail::bind_signature<void (te::T const, te::T), T>::type,
  void (T const, T)
>{}, "");

// Check with C-style varargs
static_assert(std::is_same<
  te::detail::bind_signature<char (int, ...), T>::type,
  char (int, ...)
>{}, "");

static_assert(std::is_same<
  te::detail::bind_signature<char (te::T&, ...), T>::type,
  char (T&, ...)
>{}, "");

static_assert(std::is_same<
  te::detail::bind_signature<te::T& (te::T&, ...), T>::type,
  T& (T&, ...)
>{}, "");

static_assert(std::is_same<
  te::detail::bind_signature<void (te::T&, ...), T>::type,
  void (T&, ...)
>{}, "");

int main() { }
