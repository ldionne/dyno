// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <benchmark/benchmark.h>


namespace {
  struct VTable {
    void (*f1)(void*);
    void (*f2)(void*);
    void (*f3)(void*);
    void (*f4)(void*);
    void (*f5)(void*);
  };

  template <typename T> void f1(void* self) { static_cast<T*>(self)->f1(); }
  template <typename T> void f2(void* self) { static_cast<T*>(self)->f2(); }
  template <typename T> void f3(void* self) { static_cast<T*>(self)->f3(); }
  template <typename T> void f4(void* self) { static_cast<T*>(self)->f4(); }
  template <typename T> void f5(void* self) { static_cast<T*>(self)->f5(); }

  template <typename T>
  struct model_t {
    explicit model_t(T t) : value_{t} { }
    void f1() { ++value_; }
    void f2() { --value_; }
    void f3() { ++value_; }
    void f4() { --value_; }
    void f5() { ++value_; }
    T value_;
  };
} // end anonymous namespace

namespace { namespace handrolled_remote {
  template <typename T>
  static constexpr VTable const vtable = {&f1<T>, &f2<T>, &f3<T>, &f4<T>, &f5<T>};

  struct any {
    template <typename T>
    explicit any(T t) : vptr_{&vtable<model_t<T>>}, self_{new model_t<T>{t}} { }
    void f1() { vptr_->f1(self_); }
    void f2() { vptr_->f2(self_); }
    void f3() { vptr_->f3(self_); }
    void f4() { vptr_->f4(self_); }
    void f5() { vptr_->f5(self_); }

    VTable const* const vptr_;
    void* self_;
  };
}} // end namespace handrolled_remote

namespace { namespace handrolled_local {
  template <typename T>
  static constexpr VTable const vtable = {&f1<T>, &f2<T>, &f3<T>, &f4<T>, &f5<T>};

  struct any {
    template <typename T>
    explicit any(T t) : vtbl_{vtable<model_t<T>>}, self_{new model_t<T>{t}} { }
    void f1() { vtbl_.f1(self_); }
    void f2() { vtbl_.f2(self_); }
    void f3() { vtbl_.f3(self_); }
    void f4() { vtbl_.f4(self_); }
    void f5() { vtbl_.f5(self_); }

    VTable const vtbl_;
    void* self_;
  };
}} // end namespace handrolled_local


inline void escape(void* v) {
  asm volatile("" : : "g"(v) : "memory");
}

static void BM_remote(benchmark::State& state) {
  using Any = handrolled_remote::any;
  Any a{0};
  int const N = state.range(0);
  escape(&a);
  while (state.KeepRunning()) {
    for (int i = 0; i != N; ++i) {
      a.f1();
      a.f2();
      a.f3();
      a.f4();
      a.f5();
    }
  }
}

static void BM_local(benchmark::State& state) {
  using Any = handrolled_local::any;
  Any a{0};
  int const N = state.range(0);
  escape(&a);
  while (state.KeepRunning()) {
    for (int i = 0; i != N; ++i) {
      a.f1();
      a.f2();
      a.f3();
      a.f4();
      a.f5();
    }
  }
}

volatile int N = 1000;
BENCHMARK(BM_remote)->Arg(N);
BENCHMARK(BM_local)->Arg(N);
BENCHMARK_MAIN();
