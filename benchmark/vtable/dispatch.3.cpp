// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include "model.hpp"

#include <dyno.hpp>

#include <benchmark/benchmark.h>
using namespace dyno::literals;


// This benchmark measures the overhead of dispatching virtual calls using
// different vtable policies.

template <typename ...InlineMethods>
static void BM_dispatch3(benchmark::State& state) {
  using VTablePolicy = dyno::vtable<
    dyno::local<dyno::only<InlineMethods...>>,
    dyno::remote<dyno::everything_else>
  >;
  unsigned int x = 0;
  model<VTablePolicy> m{x};
  int const N = state.range(0);
  while (state.KeepRunning()) {
    for (int i = 0; i != N; ++i) {
      benchmark::DoNotOptimize(m);
      m.f1();
      m.f2();
      m.f3();
    }
  }
}

static constexpr int N = 100;
BENCHMARK(BM_dispatch3)->Arg(N);
BENCHMARK_TEMPLATE(BM_dispatch3, decltype("f1"_s))->Arg(N);
BENCHMARK_TEMPLATE(BM_dispatch3, decltype("f1"_s), decltype("f2"_s))->Arg(N);
BENCHMARK_TEMPLATE(BM_dispatch3, decltype("f1"_s), decltype("f2"_s), decltype("f3"_s))->Arg(N);
BENCHMARK_MAIN();
