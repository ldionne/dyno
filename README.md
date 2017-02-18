# An experimental type erasure library

## Disclaimer: At this point, this is just a toy project and is useless for any purpose except curiosity.

## Dependencies
The library depends on [Boost.Hana][] and [CallableTraits][]. The unit tests
depend on [libawful][] and the benchmarks on [Google Benchmark][], but you don't
need them to use the library. For local development, all the dependencies are
pulled automatically.


## Building the library
`te` is a header-only library, so there's nothing to build per-se. Just add the
`include/` directory to your compiler's header search path (and make sure the
dependencies are satisfied), and you're good to go. However, there are unit
tests, examples and benchmarks that can be built:

```sh
(mkdir build && cd build && cmake ..)     # Setup the build directory
cmake --build build --target dependencies # Fetch and build all the dependencies

cmake --build build --target examples   # Build and run the examples
cmake --build build --target tests      # Build and run the unit tests
cmake --build build --target check      # Does both examples and tests
cmake --build build --target benchmarks # Build and run the benchmarks
```


<!-- Links -->
[Boost.Hana]: https://github.com/boostorg/hana
[CallableTraits]: https://github.com/badair/callable_traits
[Google Benchmark]: https://github.com/google/benchmark
[libawful]: https://github.com/ldionne/libawful
