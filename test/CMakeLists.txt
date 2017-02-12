# Copyright Louis Dionne 2017
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

add_custom_target(tests
  COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
  COMMENT "Build and run all the unit tests.")

# Generate tests that include each public header.
include(TestHeaders)
file(GLOB_RECURSE HEADERS RELATIVE "${TE_SOURCE_DIR}/include"
                                   "${TE_SOURCE_DIR}/include/*.hpp")
generate_standalone_header_tests(HEADERS ${HEADERS} LINK_LIBRARIES te
                                 MASTER_TARGET tests EXCLUDE_FROM_ALL)


include(CompileFailTest)

# Add all the regular unit tests. When a test has `.fail` in its name, we
# create a test that succeeds whenever the test fails to build.
file(GLOB_RECURSE UNIT_TESTS "*.cpp")
foreach(ut IN LISTS UNIT_TESTS)
  te_get_target_name(target "${ut}")

  if (target MATCHES "[.]fail")
    compile_fail("${target}" "${ut}")
  else()
    add_executable(${target} EXCLUDE_FROM_ALL "${ut}")
    add_test(${target} ${target})
    add_dependencies(tests ${target})
  endif()

  te_set_test_properties(${target})
endforeach()
