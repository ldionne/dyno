// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include "model.hpp"

#include <dyno.hpp>

#include <benchmark/benchmark.h>
using namespace dyno::literals;


// This benchmark measures the overhead of dispatching virtual calls using
// different vtable policies, and inheritance.

template <typename VTablePolicy>
static void BM_dispatch4(benchmark::State& state) {
  unsigned int x = 0;
  model<VTablePolicy> m{x};
  int const N = state.range(0);
  while (state.KeepRunning()) {
    for (int i = 0; i != N; ++i) {
      benchmark::DoNotOptimize(m);
      m.f1();
      m.f2();
      m.f3();
      m.f4();
    }
  }
}

template <char const* ...InlineMethods>
using inline_only = dyno::vtable<
  dyno::local<dyno::only<InlineMethods...>>,
  dyno::remote<dyno::everything_else>
>;

static constexpr int N = 100;
BENCHMARK_TEMPLATE(BM_dispatch4, inheritance_tag)->Arg(N);
BENCHMARK_TEMPLATE(BM_dispatch4, inline_only<>)->Arg(N);
BENCHMARK_TEMPLATE(BM_dispatch4, inline_only<"f1"_s>)->Arg(N);
BENCHMARK_TEMPLATE(BM_dispatch4, inline_only<"f1"_s, "f2"_s>)->Arg(N);
BENCHMARK_TEMPLATE(BM_dispatch4, inline_only<"f1"_s, "f2"_s, "f3"_s>)->Arg(N);
BENCHMARK_TEMPLATE(BM_dispatch4, inline_only<"f1"_s, "f2"_s, "f3"_s, "f4"_s>)->Arg(N);
BENCHMARK_MAIN();
