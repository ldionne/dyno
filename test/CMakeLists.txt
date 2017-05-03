# Copyright Louis Dionne 2017
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

add_custom_target(tests
  COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
  COMMENT "Build and run all the unit tests.")

# Generate tests that include each public header.
include(TestHeaders)
file(GLOB_RECURSE HEADERS RELATIVE "${DYNO_SOURCE_DIR}/include"
                                   "${DYNO_SOURCE_DIR}/include/*.hpp")
generate_standalone_header_tests(HEADERS ${HEADERS} LINK_LIBRARIES dyno
                                 MASTER_TARGET tests EXCLUDE_FROM_ALL)


include(CompileFailTest)

# Add all the regular unit tests. When a test has `.fail` in its name, we
# create a test that succeeds whenever the test fails to build.
file(GLOB_RECURSE UNIT_TESTS "*.cpp")
file(GLOB_RECURSE EXCLUDED_UNIT_TESTS "deploy/*.cpp")
list(REMOVE_ITEM UNIT_TESTS ${EXCLUDED_UNIT_TESTS})
foreach(ut IN LISTS UNIT_TESTS)
  dyno_get_target_name(target "${ut}")

  if (target MATCHES "[.]fail")
    compile_fail("${target}" "${ut}")
  else()
    add_executable(${target} EXCLUDE_FROM_ALL "${ut}")
    add_test(${target} ${target})
    add_dependencies(tests ${target})
  endif()

  dyno_set_test_properties(${target})
endforeach()

# Add the deployment test, which checks that we can indeed install `dyno` and
# then use the provided `DynoConfig.cmake` config file to use `dyno` from an
# external project.
add_custom_target(test.deploy
  COMMAND ${CMAKE_COMMAND} --build "${CMAKE_BINARY_DIR}" --target install
  COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_CURRENT_BINARY_DIR}/deploy"
  COMMAND ${CMAKE_COMMAND} -E chdir "${CMAKE_CURRENT_BINARY_DIR}/deploy"
            ${CMAKE_COMMAND} "${CMAKE_CURRENT_SOURCE_DIR}/deploy"
                             -DCMAKE_CXX_COMPILER="${CMAKE_CXX_COMPILER}"
                             -DCMAKE_PREFIX_PATH="${CMAKE_PREFIX_PATH}\;${CMAKE_INSTALL_PREFIX}"
  COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_BINARY_DIR}/deploy"
)
add_dependencies(tests test.deploy)
