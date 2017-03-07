// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <dyno.hpp>

#include <benchmark/benchmark.h>

#include <string>
using namespace dyno::literals;


struct Concept : decltype(dyno::requires(
  dyno::CopyConstructible{},
  dyno::Swappable{},
  dyno::Destructible{},
  dyno::Storable{}
)) { };

template <typename Storage>
static void BM_swap(benchmark::State& state) {
  using VTable = dyno::vtable<dyno::remote<dyno::everything>>::apply<Concept>;
  VTable vtable_a{
    dyno::complete_concept_map<Concept, int>(dyno::concept_map<Concept, int>)
  };
  VTable vtable_b{
    dyno::complete_concept_map<Concept, std::string>(dyno::concept_map<Concept, std::string>)
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

BENCHMARK_TEMPLATE(BM_swap, dyno::sbo_storage<8>);
BENCHMARK_TEMPLATE(BM_swap, dyno::fallback_storage<dyno::local_storage<8>, dyno::remote_storage>);
BENCHMARK_MAIN();
