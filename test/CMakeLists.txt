# Copyright Louis Dionne 2017
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

find_package(Awful QUIET)
if (NOT TARGET awful)
  message(WARNING "The Awful library is not found; unit tests won't be available.")
  return()
endif()

add_custom_target(tests
  COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
  COMMENT "Build and run all the unit tests."
  USES_TERMINAL)
add_dependencies(check tests)

# Generate tests that include each public header.
include(TestHeaders)
file(GLOB_RECURSE HEADERS RELATIVE "${PROJECT_SOURCE_DIR}/include"
                                   "${PROJECT_SOURCE_DIR}/include/*.hpp")
add_header_test(test.headers EXCLUDE_FROM_ALL HEADERS ${HEADERS})
target_link_libraries(test.headers PRIVATE Dyno::dyno)
add_dependencies(tests test.headers)

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

  dyno_set_common_properties(${target})
  target_link_libraries(${target} PRIVATE awful)
endforeach()

# Add the deployment test, which checks that we can indeed install dyno and
# then use `find_package` to depend on it from another CMake project.
include(ExternalProject)
set(DYNO_FAKE_INSTALL_DIR "${PROJECT_BINARY_DIR}/fakeroot")
ExternalProject_Add(test.deploy.fakeroot
  SOURCE_DIR "${PROJECT_SOURCE_DIR}"
  EXCLUDE_FROM_ALL TRUE
  BUILD_ALWAYS TRUE
  INSTALL_DIR "${DYNO_FAKE_INSTALL_DIR}"
  CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>
             -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
             -DCMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH}
             -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
  TEST_COMMAND ""      # Disable test step
  UPDATE_COMMAND ""    # Disable source work-tree update
)

add_custom_target(test.deploy
  DEPENDS test.deploy.fakeroot
  COMMAND ${CMAKE_COMMAND} -E remove_directory "${CMAKE_CURRENT_BINARY_DIR}/deploy"
  COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_CURRENT_BINARY_DIR}/deploy"
  COMMAND ${CMAKE_COMMAND} -E chdir "${CMAKE_CURRENT_BINARY_DIR}/deploy"
            ${CMAKE_COMMAND} "${CMAKE_CURRENT_SOURCE_DIR}/deploy"
                             -DCMAKE_CXX_COMPILER="${CMAKE_CXX_COMPILER}"
                             -DCMAKE_PREFIX_PATH="${CMAKE_PREFIX_PATH}\;${DYNO_FAKE_INSTALL_DIR}"
                             -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
  COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_BINARY_DIR}/deploy"
)
add_test(NAME test.deploy
         COMMAND ${CMAKE_COMMAND} --build "${PROJECT_BINARY_DIR}" --target test.deploy)
