# Copyright Louis Dionne 2017
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

find_package(benchmark) # This is GoogleBenchmark
if (NOT TARGET benchmark::benchmark)
  message(WARNING "The Google Benchmark library is not found; benchmarks won't be available.")
  return()
endif()

add_custom_target(benchmarks COMMENT "Build and run all the benchmarks.")

function(add_benchmark benchmark)
  dyno_get_target_name(target "${benchmark}")
  add_executable(${target}.exe EXCLUDE_FROM_ALL "${benchmark}")
  dyno_set_test_properties(${target}.exe)
  target_compile_options(${target}.exe PRIVATE -O3)
  target_link_libraries(${target}.exe PRIVATE benchmark::benchmark)
  add_custom_target(${target} COMMAND ${target}.exe DEPENDS ${target}.exe USES_TERMINAL)
  add_dependencies(benchmarks ${target})
endfunction()

file(GLOB_RECURSE benchmarks RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "*.cpp")
list(REMOVE_ITEM benchmarks "any_iterator.cpp")
foreach(benchmark IN LISTS benchmarks)
  add_benchmark("${benchmark}")
endforeach()

find_package(Boost)
find_package(mpark_variant)
if (NOT TARGET Boost::boost)
  message(STATUS "Boost headers were not found; benchmark.any_iterator not available")
elseif(NOT TARGET mpark_variant)
  message(STATUS "MPark.Variant not found; benchmark.any_iterator not available")
else()
  add_benchmark(any_iterator.cpp)
  target_link_libraries(benchmark.any_iterator.exe PRIVATE Boost::boost mpark_variant)
endif()
