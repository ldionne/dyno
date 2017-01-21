# Copyright Louis Dionne 2017
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

if (NOT TARGET ${DEPENDENCY_google_benchmark})
  message(WARNING "The Google Benchmark library is not found; benchmarks won't be available.")
  return()
endif()

add_custom_target(benchmarks COMMENT "Build and run all the benchmarks.")

file(GLOB_RECURSE BENCHMARKS "*.cpp")
foreach(benchmark IN LISTS BENCHMARKS)
  te_get_target_name(target "${benchmark}")
  add_executable(${target}.exe EXCLUDE_FROM_ALL "${benchmark}")
  te_set_test_properties(${target}.exe)
  target_compile_options(${target}.exe PRIVATE -O3)
  target_link_libraries(${target}.exe PRIVATE ${DEPENDENCY_google_benchmark})
  add_custom_target(${target} COMMAND ${target}.exe DEPENDS ${target}.exe)
  add_dependencies(benchmarks ${target})
endforeach()
