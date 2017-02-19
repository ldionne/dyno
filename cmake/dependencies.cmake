# Copyright Louis Dionne 2017
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

# This file must define the following targets, each of which can be linked
# against to get the right includes and/or link libraries:
#
#   dependency.BoostTypeErasure
#   dependency.CallableTraits
#   dependency.GoogleBenchmark
#   dependency.Hana
#   dependency.libawful
#
# It also defines the following target, which can be used to install all the
# dependencies:
#
#   dependencies
#
# Since C++ lacks a standardized or even agreed-upon dependency management
# system, this makes it easy to use this library with any system by simply
# providing the dependencies here.

include(ExternalProject)
add_custom_target(dependencies COMMENT "Fetch and build all the dependencies")

# Boost.Hana
ExternalProject_Add(install.Hana EXCLUDE_FROM_ALL 1
  URL https://github.com/boostorg/hana/archive/develop.zip
  TIMEOUT 120
  PREFIX "${CMAKE_BINARY_DIR}/dependencies/Hana"
  CONFIGURE_COMMAND "" # Disable configure step
  BUILD_COMMAND ""     # Disable build step
  INSTALL_COMMAND ""   # Disable install step
  TEST_COMMAND ""      # Disable test step
  UPDATE_COMMAND ""    # Disable source work-tree update
)
add_dependencies(dependencies install.Hana)
ExternalProject_Get_Property(install.Hana SOURCE_DIR)
add_library(dependency.Hana INTERFACE)
target_include_directories(dependency.Hana INTERFACE ${SOURCE_DIR}/include)


# [Boost.]CallableTraits
ExternalProject_Add(install.CallableTraits EXCLUDE_FROM_ALL 1
  URL https://github.com/badair/callable_traits/archive/master.zip
  TIMEOUT 120
  PREFIX "${CMAKE_BINARY_DIR}/dependencies/CallableTraits"
  CONFIGURE_COMMAND "" # Disable configure step
  BUILD_COMMAND ""     # Disable build step
  INSTALL_COMMAND ""   # Disable install step
  TEST_COMMAND ""      # Disable test step
  UPDATE_COMMAND ""    # Disable source work-tree update
)
add_dependencies(dependencies install.CallableTraits)
ExternalProject_Get_Property(install.CallableTraits SOURCE_DIR)
add_library(dependency.CallableTraits INTERFACE)
target_include_directories(dependency.CallableTraits INTERFACE ${SOURCE_DIR}/include)


# libawful
ExternalProject_Add(install.libawful EXCLUDE_FROM_ALL 1
  URL https://github.com/ldionne/libawful/archive/master.zip
  TIMEOUT 120
  PREFIX "${CMAKE_BINARY_DIR}/dependencies/libawful"
  CONFIGURE_COMMAND "" # Disable configure step
  BUILD_COMMAND ""     # Disable build step
  INSTALL_COMMAND ""   # Disable install step
  TEST_COMMAND ""      # Disable test step
  UPDATE_COMMAND ""    # Disable source work-tree update
)
add_dependencies(dependencies install.libawful)
ExternalProject_Get_Property(install.libawful SOURCE_DIR)
add_library(dependency.libawful INTERFACE)
target_include_directories(dependency.libawful INTERFACE ${SOURCE_DIR}/include)


# Google Benchmark
ExternalProject_Add(install.GoogleBenchmark EXCLUDE_FROM_ALL 1
  URL https://github.com/google/benchmark/archive/master.zip
  TIMEOUT 120
  PREFIX "${CMAKE_BINARY_DIR}/dependencies/GoogleBenchmark"
  CMAKE_ARGS "-DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}"
             "-DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>"
             "-DCMAKE_BUILD_TYPE=Release" # Always build in release mode
  UPDATE_COMMAND "" # Disable source work-tree update
)
add_dependencies(dependencies install.GoogleBenchmark)
ExternalProject_Get_Property(install.GoogleBenchmark INSTALL_DIR)
add_library(_libbenchmark STATIC IMPORTED)
set_target_properties(_libbenchmark PROPERTIES IMPORTED_LOCATION ${INSTALL_DIR}/lib/libbenchmark.a)
add_library(dependency.GoogleBenchmark INTERFACE)
target_include_directories(dependency.GoogleBenchmark INTERFACE ${INSTALL_DIR}/include)
target_link_libraries(dependency.GoogleBenchmark INTERFACE _libbenchmark)


# Boost.TypeErasure
find_package(Boost)
if (Boost_FOUND)
  add_library(dependency.BoostTypeErasure INTERFACE)
  target_include_directories(dependency.BoostTypeErasure INTERFACE ${Boost_INCLUDE_DIRS})
endif()
