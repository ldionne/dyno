// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <dyno.hpp>

#include <benchmark/benchmark.h>


namespace { namespace handrolled_classic {
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
  static constexpr VTable const vtable = {&f1<T>, &f2<T>, &f3<T>, &f4<T>, &f5<T>};

  struct any {
    template <typename T>
    explicit any(T t) : self_{new model_t<T>{t}} { }
    any& f1() { self_->vptr_->f1(self_); return *this; }
    any& f2() { self_->vptr_->f2(self_); return *this; }
    any& f3() { self_->vptr_->f3(self_); return *this; }
    any& f4() { self_->vptr_->f4(self_); return *this; }
    any& f5() { self_->vptr_->f5(self_); return *this; }

  private:
    struct concept_t {
      VTable const* vptr_;
    };

    template <typename T>
    struct model_t : concept_t {
      explicit model_t(T t) : concept_t{&vtable<model_t>}, value_{t} { }
      void f1() { ++value_; }
      void f2() { --value_; }
      void f3() { ++value_; }
      void f4() { --value_; }
      void f5() { ++value_; }
      T value_;
    };

    concept_t* self_;
  };
}} // end namespace handrolled_classic

namespace { namespace handrolled_remote {
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
  static constexpr VTable const vtable = {&f1<T>, &f2<T>, &f3<T>, &f4<T>, &f5<T>};

  struct any {
    template <typename T>
    explicit any(T t) : vptr_{&vtable<model_t<T>>}, self_{new model_t<T>{t}} { }
    any& f1() { vptr_->f1(self_); return *this; }
    any& f2() { vptr_->f2(self_); return *this; }
    any& f3() { vptr_->f3(self_); return *this; }
    any& f4() { vptr_->f4(self_); return *this; }
    any& f5() { vptr_->f5(self_); return *this; }

  private:
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

    VTable const* vptr_;
    void* self_;
  };
}} // end namespace handrolled_remote

namespace { namespace handrolled_local {
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
  static constexpr VTable const vtable = {&f1<T>, &f2<T>, &f3<T>, &f4<T>, &f5<T>};

  struct any {
    template <typename T>
    explicit any(T t) : vtbl_{vtable<model_t<T>>}, self_{new model_t<T>{t}} { }
    any& f1() { vtbl_.f1(self_); return *this; }
    any& f2() { vtbl_.f2(self_); return *this; }
    any& f3() { vtbl_.f3(self_); return *this; }
    any& f4() { vtbl_.f4(self_); return *this; }
    any& f5() { vtbl_.f5(self_); return *this; }

  private:
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

    // TODO: Until https://github.com/google/benchmark/issues/764 is fixed,
    //       we can't make this member const.
    VTable vtbl_;
    void* self_;
  };
}} // end namespace handrolled_local

namespace { namespace classic {
  struct any {
    template <typename T>
    explicit any(T t) : self_{new model_t<T>{t}} { }
    any& f1() { self_->f1(); return *this; }
    any& f2() { self_->f2(); return *this; }
    any& f3() { self_->f3(); return *this; }
    any& f4() { self_->f4(); return *this; }
    any& f5() { self_->f5(); return *this; }

  private:
    struct concept_t {
      virtual void f1() = 0;
      virtual void f2() = 0;
      virtual void f3() = 0;
      virtual void f4() = 0;
      virtual void f5() = 0;
    };

    template <typename T>
    struct model_t : concept_t {
      explicit model_t(T t) : value_{t} { }
      virtual void f1() override final { ++value_; }
      virtual void f2() override final { --value_; }
      virtual void f3() override final { ++value_; }
      virtual void f4() override final { --value_; }
      virtual void f5() override final { ++value_; }
      T value_;
    };

    concept_t* self_;
  };
}} // end namespace classic

namespace { namespace dyno_remote {
  using namespace dyno::literals;

  struct Concept : decltype(dyno::requires_(
    "f1"_s = dyno::function<void (dyno::T&)>,
    "f2"_s = dyno::function<void (dyno::T&)>,
    "f3"_s = dyno::function<void (dyno::T&)>,
    "f4"_s = dyno::function<void (dyno::T&)>,
    "f5"_s = dyno::function<void (dyno::T&)>
  )) { };

  template <typename Policy>
  struct any_template {
    template <typename T>
    explicit any_template(T t)
      : vtable_{
        dyno::complete_concept_map<Concept, T>(dyno::make_concept_map(
          "f1"_s = [](T& self) { ++self; },
          "f2"_s = [](T& self) { --self; },
          "f3"_s = [](T& self) { ++self; },
          "f4"_s = [](T& self) { --self; },
          "f5"_s = [](T& self) { ++self; }
        ))
      }
      , self_{new T(t)}
    { }

    any_template& f1() { vtable_["f1"_s](self_); return *this; }
    any_template& f2() { vtable_["f2"_s](self_); return *this; }
    any_template& f3() { vtable_["f3"_s](self_); return *this; }
    any_template& f4() { vtable_["f4"_s](self_); return *this; }
    any_template& f5() { vtable_["f5"_s](self_); return *this; }

  private:
    using VTable = typename dyno::vtable<Policy>::template apply<Concept>;
    VTable vtable_;
    void* self_;
  };

  using any = any_template<dyno::remote<dyno::everything>>;
}} // end namespace dyno_remote

namespace { namespace dyno_local {
  using any = dyno_remote::any_template<dyno::local<dyno::everything>>;
}} // end namespace dyno_local

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

template <typename Any>
static void BM_any_4_function(benchmark::State& state) {
  Any a{0};
  int const N = state.range(0);
  while (state.KeepRunning()) {
    for (int i = 0; i != N; ++i) {
      benchmark::DoNotOptimize(a.f1());
      benchmark::DoNotOptimize(a.f2());
      benchmark::DoNotOptimize(a.f3());
      benchmark::DoNotOptimize(a.f4());
    }
  }
}

