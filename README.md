# An experimental type erasure library

## Disclaimer: At this point, this is just a toy project and is useless for any purpose except curiosity.

## Dependencies
The library depends on [Boost.Hana][], [CallableTraits][]. The benchmarks also
depend on [Google Benchmark][], but you don't need it to use the library.


## Building the library
`te` is a header-only library, so there's nothing to build per-se. Just add the
`include/` directory to your compiler's header search path (and make sure the
dependencies are satisfied), and you're good to go. However, there are unit
tests, examples and benchmarks that can be built:

```sh
# Setup the build directory. You might want to add some options to the commands here.
(mkdir build && cd build && conan install .. && cmake ..)

cmake --build build --target examples   # Build and run the examples
cmake --build build --target tests      # Build and run the unit tests
cmake --build build --target check      # Does both examples and tests
cmake --build build --target benchmarks # Build and run the benchmarks (requires Google Benchmark)
```


<!-- Links -->
[Boost.Hana]: https://github.com/boostorg/hana
[CallableTraits]: https://github.com/badair/callable_traits
[Google Benchmark]: https://github.com/google/benchmark
