# Copyright Louis Dionne 2017
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

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
