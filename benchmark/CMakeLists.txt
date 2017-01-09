# Copyright Louis Dionne 2017
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

add_custom_target(benchmarks COMMENT "Build all the benchmarks.")
add_dependencies(check benchmarks)

file(GLOB_RECURSE BENCHMARKS "*.cpp")
foreach(benchmark IN LISTS BENCHMARKS)
  te_get_target_name(target "${benchmark}")
  add_executable(${target} EXCLUDE_FROM_ALL "${benchmark}")
  te_set_test_properties(${target})
  target_compile_options(${target} PRIVATE -O3)
  add_test(${target} ${target})
  add_dependencies(benchmarks ${target})
endforeach()
