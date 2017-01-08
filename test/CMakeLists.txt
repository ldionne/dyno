# Copyright Louis Dionne 2017
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

add_custom_target(tests COMMENT "Build all the unit tests.")
add_dependencies(check tests)

file(GLOB_RECURSE UNIT_TESTS "*.cpp")
foreach(ut IN LISTS UNIT_TESTS)
  te_get_target_name(target "${ut}")
  add_executable(test.${target} EXCLUDE_FROM_ALL "${ut}")
  te_set_test_properties(test.${target})
  add_test(test.${target} test.${target})
  add_dependencies(tests test.${target})
endforeach()
