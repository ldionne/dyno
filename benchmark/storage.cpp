// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <te.hpp>

#include <benchmark/benchmark.h>

#include <string>
using namespace te::literals;


struct Concept : decltype(te::requires(
  te::CopyConstructible{},
  te::Swappable{},
  te::Destructible{}
)) { };

template <typename Storage>
static void BM_swap_same_types(benchmark::State& state) {
  te::local_vtable<Concept> vtable{te::concept_map<Concept, std::string>};
  Storage a{std::string{"foobar"}};
  Storage b{std::string{"boombaz"}};

  while (state.KeepRunning()) {
    a.swap(vtable, b, vtable);
    a.swap(vtable, b, vtable);
    benchmark::DoNotOptimize(a);
    benchmark::DoNotOptimize(b);
  }

  a.destruct(vtable);
  b.destruct(vtable);
}

template <typename Storage>
static void BM_swap_different_types(benchmark::State& state) {
  te::local_vtable<Concept> vtable_a{te::concept_map<Concept, int>};
  te::local_vtable<Concept> vtable_b{te::concept_map<Concept, std::string>};
  Storage a{123};
  Storage b{std::string{"foobar"}};

  while (state.KeepRunning()) {
    a.swap(vtable_a, b, vtable_b);
    a.swap(vtable_b, b, vtable_a);
    benchmark::DoNotOptimize(a);
    benchmark::DoNotOptimize(b);
  }

  a.destruct(vtable_a);
  b.destruct(vtable_b);
}

BENCHMARK_TEMPLATE(BM_swap_same_types, te::sbo_storage<8>);
BENCHMARK_TEMPLATE(BM_swap_same_types, te::fallback_storage<te::local_storage<8>, te::remote_storage>);

BENCHMARK_TEMPLATE(BM_swap_different_types, te::sbo_storage<8>);
BENCHMARK_TEMPLATE(BM_swap_different_types, te::fallback_storage<te::local_storage<8>, te::remote_storage>);
BENCHMARK_MAIN();
