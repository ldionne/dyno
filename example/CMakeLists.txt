# Copyright Louis Dionne 2017
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

add_custom_target(examples COMMENT "Build all the examples.")
add_dependencies(check examples)

file(GLOB_RECURSE EXAMPLES "*.cpp")
foreach(example IN LISTS EXAMPLES)
  te_get_target_name(target "${example}")
  add_executable(example.${target} EXCLUDE_FROM_ALL "${example}")
  te_set_test_properties(example.${target})
  add_test(example.${target} example.${target})
  add_dependencies(examples example.${target})
endforeach()
