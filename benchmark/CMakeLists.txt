# Copyright Louis Dionne 2017
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

if (NOT TARGET dependency.GoogleBenchmark)
  message(WARNING "The Google Benchmark library is not found; benchmarks won't be available.")
  return()
endif()

add_custom_target(benchmarks COMMENT "Build and run all the benchmarks.")

function(add_benchmark benchmark)
  dyno_get_target_name(target "${benchmark}")
  add_executable(${target}.exe EXCLUDE_FROM_ALL "${benchmark}")
  dyno_set_test_properties(${target}.exe)
  target_compile_options(${target}.exe PRIVATE -O3)
  target_link_libraries(${target}.exe PRIVATE dependency.GoogleBenchmark)
  add_custom_target(${target} COMMAND ${target}.exe DEPENDS ${target}.exe)
  add_dependencies(benchmarks ${target})
endfunction()

foreach(benchmark n_functions storage.swap.different_types storage.swap.same_type)
  add_benchmark(${benchmark}.cpp)
endforeach()

if (NOT TARGET dependency.BoostTypeErasure OR NOT TARGET dependency.BoostVariant)
  message(STATUS "Boost.TypeErasure and/or Boost.Variant not found; benchmark.any_iterator not available")
else()
  add_benchmark(any_iterator.cpp)
  target_link_libraries(benchmark.any_iterator.exe PRIVATE dependency.BoostTypeErasure)
endif()
