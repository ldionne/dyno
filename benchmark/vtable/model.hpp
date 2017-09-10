// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#ifndef BENCHMARK_VTABLE_MODEL_HPP
#define BENCHMARK_VTABLE_MODEL_HPP

#include <dyno.hpp>
#include <benchmark/benchmark.h>
#include <utility>
using namespace dyno::literals;


struct Concept : decltype(dyno::requires(
  dyno::CopyConstructible{},
  dyno::Swappable{},
  dyno::Destructible{},
  dyno::Storable{},
  "f1"_s = dyno::function<void(dyno::T&)>,
  "f2"_s = dyno::function<void(dyno::T&)>,
  "f3"_s = dyno::function<void(dyno::T&)>,
  "f4"_s = dyno::function<void(dyno::T&)>
)) { };

template <typename T>
auto const dyno::default_concept_map<Concept, T> = dyno::make_concept_map(
  "f1"_s = [](T& self) { ++self; benchmark::DoNotOptimize(self); },
  "f2"_s = [](T& self) { ++self; benchmark::DoNotOptimize(self); },
  "f3"_s = [](T& self) { ++self; benchmark::DoNotOptimize(self); },
  "f4"_s = [](T& self) { ++self; benchmark::DoNotOptimize(self); }
);

template <typename VTablePolicy>
struct model {
  template <typename T>
  explicit model(T t)
    : poly_{std::move(t)}
  { }

  void f1() { poly_.virtual_("f1"_s)(poly_); }
  void f2() { poly_.virtual_("f2"_s)(poly_); }
  void f3() { poly_.virtual_("f3"_s)(poly_); }
  void f4() { poly_.virtual_("f4"_s)(poly_); }

private:
  dyno::poly<Concept, dyno::local_storage<8>, VTablePolicy> poly_;
};

#endif // BENCHMARK_VTABLE_MODEL_HPP
