# Copyright Louis Dionne 2017
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

add_custom_target(examples
  COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
  COMMENT "Build and run all the examples."
  USES_TERMINAL)
add_dependencies(check examples)

file(GLOB_RECURSE EXAMPLES "*.cpp")
foreach(example IN LISTS EXAMPLES)
  dyno_get_target_name(target "${example}")
  add_executable(${target} EXCLUDE_FROM_ALL "${example}")
  dyno_set_common_properties(${target})
  add_test(${target} ${target})
  add_dependencies(examples ${target})
endforeach()