template <typename Any>
static void BM_any_5_function(benchmark::State& state) {
  Any a{0};
  int const N = state.range(0);
  while (state.KeepRunning()) {
    for (int i = 0; i != N; ++i) {
      benchmark::DoNotOptimize(a.f1());
      benchmark::DoNotOptimize(a.f2());
      benchmark::DoNotOptimize(a.f3());
      benchmark::DoNotOptimize(a.f4());
      benchmark::DoNotOptimize(a.f5());
    }
  }
}

static constexpr int N = 100;

BENCHMARK_TEMPLATE(BM_any_1_function, handrolled_classic::any   )->Arg(N)->Repetitions(4)->ReportAggregatesOnly(true);
BENCHMARK_TEMPLATE(BM_any_1_function, handrolled_remote::any    )->Arg(N)->Repetitions(4)->ReportAggregatesOnly(true);
BENCHMARK_TEMPLATE(BM_any_1_function, handrolled_local::any     )->Arg(N)->Repetitions(4)->ReportAggregatesOnly(true);
BENCHMARK_TEMPLATE(BM_any_1_function, classic::any              )->Arg(N)->Repetitions(4)->ReportAggregatesOnly(true);
BENCHMARK_TEMPLATE(BM_any_1_function, dyno_remote::any          )->Arg(N)->Repetitions(4)->ReportAggregatesOnly(true);
BENCHMARK_TEMPLATE(BM_any_1_function, dyno_local::any           )->Arg(N)->Repetitions(4)->ReportAggregatesOnly(true);

BENCHMARK_TEMPLATE(BM_any_2_function, handrolled_classic::any   )->Arg(N)->Repetitions(4)->ReportAggregatesOnly(true);
BENCHMARK_TEMPLATE(BM_any_2_function, handrolled_remote::any    )->Arg(N)->Repetitions(4)->ReportAggregatesOnly(true);
BENCHMARK_TEMPLATE(BM_any_2_function, handrolled_local::any     )->Arg(N)->Repetitions(4)->ReportAggregatesOnly(true);
BENCHMARK_TEMPLATE(BM_any_2_function, classic::any              )->Arg(N)->Repetitions(4)->ReportAggregatesOnly(true);
BENCHMARK_TEMPLATE(BM_any_2_function, dyno_remote::any          )->Arg(N)->Repetitions(4)->ReportAggregatesOnly(true);
BENCHMARK_TEMPLATE(BM_any_2_function, dyno_local::any           )->Arg(N)->Repetitions(4)->ReportAggregatesOnly(true);

BENCHMARK_TEMPLATE(BM_any_3_function, handrolled_classic::any   )->Arg(N)->Repetitions(4)->ReportAggregatesOnly(true);
BENCHMARK_TEMPLATE(BM_any_3_function, handrolled_remote::any    )->Arg(N)->Repetitions(4)->ReportAggregatesOnly(true);
BENCHMARK_TEMPLATE(BM_any_3_function, handrolled_local::any     )->Arg(N)->Repetitions(4)->ReportAggregatesOnly(true);
BENCHMARK_TEMPLATE(BM_any_3_function, classic::any              )->Arg(N)->Repetitions(4)->ReportAggregatesOnly(true);
BENCHMARK_TEMPLATE(BM_any_3_function, dyno_remote::any          )->Arg(N)->Repetitions(4)->ReportAggregatesOnly(true);
BENCHMARK_TEMPLATE(BM_any_3_function, dyno_local::any           )->Arg(N)->Repetitions(4)->ReportAggregatesOnly(true);

BENCHMARK_TEMPLATE(BM_any_4_function, handrolled_classic::any   )->Arg(N)->Repetitions(4)->ReportAggregatesOnly(true);
BENCHMARK_TEMPLATE(BM_any_4_function, handrolled_remote::any    )->Arg(N)->Repetitions(4)->ReportAggregatesOnly(true);
BENCHMARK_TEMPLATE(BM_any_4_function, handrolled_local::any     )->Arg(N)->Repetitions(4)->ReportAggregatesOnly(true);
BENCHMARK_TEMPLATE(BM_any_4_function, classic::any              )->Arg(N)->Repetitions(4)->ReportAggregatesOnly(true);
BENCHMARK_TEMPLATE(BM_any_4_function, dyno_remote::any          )->Arg(N)->Repetitions(4)->ReportAggregatesOnly(true);
BENCHMARK_TEMPLATE(BM_any_4_function, dyno_local::any           )->Arg(N)->Repetitions(4)->ReportAggregatesOnly(true);

BENCHMARK_TEMPLATE(BM_any_5_function, handrolled_classic::any   )->Arg(N)->Repetitions(4)->ReportAggregatesOnly(true);
BENCHMARK_TEMPLATE(BM_any_5_function, handrolled_remote::any    )->Arg(N)->Repetitions(4)->ReportAggregatesOnly(true);
BENCHMARK_TEMPLATE(BM_any_5_function, handrolled_local::any     )->Arg(N)->Repetitions(4)->ReportAggregatesOnly(true);
BENCHMARK_TEMPLATE(BM_any_5_function, classic::any              )->Arg(N)->Repetitions(4)->ReportAggregatesOnly(true);
BENCHMARK_TEMPLATE(BM_any_5_function, dyno_remote::any          )->Arg(N)->Repetitions(4)->ReportAggregatesOnly(true);
BENCHMARK_TEMPLATE(BM_any_5_function, dyno_local::any           )->Arg(N)->Repetitions(4)->ReportAggregatesOnly(true);

BENCHMARK_MAIN();
