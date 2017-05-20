// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include "vtables.hpp"


inline void escape(void* v) {
  asm volatile("" : : "g"(v) : "memory");
}

template <typename Any>
static void BM_any_1_function(benchmark::State& state) {
  Any a{0};
  int const N = state.range(0);
  while (state.KeepRunning()) {
    for (int i = 0; i != N; ++i) {
      escape(&a);
      a.f1();
    }
  }
}

template <typename Any>
static void BM_any_2_function(benchmark::State& state) {
  Any a{0};
  int const N = state.range(0);
  while (state.KeepRunning()) {
    for (int i = 0; i != N; ++i) {
      escape(&a);
      a.f1();
      a.f2();
    }
  }
}

template <typename Any>
static void BM_any_3_function(benchmark::State& state) {
  Any a{0};
  int const N = state.range(0);
  while (state.KeepRunning()) {
    for (int i = 0; i != N; ++i) {
      escape(&a);
      a.f1();
      a.f2();
      a.f3();
    }
  }
}

template <typename Any>
static void BM_any_4_function(benchmark::State& state) {
  Any a{0};
  int const N = state.range(0);
  while (state.KeepRunning()) {
    for (int i = 0; i != N; ++i) {
      escape(&a);
      a.f1();
      a.f2();
      a.f3();
      a.f4();
    }
  }
}

template <typename Any>
static void BM_any_5_function(benchmark::State& state) {
  Any a{0};
  int const N = state.range(0);
  while (state.KeepRunning()) {
    for (int i = 0; i != N; ++i) {
      escape(&a);
      a.f1();
      a.f2();
      a.f3();
      a.f4();
      a.f5();
    }
  }
}

volatile int N = 1000;

BENCHMARK_TEMPLATE(BM_any_1_function, handrolled_classic::any   )->Arg(N);
BENCHMARK_TEMPLATE(BM_any_1_function, handrolled_remote::any    )->Arg(N);
BENCHMARK_TEMPLATE(BM_any_1_function, handrolled_local::any     )->Arg(N);
BENCHMARK_TEMPLATE(BM_any_1_function, classic::any              )->Arg(N);
BENCHMARK_TEMPLATE(BM_any_1_function, dyno_remote::any          )->Arg(N);
BENCHMARK_TEMPLATE(BM_any_1_function, dyno_local::any           )->Arg(N);

BENCHMARK_TEMPLATE(BM_any_2_function, handrolled_classic::any   )->Arg(N);
BENCHMARK_TEMPLATE(BM_any_2_function, handrolled_remote::any    )->Arg(N);
BENCHMARK_TEMPLATE(BM_any_2_function, handrolled_local::any     )->Arg(N);
BENCHMARK_TEMPLATE(BM_any_2_function, classic::any              )->Arg(N);
BENCHMARK_TEMPLATE(BM_any_2_function, dyno_remote::any          )->Arg(N);
BENCHMARK_TEMPLATE(BM_any_2_function, dyno_local::any           )->Arg(N);

BENCHMARK_TEMPLATE(BM_any_3_function, handrolled_classic::any   )->Arg(N);
BENCHMARK_TEMPLATE(BM_any_3_function, handrolled_remote::any    )->Arg(N);
BENCHMARK_TEMPLATE(BM_any_3_function, handrolled_local::any     )->Arg(N);
BENCHMARK_TEMPLATE(BM_any_3_function, classic::any              )->Arg(N);
BENCHMARK_TEMPLATE(BM_any_3_function, dyno_remote::any          )->Arg(N);
BENCHMARK_TEMPLATE(BM_any_3_function, dyno_local::any           )->Arg(N);

BENCHMARK_TEMPLATE(BM_any_4_function, handrolled_classic::any   )->Arg(N);
BENCHMARK_TEMPLATE(BM_any_4_function, handrolled_remote::any    )->Arg(N);
BENCHMARK_TEMPLATE(BM_any_4_function, handrolled_local::any     )->Arg(N);
BENCHMARK_TEMPLATE(BM_any_4_function, classic::any              )->Arg(N);
BENCHMARK_TEMPLATE(BM_any_4_function, dyno_remote::any          )->Arg(N);
BENCHMARK_TEMPLATE(BM_any_4_function, dyno_local::any           )->Arg(N);

BENCHMARK_TEMPLATE(BM_any_5_function, handrolled_classic::any   )->Arg(N);
BENCHMARK_TEMPLATE(BM_any_5_function, handrolled_remote::any    )->Arg(N);
BENCHMARK_TEMPLATE(BM_any_5_function, handrolled_local::any     )->Arg(N);
BENCHMARK_TEMPLATE(BM_any_5_function, classic::any              )->Arg(N);
BENCHMARK_TEMPLATE(BM_any_5_function, dyno_remote::any          )->Arg(N);
BENCHMARK_TEMPLATE(BM_any_5_function, dyno_local::any           )->Arg(N);

BENCHMARK_MAIN();
