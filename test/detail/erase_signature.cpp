// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <te/detail/erase_signature.hpp>
#include <te/dsl.hpp>

#include <type_traits>


static_assert(std::is_same<
  te::detail::erase_signature<char ()>::type,
  char ()
>{}, "");

static_assert(std::is_same<
  te::detail::erase_signature<char (void)>::type,
  char (void)
>{}, "");

static_assert(std::is_same<
  te::detail::erase_signature<char (int)>::type,
  char (int)
>{}, "");

static_assert(std::is_same<
  te::detail::erase_signature<te::T& (int)>::type,
  void* (int)
>{}, "");

static_assert(std::is_same<
  te::detail::erase_signature<void (te::T&)>::type,
  void (void*)
>{}, "");

static_assert(std::is_same<
  te::detail::erase_signature<te::T&& (te::T&)>::type,
  void* (void*)
>{}, "");

// Check with C-style varargs
static_assert(std::is_same<
  te::detail::erase_signature<char (int, ...)>::type,
  char (int, ...)
>{}, "");

static_assert(std::is_same<
  te::detail::erase_signature<char (te::T&, ...)>::type,
  char (void*, ...)
>{}, "");

static_assert(std::is_same<
  te::detail::erase_signature<te::T& (te::T&, ...)>::type,
  void* (void*, ...)
>{}, "");

static_assert(std::is_same<
  te::detail::erase_signature<void (te::T&, ...)>::type,
  void (void*, ...)
>{}, "");

int main() { }
