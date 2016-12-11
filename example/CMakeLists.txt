# Copyright Louis Dionne 2016
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

add_custom_target(examples COMMENT "Build all the examples.")
add_dependencies(check examples)

function(te_set_target_properties target)
  target_link_libraries(${target} PRIVATE te)
  set_target_properties(${target} PROPERTIES CXX_EXTENSIONS NO)
  target_compile_definitions(${target} PRIVATE BOOST_HANA_CONFIG_ENABLE_STRING_UDL)
  target_compile_options(${target} PRIVATE -Wno-gnu-string-literal-operator-template)
endfunction()

foreach(target any_iterator)
  add_executable(example.${target} EXCLUDE_FROM_ALL "${target}.cpp")
  te_set_target_properties(example.${target})
  add_test(example.${target} example.${target})
  add_dependencies(examples example.${target})
endforeach()
