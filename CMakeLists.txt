# Copyright Louis Dionne 2017
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

cmake_minimum_required(VERSION 3.7)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

project(TE VERSION 0.0.1 LANGUAGES CXX)
# TODO: Set these as interface properties when supported
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED YES)


# Setup the `te` library target, assuming the dependencies are provided.
include(dependencies)
add_library(te INTERFACE)
target_include_directories(te INTERFACE include)
target_compile_options(te INTERFACE -Wno-gnu-string-literal-operator-template)
target_link_libraries(te INTERFACE ${DEPENDENCY_hana} ${DEPENDENCY_callable_traits})


# All unit tests and examples are given those properties.
function(te_set_test_properties target)
  target_link_libraries(${target} PRIVATE te ${DEPENDENCY_libawful})
  set_target_properties(${target} PROPERTIES CXX_EXTENSIONS NO)
endfunction()

# Return the target name associated to a source file. If the path of the
# source file relative from the root of the project is `path/to/file.cpp`,
# the target name associated to it will be `path.to.file`.
function(te_get_target_name out file)
  if (NOT IS_ABSOLUTE ${file})
    set(file "${CMAKE_CURRENT_SOURCE_DIR}/${file}")
  endif()
  file(RELATIVE_PATH _relative ${TE_SOURCE_DIR} ${file})
  string(REPLACE ".cpp" "" _name ${_relative})
  string(REGEX REPLACE "/" "." _name ${_name})
  set(${out} "${_name}" PARENT_SCOPE)
endfunction()


# Setup subdirectories
enable_testing()
add_subdirectory(benchmark)
add_subdirectory(example)
add_subdirectory(test)

# Setup the `check` convenience target, which is equivalent to examples + tests.
add_custom_target(check DEPENDS examples tests
  COMMENT "Build and run all the tests and examples.")
