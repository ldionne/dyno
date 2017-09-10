// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#ifndef BENCHMARK_STORAGE_MODEL_HPP
#define BENCHMARK_STORAGE_MODEL_HPP

#include <dyno.hpp>
#include <benchmark/benchmark.h>
#include <utility>
using namespace dyno::literals;


struct Concept : decltype(dyno::requires(
  dyno::CopyConstructible{},
  dyno::Swappable{},
  dyno::Destructible{},
  dyno::Storable{},
  "a"_s = dyno::function<void(dyno::T&)>,
  "b"_s = dyno::function<void(dyno::T&)>,
  "c"_s = dyno::function<void(dyno::T&)>
)) { };

template <typename T>
auto const dyno::default_concept_map<Concept, T> = dyno::make_concept_map(
  "a"_s = [](T& self) { benchmark::DoNotOptimize(self); },
  "b"_s = [](T& self) { benchmark::DoNotOptimize(self); },
  "c"_s = [](T& self) { benchmark::DoNotOptimize(self); }
);

template <typename StoragePolicy>
struct model {
  template <typename T>
  explicit model(T t)
    : poly_{std::move(t)}
  { }

  void swap(model& other) { poly_.swap(other.poly_); }

  void a() { poly_.virtual_("a"_s)(poly_); }
  void b() { poly_.virtual_("b"_s)(poly_); }
  void c() { poly_.virtual_("c"_s)(poly_); }

private:
  dyno::poly<Concept, StoragePolicy> poly_;
};

#endif // BENCHMARK_STORAGE_MODEL_HPP
