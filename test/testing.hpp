// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#ifndef DYNO_TEST_TESTING_HPP
#define DYNO_TEST_TESTING_HPP

#include <cstdio>
#include <cstdlib>


// Definition copied from `assert`. We don't use `assert` because we want to
// allow testing in Release mode, when `_NDEBUG` is defined.
#define DYNO_CHECK(...)                                                   \
  ((__VA_ARGS__) ? (void)0 : DYNO_CHECK_IMPL(#__VA_ARGS__, __FILE__, __LINE__))

#define DYNO_CHECK_IMPL(expr, file, line) \
  (std::printf("%s:%u: failed assertion `%s'\n", file, line, expr), std::abort())

#endif // DYNO_TEST_TESTING_HPP
