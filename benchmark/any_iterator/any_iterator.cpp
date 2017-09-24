// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <benchmark/benchmark.h>

#include "boost_type_erasure.hpp"
#include "boost_variant.hpp"
#include "dyno_generic.hpp"
#include "handrolled_remote_storage.hpp"
#include "handrolled_sean.hpp"
#include "mpark_variant.hpp"
#include "sean.hpp"

#include <utility>
#include <vector>


// We use this to make sure the compiler is not able to see through the
// initialization of the `any_iterator`. Otherwise, inlining can cause
// the whole dynamic dispatch to be elided, which does not faithfully
// represent what would happen in a complex system.
template <typename Iterator, typename T>
__attribute__((noinline)) Iterator hide(T t) {
  return Iterator{std::move(t)};
}

template <typename Iterator>
static void BM_any_iterator(benchmark::State& state) {
  using T = typename Iterator::value_type;
  std::vector<T> input(state.range(0)), output(state.range(0));

  while (state.KeepRunning()) {
    Iterator first{hide<Iterator>(input.begin())};
    Iterator last{hide<Iterator>(input.end())};
    Iterator result{hide<Iterator>(output.begin())};

    for (; !(first == last); ++first, ++result) {
      *result = *first;
    }
  }
}

static constexpr int N = 100;
BENCHMARK_TEMPLATE(BM_any_iterator, std::vector<int>::iterator)->Arg(N);

BENCHMARK_TEMPLATE(BM_any_iterator, sean::any_iterator<int>)->Arg(N);
BENCHMARK_TEMPLATE(BM_any_iterator, handrolled_sean::any_iterator<int>)->Arg(N);

BENCHMARK_TEMPLATE(BM_any_iterator, dyno_generic::remote_storage)->Arg(N);
BENCHMARK_TEMPLATE(BM_any_iterator, handrolled_remote_storage::any_iterator<int>)->Arg(N);

BENCHMARK_TEMPLATE(BM_any_iterator, dyno_generic::local_storage)->Arg(N);
BENCHMARK_TEMPLATE(BM_any_iterator, dyno_generic::local_storage_inlined_vtable)->Arg(N);

BENCHMARK_TEMPLATE(BM_any_iterator, boost_type_erasure::any_iterator<int>)->Arg(N);

BENCHMARK_TEMPLATE(BM_any_iterator, boost_variant::any_iterator<std::vector<int>::iterator>)->Arg(N);
BENCHMARK_TEMPLATE(BM_any_iterator, mpark_variant::any_iterator<std::vector<int>::iterator>)->Arg(N);
BENCHMARK_MAIN();
