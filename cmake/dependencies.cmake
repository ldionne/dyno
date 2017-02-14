# Copyright Louis Dionne 2017
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

# This file must define the following variables, each of which should expand
# to a target name that can be linked against:
#   DEPENDENCY_hana
#   DEPENDENCY_callable_traits
#   DEPENDENCY_google_benchmark
#   DEPENDENCY_libawful
#   DEPENDENCY_boost_type_erasure
#
# Since C++ lacks a standardized or even agreed-upon dependency management
# system, this makes it easy to use this library with any system by simply
# providing the dependencies here.

include(ExternalProject)
ExternalProject_Add(install-Hana EXCLUDE_FROM_ALL 1
  URL https://github.com/boostorg/hana/archive/develop.zip
  TIMEOUT 120
  PREFIX "${CMAKE_BINARY_DIR}/dependencies/hana"
  CONFIGURE_COMMAND "" # Disable configure step
  BUILD_COMMAND ""     # Disable build step
  INSTALL_COMMAND ""   # Disable install step
  TEST_COMMAND ""      # Disable test step
  UPDATE_COMMAND ""    # Disable source work-tree update
)
ExternalProject_Get_Property(install-Hana SOURCE_DIR)
add_library(hana INTERFACE)
target_include_directories(hana INTERFACE ${SOURCE_DIR}/include)
add_dependencies(hana install-Hana)
set(DEPENDENCY_hana hana)

ExternalProject_Add(install-CallableTraits EXCLUDE_FROM_ALL 1
  URL https://github.com/badair/callable_traits/archive/master.zip
  TIMEOUT 120
  PREFIX "${CMAKE_BINARY_DIR}/dependencies/callable_traits"
  CONFIGURE_COMMAND "" # Disable configure step
  BUILD_COMMAND ""     # Disable build step
  INSTALL_COMMAND ""   # Disable install step
  TEST_COMMAND ""      # Disable test step
  UPDATE_COMMAND ""    # Disable source work-tree update
)
ExternalProject_Get_Property(install-CallableTraits SOURCE_DIR)
add_library(callable_traits INTERFACE)
target_include_directories(callable_traits INTERFACE ${SOURCE_DIR}/include)
add_dependencies(callable_traits install-CallableTraits)
set(DEPENDENCY_callable_traits callable_traits)

ExternalProject_Add(install-libawful EXCLUDE_FROM_ALL 1
  URL https://github.com/ldionne/libawful/archive/master.zip
  TIMEOUT 120
  PREFIX "${CMAKE_BINARY_DIR}/dependencies/libawful"
  CONFIGURE_COMMAND "" # Disable configure step
  BUILD_COMMAND ""     # Disable build step
  INSTALL_COMMAND ""   # Disable install step
  TEST_COMMAND ""      # Disable test step
  UPDATE_COMMAND ""    # Disable source work-tree update
)
ExternalProject_Get_Property(install-libawful SOURCE_DIR)
add_library(libawful INTERFACE)
target_include_directories(libawful INTERFACE ${SOURCE_DIR}/include)
add_dependencies(libawful install-libawful)
set(DEPENDENCY_libawful libawful)

find_package(Boost COMPONENTS type_erasure)
if (Boost_FOUND)
  set(DEPENDENCY_boost_type_erasure Boost::type_erasure)
endif()

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_define_targets()
set(DEPENDENCY_google_benchmark CONAN_PKG::google-benchmark)
