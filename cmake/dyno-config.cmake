# Copyright Louis Dionne 2017
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

include(CMakeFindDependencyMacro)
find_dependency(Hana REQUIRED)
find_dependency(CallableTraits REQUIRED)

if(NOT TARGET Dyno::dyno)
  include("${CMAKE_CURRENT_LIST_DIR}/dyno-targets.cmake")
endif()
