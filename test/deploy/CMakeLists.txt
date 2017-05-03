# Copyright Louis Dionne 2017
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

cmake_minimum_required(VERSION 3.0)
project(external CXX)
find_package(Dyno REQUIRED)

# TODO: It's not very neat that we have to find the dependencies ourselves, but
# CMake exports are not transitive. See https://cmake.org/pipermail/cmake/2016-June/063773.html.
find_package(Hana REQUIRED)
find_package(CallableTraits REQUIRED)

add_executable(main main.cpp)
target_link_libraries(main dyno)
