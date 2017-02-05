// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <te.hpp>

#include <benchmark/benchmark.h>


namespace { namespace handrolled_classic {
  struct VTable {
    void (*f1)(void*);
    void (*f2)(void*);
    void (*f3)(void*);
  };

  template <typename T> void f1(void* self) { static_cast<T*>(self)->f1(); }
  template <typename T> void f2(void* self) { static_cast<T*>(self)->f2(); }
  template <typename T> void f3(void* self) { static_cast<T*>(self)->f3(); }

  template <typename T>
  static constexpr VTable const vtable = {&f1<T>, &f2<T>, &f3<T>};

  struct any {
    template <typename T>
    explicit any(T t) : self_{new model_t<T>{t}} { }
    any& f1() { self_->vptr_->f1(self_); return *this; }
    any& f2() { self_->vptr_->f2(self_); return *this; }
    any& f3() { self_->vptr_->f3(self_); return *this; }

  private:
    struct concept_t {
      VTable const* vptr_;
    };

    template <typename T>
    struct model_t : concept_t {
      explicit model_t(T t) : concept_t{&vtable<model_t>}, value_{t} { }
      void f1() { ++value_; };
      void f2() { --value_; };
      void f3() { ++value_; };
      T value_;
    };

    concept_t* self_;
  };
}} // end namespace handrolled_classic

namespace { namespace handrolled_split_ptr {
  struct VTable {
    void (*f1)(void*);
    void (*f2)(void*);
    void (*f3)(void*);
  };

  template <typename T> void f1(void* self) { static_cast<T*>(self)->f1(); }
  template <typename T> void f2(void* self) { static_cast<T*>(self)->f2(); }
  template <typename T> void f3(void* self) { static_cast<T*>(self)->f3(); }

  template <typename T>
  static constexpr VTable const vtable = {&f1<T>, &f2<T>, &f3<T>};

  struct any {
    template <typename T>
    explicit any(T t) : vptr_{&vtable<model_t<T>>}, self_{new model_t<T>{t}} { }
    any& f1() { vptr_->f1(self_); return *this; }
    any& f2() { vptr_->f2(self_); return *this; }
    any& f3() { vptr_->f3(self_); return *this; }

  private:
    template <typename T>
    struct model_t {
      explicit model_t(T t) : value_{t} { }
      void f1() { ++value_; };
      void f2() { --value_; };
      void f3() { ++value_; };
      T value_;
    };

    VTable const* vptr_;
    void* self_;
  };
}} // end namespace handrolled_split_ptr

namespace { namespace classic {
  struct any {
    template <typename T>
    explicit any(T t) : self_{new model_t<T>{t}} { }
    any& f1() { self_->f1(); return *this; }
    any& f2() { self_->f2(); return *this; }
    any& f3() { self_->f3(); return *this; }

  private:
    struct concept_t {
      virtual void f1() = 0;
      virtual void f2() = 0;
      virtual void f3() = 0;
    };

    template <typename T>
    struct model_t : concept_t {
      explicit model_t(T t) : value_{t} { }
      void f1() override final { ++value_; }
      void f2() override final { --value_; }
      void f3() override final { ++value_; }
      T value_;
    };

    concept_t* self_;
  };
}} // end namespace classic

namespace { namespace te_split_ptr {
  using namespace te::literals;

  struct Concept : decltype(te::requires(
    "f1"_s = te::function<void (te::T&)>,
    "f2"_s = te::function<void (te::T&)>,
    "f3"_s = te::function<void (te::T&)>
  )) { };

  struct any {
    template <typename T>
    explicit any(T t)
      : vtable_{
        te::make_concept_map<Concept, T>(
          "f1"_s = [](T& self) { ++self; },
          "f2"_s = [](T& self) { --self; },
          "f3"_s = [](T& self) { ++self; }
        )
      }
      , self_{new T(t)}
    { }

    any& f1() { vtable_["f1"_s](self_); return *this; }
    any& f2() { vtable_["f2"_s](self_); return *this; }
    any& f3() { vtable_["f3"_s](self_); return *this; }

  private:
    te::remote_vtable<te::local_vtable<Concept>> vtable_;
    void* self_;
  };
}} // end namespace te_split_ptr

template <typename Any>
static void BM_any_1_function(benchmark::State& state) {
  Any a{0};
  int const N = state.range(0);
  while (state.KeepRunning()) {
    for (int i = 0; i != N; ++i) {
      benchmark::DoNotOptimize(a.f1());
    }
  }
}

template <typename Any>
static void BM_any_2_function(benchmark::State& state) {
  Any a{0};
  int const N = state.range(0);
  while (state.KeepRunning()) {
    for (int i = 0; i != N; ++i) {
      benchmark::DoNotOptimize(a.f1());
      benchmark::DoNotOptimize(a.f2());
    }
  }
}

template <typename Any>
static void BM_any_3_function(benchmark::State& state) {
  Any a{0};
  int const N = state.range(0);
  while (state.KeepRunning()) {
    for (int i = 0; i != N; ++i) {
      benchmark::DoNotOptimize(a.f1());
      benchmark::DoNotOptimize(a.f2());
      benchmark::DoNotOptimize(a.f3());
    }
  }
}

static constexpr int N = 1000;

BENCHMARK_TEMPLATE(BM_any_1_function, handrolled_classic::any   )->Arg(N);
BENCHMARK_TEMPLATE(BM_any_1_function, handrolled_split_ptr::any )->Arg(N);
BENCHMARK_TEMPLATE(BM_any_1_function, classic::any              )->Arg(N);
BENCHMARK_TEMPLATE(BM_any_1_function, te_split_ptr::any         )->Arg(N);

BENCHMARK_TEMPLATE(BM_any_2_function, handrolled_classic::any   )->Arg(N);
BENCHMARK_TEMPLATE(BM_any_2_function, handrolled_split_ptr::any )->Arg(N);
BENCHMARK_TEMPLATE(BM_any_2_function, classic::any              )->Arg(N);
BENCHMARK_TEMPLATE(BM_any_2_function, te_split_ptr::any         )->Arg(N);

BENCHMARK_TEMPLATE(BM_any_3_function, handrolled_classic::any   )->Arg(N);
BENCHMARK_TEMPLATE(BM_any_3_function, handrolled_split_ptr::any )->Arg(N);
BENCHMARK_TEMPLATE(BM_any_3_function, classic::any              )->Arg(N);
BENCHMARK_TEMPLATE(BM_any_3_function, te_split_ptr::any         )->Arg(N);
BENCHMARK_MAIN();
