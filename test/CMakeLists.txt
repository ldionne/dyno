# Copyright Louis Dionne 2017
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

add_custom_target(tests COMMENT "Build all the unit tests.")
add_dependencies(check tests)

# Generate tests that include each public header.
file(GLOB_RECURSE HEADERS RELATIVE "${TE_SOURCE_DIR}/include"
                                   "${TE_SOURCE_DIR}/include/*.hpp")

add_custom_target(test.headers COMMENT "Build all the header-inclusion unit tests.")
add_dependencies(tests test.headers)
include(TestHeaders)
generate_standalone_header_tests(HEADERS ${HEADERS}
                                 LINK_LIBRARIES te
                                 MASTER_TARGET tests
                                 EXCLUDE_FROM_ALL)

# Add all the regular unit tests. When a test has `.fail` in its name, we
# create a test that succeeds whenever the test fails to build.
file(GLOB_RECURSE UNIT_TESTS "*.cpp")
foreach(ut IN LISTS UNIT_TESTS)
  te_get_target_name(target "${ut}")
  add_executable(${target} EXCLUDE_FROM_ALL "${ut}")
  te_set_test_properties(${target})

  if (target MATCHES "[.]fail")
    message(STATUS "ADDING TEST FAILURE UNIT TEST ${target}")
    add_test(NAME ${target}
      COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR}
                               --target ${target}
                               --config $<CONFIGURATION>)
    set_tests_properties(${target} PROPERTIES WILL_FAIL TRUE)
  else()
    add_test(${target} ${target})
    add_dependencies(tests ${target})
  endif()
endforeach()
