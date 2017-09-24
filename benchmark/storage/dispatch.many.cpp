// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include "model.hpp"

#include <dyno.hpp>

#include <benchmark/benchmark.h>

#include <cstddef>
#include <type_traits>
#include <utility>
#include <vector>


// This benchmark measures the overhead of dispatching methods through a
// type-erased wrapper with different storage policies.

template <typename StoragePolicy, typename FirstHalf, typename SecondHalf>
static void BM_dispatch_many(benchmark::State& state) {
  std::vector<model<StoragePolicy>> models;
  for (int i = 0; i != state.range(0); ++i) {
    if (i % 2 == 0) {
      models.push_back(model<StoragePolicy>{FirstHalf{}});
    } else {
      models.push_back(model<StoragePolicy>{SecondHalf{}});
    }
  }
  benchmark::DoNotOptimize(models);
  while (state.KeepRunning()) {
    for (auto& model : models) {
      model.f1();
      model.f2();
      model.f3();
    }
  }
}

template <std::size_t Bytes>
using WithSize = std::aligned_storage_t<Bytes>;

static constexpr int N = 10;

// Always insert the same type in the type-erasure wrapper (may interact with
// branch prediction and caches).
BENCHMARK_TEMPLATE(BM_dispatch_many, inheritance_tag,         WithSize<4>, WithSize<4>)->Arg(N);
BENCHMARK_TEMPLATE(BM_dispatch_many, dyno::remote_storage,    WithSize<4>, WithSize<4>)->Arg(N);
BENCHMARK_TEMPLATE(BM_dispatch_many, dyno::sbo_storage<4>,    WithSize<4>, WithSize<4>)->Arg(N);
BENCHMARK_TEMPLATE(BM_dispatch_many, dyno::sbo_storage<8>,    WithSize<4>, WithSize<4>)->Arg(N);
BENCHMARK_TEMPLATE(BM_dispatch_many, dyno::sbo_storage<16>,   WithSize<4>, WithSize<4>)->Arg(N);
BENCHMARK_TEMPLATE(BM_dispatch_many, dyno::local_storage<16>, WithSize<4>, WithSize<4>)->Arg(N);

// For some reason, the benchmarks below for local_storage are much better
// when this benchmark is enabled than when it is not. TODO: Find out why.
BENCHMARK_TEMPLATE(BM_dispatch_many, dyno::local_storage<16>, WithSize<8>, WithSize<8>)->Arg(N);

// Insert two different types in the type-erasure wrapper to look at what happens
// with SBO.
BENCHMARK_TEMPLATE(BM_dispatch_many, inheritance_tag,         WithSize<8>, WithSize<16>)->Arg(N);
BENCHMARK_TEMPLATE(BM_dispatch_many, dyno::remote_storage,    WithSize<8>, WithSize<16>)->Arg(N);
BENCHMARK_TEMPLATE(BM_dispatch_many, dyno::sbo_storage<4>,    WithSize<8>, WithSize<16>)->Arg(N);
BENCHMARK_TEMPLATE(BM_dispatch_many, dyno::sbo_storage<8>,    WithSize<8>, WithSize<16>)->Arg(N);
BENCHMARK_TEMPLATE(BM_dispatch_many, dyno::sbo_storage<16>,   WithSize<8>, WithSize<16>)->Arg(N);
BENCHMARK_TEMPLATE(BM_dispatch_many, dyno::local_storage<16>, WithSize<8>, WithSize<16>)->Arg(N);
BENCHMARK_MAIN();
