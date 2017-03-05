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
  VTable vtable{
    te::complete_concept_map<Concept, std::string>(te::concept_map<Concept, std::string>)
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

BENCHMARK_TEMPLATE(BM_swap, te::sbo_storage<8>);
BENCHMARK_TEMPLATE(BM_swap, te::fallback_storage<te::local_storage<8>, te::remote_storage>);
BENCHMARK_MAIN();
