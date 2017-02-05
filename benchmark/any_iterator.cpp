// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <te.hpp>

#include <benchmark/benchmark.h>

#include <iterator>
#include <memory>
#include <utility>
#include <vector>


namespace { namespace classic {
  template <typename Value, typename Reference = Value&>
  struct any_iterator {
    using value_type = Value;
    using reference = Reference;

    template <typename Iterator>
    explicit any_iterator(Iterator it)
      : it_{std::make_shared<model_t<Iterator>>(it)}
    { }

    friend bool operator==(any_iterator const& a, any_iterator const& b) {
      return a.it_->equal(*b.it_);
    }

    any_iterator& operator++() {
      it_->increment();
      return *this;
    }

    Reference operator*() {
      return it_->dereference();
    }

  private:
    struct concept_t {
      virtual void increment() = 0;
      virtual reference dereference() = 0;
      virtual bool equal(concept_t const&) const = 0;
    };

    template <typename Iterator>
    struct model_t : concept_t {
      explicit model_t(Iterator it) : it_(it) { }
      void increment() override final { ++it_; }
      reference dereference() override final { return *it_; }
      bool equal(concept_t const& other_) const override final {
        model_t const& other = static_cast<model_t const&>(other_);
        return it_ == other.it_;
      }
      Iterator it_;
    };

    std::shared_ptr<concept_t> it_;
  };
}} // end namespace classic

namespace { namespace handrolled_split_ptr {
  template <typename Reference>
  struct VTable {
    void (*increment)(void*);
    Reference (*dereference)(void*);
    bool (*equal)(void const*, void const*);
  };

  template <typename T>
  void increment(void* self) {
    ++*static_cast<T*>(self);
  }

  template <typename T>
  bool equal(void const* a, void const* b) {
    return *static_cast<T const*>(a) == *static_cast<T const*>(b);
  }

  template <typename T>
  typename T::reference dereference(void* self) {
    return **static_cast<T*>(self);
  }

  template <typename T>
  static constexpr VTable<typename T::reference> const vtable = {
    &increment<T>, &dereference<T>, &equal<T>
  };


  template <typename Value, typename Reference = Value&>
  struct any_iterator {
    using value_type = Value;
    using reference = Reference;

    template <typename Iterator>
    explicit any_iterator(Iterator it)
      : vptr_{&vtable<Iterator>}
      , self_{std::make_shared<Iterator>(std::move(it))}
    { }

    any_iterator& operator++() {
      vptr_->increment(self_.get());
      return *this;
    }

    reference operator*() {
      return vptr_->dereference(self_.get());
    }

    friend bool operator==(any_iterator const& a, any_iterator const& b) {
      return a.vptr_->equal(a.self_.get(), b.self_.get());
    }

  private:
    VTable<reference> const* vptr_;
    std::shared_ptr<void> self_;
  };
}} // end namespace handrolled_split_ptr

namespace { namespace handrolled_classic {
  template <typename Reference>
  struct VTable {
    void (*increment)(void*);
    Reference (*dereference)(void*);
    bool (*equal)(void const*, void const*);
  };

  template <typename T>
  void increment(void* self) {
    ++*static_cast<T*>(self);
  }

  template <typename T>
  bool equal(void const* a, void const* b) {
    return *static_cast<T const*>(a) == *static_cast<T const*>(b);
  }

  template <typename T>
  typename T::reference dereference(void* self) {
    return **static_cast<T*>(self);
  }

  template <typename T>
  static constexpr VTable<typename T::reference> const vtable = {
    &increment<T>, &dereference<T>, &equal<T>
  };


  template <typename Value, typename Reference = Value&>
  struct any_iterator {
    using value_type = Value;
    using reference = Reference;

    template <typename Iterator>
    explicit any_iterator(Iterator it)
      : self_{std::make_shared<model_t<Iterator>>(std::move(it))}
    { }

    any_iterator& operator++() {
      self_->vptr_->increment(self_.get());
      return *this;
    }

    reference operator*() {
      return self_->vptr_->dereference(self_.get());
    }

    friend bool operator==(any_iterator const& a, any_iterator const& b) {
      return a.self_->vptr_->equal(a.self_.get(), b.self_.get());
    }

  private:
    struct concept_t {
      VTable<reference> const* vptr_;
    };

    template <typename Iterator>
    struct model_t : concept_t {
      using value_type = Value;
      using reference = Reference;
      explicit model_t(Iterator it) : concept_t{&vtable<model_t>}, it_{std::move(it)} { }
      void operator++() { ++it_; }
      reference operator*() { return *it_; }
      friend bool operator==(model_t const& a, model_t const& b)
      { return a.it_ == b.it_; }
      Iterator it_;
    };

    std::shared_ptr<concept_t> self_;
  };
}} // end namespace handrolled_classic

namespace { namespace te_style {
  using namespace te::literals;

  template <typename Reference>
  struct Iterator : decltype(te::requires(
    "increment"_s = te::function<void (te::T&)>,
    "dereference"_s = te::function<Reference (te::T&)>,
    "equal"_s = te::function<bool (te::T const&, te::T const&)>
  )) { };

  template <typename Value, typename Reference = Value&>
  struct any_iterator {
    using value_type = Value;
    using reference = Reference;

    template <typename It>
    explicit any_iterator(It it)
      : vtable_{
        te::make_concept_map<Iterator<Reference>, It>(
          "increment"_s = [](It& self) { ++self; },
          "dereference"_s = [](It& self) -> decltype(auto) { return *self; },
          "equal"_s = [](It const& a, It const& b) -> bool { return a == b; }
        )
      }
      , self_{std::make_shared<It>(std::move(it))}
    { }

    any_iterator& operator++() {
      vtable_["increment"_s](self_.get());
      return *this;
    }

    reference operator*() {
      return vtable_["dereference"_s](self_.get());
    }

    friend bool operator==(any_iterator const& a, any_iterator const& b) {
      return a.vtable_["equal"_s](a.self_.get(), b.self_.get());
    }

  private:
    te::remote_vtable<te::local_vtable<Iterator<reference>>> vtable_;
    std::shared_ptr<void> self_;
  };
}} // end namespace te_style


template <typename Iterator>
static void BM_any_iterator(benchmark::State& state) {
  using T = typename Iterator::value_type;
  std::vector<T> input(state.range(0)), output(state.range(0));

  while (state.KeepRunning()) {

    state.PauseTiming();
    Iterator first{input.begin()}, last{input.end()};
    Iterator result{output.begin()};

    state.ResumeTiming();
    for (; !(first == last); ++first, ++result) {
      *result = *first;
    }
  }
}

static constexpr int N = 100;
BENCHMARK_TEMPLATE(BM_any_iterator, std::vector<int>::iterator)->Arg(N);
BENCHMARK_TEMPLATE(BM_any_iterator, classic::any_iterator<int>)->Arg(N);
BENCHMARK_TEMPLATE(BM_any_iterator, handrolled_split_ptr::any_iterator<int>)->Arg(N);
BENCHMARK_TEMPLATE(BM_any_iterator, handrolled_classic::any_iterator<int>)->Arg(N);
BENCHMARK_TEMPLATE(BM_any_iterator, te_style::any_iterator<int>)->Arg(N);
BENCHMARK_MAIN();
