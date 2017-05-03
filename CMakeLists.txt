# Copyright Louis Dionne 2017
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

cmake_minimum_required(VERSION 3.8)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

project(DYNO VERSION 0.0.1 LANGUAGES CXX)

# Setup the `dyno` library target, assuming the dependencies are provided.
add_library(dyno INTERFACE)
target_compile_features(dyno INTERFACE cxx_std_14)
target_include_directories(dyno INTERFACE include)
find_package(Hana REQUIRED)
find_package(CallableTraits REQUIRED)
target_link_libraries(dyno INTERFACE hana callable_traits)

include(CheckCXXCompilerFlag)
check_cxx_compiler_flag("-Wno-gnu-string-literal-operator-template" DYNO_HAS_WNO_GNU_STRING_UDL)
# GCC pretends to have the flag, but produces a "unrecognized command line option"
# warning when we use it.
if (DYNO_HAS_WNO_GNU_STRING_UDL AND NOT ${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
  target_compile_options(dyno INTERFACE -Wno-gnu-string-literal-operator-template)
endif()

# GCC needs -fpermissive to allow template specializations out of the namespace
# where the base template was declared, even though C++ allows it.
if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
  target_compile_options(dyno INTERFACE -fpermissive)
endif()


# All unit tests and examples are given those properties.
find_package(Awful REQUIRED)
function(dyno_set_test_properties target)
  target_link_libraries(${target} PRIVATE dyno awful)
  set_target_properties(${target} PROPERTIES CXX_EXTENSIONS NO)
  macro(setflag testname flag)
      check_cxx_compiler_flag(${flag} ${testname})
      if (${testname})
          target_compile_options(${target} PRIVATE ${flag})
      endif()
  endmacro()
  setflag(DYNO_HAS_PEDANTIC       -pedantic)
  setflag(DYNO_HAS_WALL           -Wall)
  setflag(DYNO_HAS_WEXTRA         -Wextra)
endfunction()

# Return the target name associated to a source file. If the path of the
# source file relative from the root of the project is `path/to/file.cpp`,
# the target name associated to it will be `path.to.file`.
function(dyno_get_target_name out file)
  if (NOT IS_ABSOLUTE ${file})
    set(file "${CMAKE_CURRENT_SOURCE_DIR}/${file}")
  endif()
  file(RELATIVE_PATH _relative "${DYNO_SOURCE_DIR}" "${file}")
  string(REPLACE ".cpp" "" _name "${_relative}")
  string(REGEX REPLACE "/" "." _name "${_name}")
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
