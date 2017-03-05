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
  te::Destructible{},
  te::Storable{}
)) { };

template <typename Storage>
static void BM_swap(benchmark::State& state) {
  using VTable = te::vtable<te::remote<te::everything>>::apply<Concept>;
  VTable vtable_a{
    te::complete_concept_map<Concept, int>(te::concept_map<Concept, int>)
  };
  VTable vtable_b{
    te::complete_concept_map<Concept, std::string>(te::concept_map<Concept, std::string>)
  };
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

BENCHMARK_TEMPLATE(BM_swap, te::sbo_storage<8>);
BENCHMARK_TEMPLATE(BM_swap, te::fallback_storage<te::local_storage<8>, te::remote_storage>);
BENCHMARK_MAIN();
