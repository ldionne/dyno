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
  VTable vtable{
    dyno::complete_concept_map<Concept, std::string>(dyno::concept_map<Concept, std::string>)
  };
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

BENCHMARK_TEMPLATE(BM_swap, dyno::sbo_storage<8>);
BENCHMARK_TEMPLATE(BM_swap, dyno::fallback_storage<dyno::local_storage<8>, dyno::remote_storage>);
BENCHMARK_MAIN();
