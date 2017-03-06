# Copyright Louis Dionne 2017
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

# Generates a unit test target that succeeds if the compilation of the
# specified source file fails.
#
# If a line containing `MESSAGE[...]` exists in the source file, then the
# target will make sure that `...` is contained in the output of the test.
# This allows one to test that the right static assertions are triggered.
# For example:
#
#   #include <type_traits>
#
#   template <typename T>
#   void f() { static_assert(!std::is_void<T>{}, "hey, don't do that!"); }
#
#   // MESSAGE[hey, don't do that!]
#   int main() { f<void>(); }
#
#
# Parameters
# ----------
# target:
#   Name of the test target to create.
#
# file:
#   Path of the source file that should be compiled.
function(compile_fail target file)
  file(STRINGS "${file}" message REGEX "^.*MESSAGE\\[.*\\]$")
  string(REGEX REPLACE "^.*MESSAGE\\[(.*)\\]$" "\\1" message "${message}")
  string(REPLACE ";" "\\;" message "${message}") # Escape potential ; characters

  add_executable(${target} EXCLUDE_FROM_ALL "${file}")
  add_test(NAME ${target}
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR}
                             --target ${target}
                             --config $<CONFIGURATION>)

  if (message)
    set_tests_properties(${target} PROPERTIES PASS_REGULAR_EXPRESSION "${message}")
  else()
    set_tests_properties(${target} PROPERTIES WILL_FAIL TRUE)
  endif()

  # Whenever the input file for a `configure_file` command is changed, a CMake
  # rebuild is triggered. We use this to make sure that we regenerate the test
  # definitions whenever a test file is changed. Otherwise, we don't pick up
  # changes in the failure message.
  configure_file("${file}" "${CMAKE_BINARY_DIR}/CompileFailTest.sentinel")
endfunction()
