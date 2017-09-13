// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include "model.hpp"

#include <dyno.hpp>

#include <benchmark/benchmark.h>

#include <cstddef>
#include <type_traits>
#include <utility>


// This benchmark measures the overhead of copy-constructing type-erased
// wrappers with different storage policies.

template <typename StoragePolicy, typename T>
static void BM_copy(benchmark::State& state) {
  T x{};
  model<StoragePolicy> original{x};
  while (state.KeepRunning()) {
    benchmark::DoNotOptimize(original);
    model<StoragePolicy> copy{original};
    benchmark::DoNotOptimize(copy);
  }
}

template <std::size_t Bytes>
using WithSize = std::aligned_storage_t<Bytes>;

BENCHMARK_TEMPLATE(BM_copy, dyno::remote_storage,    WithSize<4>);
BENCHMARK_TEMPLATE(BM_copy, dyno::sbo_storage<4>,    WithSize<4>);
BENCHMARK_TEMPLATE(BM_copy, dyno::sbo_storage<8>,    WithSize<4>);
BENCHMARK_TEMPLATE(BM_copy, dyno::sbo_storage<16>,   WithSize<4>);
BENCHMARK_TEMPLATE(BM_copy, dyno::local_storage<16>, WithSize<4>);

BENCHMARK_TEMPLATE(BM_copy, dyno::remote_storage,    WithSize<16>);
BENCHMARK_TEMPLATE(BM_copy, dyno::sbo_storage<4>,    WithSize<16>);
BENCHMARK_TEMPLATE(BM_copy, dyno::sbo_storage<8>,    WithSize<16>);
BENCHMARK_TEMPLATE(BM_copy, dyno::sbo_storage<16>,   WithSize<16>);
BENCHMARK_TEMPLATE(BM_copy, dyno::local_storage<16>, WithSize<16>);
BENCHMARK_MAIN();
