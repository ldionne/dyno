# Copyright Louis Dionne 2017
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

add_custom_target(tests
  COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
  COMMENT "Build and run all the unit tests.")

# Generate tests that include each public header.
include(TestHeaders)
file(GLOB_RECURSE HEADERS RELATIVE "${PROJECT_SOURCE_DIR}/include"
                                   "${PROJECT_SOURCE_DIR}/include/*.hpp")
generate_standalone_header_tests(HEADERS ${HEADERS} LINK_LIBRARIES Dyno::dyno
                                 MASTER_TARGET tests EXCLUDE_FROM_ALL)

# Add the special `test.poly.allocator` target, which depends on Boost.Interprocess.
find_package(Boost)
add_executable(test.poly.allocator EXCLUDE_FROM_ALL "poly.allocator.cpp")
target_link_libraries(test.poly.allocator PRIVATE Boost::boost)
dyno_set_test_properties(test.poly.allocator)
add_test(test.poly.allocator test.poly.allocator)
add_dependencies(tests test.poly.allocator)

# Add all the regular unit tests (that have not already been added above).
# When a test has `.fail` in its name, we create a test that succeeds
# whenever the test fails to build.
include(CompileFailTest)
file(GLOB_RECURSE UNIT_TESTS "*.cpp")
file(GLOB_RECURSE EXCLUDED_UNIT_TESTS "deploy/*.cpp")
list(REMOVE_ITEM UNIT_TESTS ${EXCLUDED_UNIT_TESTS})
foreach(ut IN LISTS UNIT_TESTS)
  dyno_get_target_name(target "${ut}")
  if (TARGET ${target})
    continue()
  endif()

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
include(ExternalProject)
set(DYNO_FAKE_INSTALL_DIR "${PROJECT_BINARY_DIR}/fakeroot")
ExternalProject_Add(test.deploy.fakeroot
  SOURCE_DIR "${PROJECT_SOURCE_DIR}"
  EXCLUDE_FROM_ALL TRUE
  BUILD_ALWAYS TRUE
  INSTALL_DIR "${DYNO_FAKE_INSTALL_DIR}"
  CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>
             -DCMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH}
  TEST_COMMAND ""      # Disable test step
  UPDATE_COMMAND ""    # Disable source work-tree update
)

add_custom_target(test.deploy
  DEPENDS test.deploy.fakeroot
  COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_CURRENT_BINARY_DIR}/deploy"
  COMMAND ${CMAKE_COMMAND} -E chdir "${CMAKE_CURRENT_BINARY_DIR}/deploy"
            ${CMAKE_COMMAND} "${CMAKE_CURRENT_SOURCE_DIR}/deploy"
                             -DCMAKE_CXX_COMPILER="${CMAKE_CXX_COMPILER}"
                             -DCMAKE_PREFIX_PATH="${CMAKE_PREFIX_PATH}\;${DYNO_FAKE_INSTALL_DIR}"
  COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_BINARY_DIR}/deploy"
)
add_dependencies(tests test.deploy)
