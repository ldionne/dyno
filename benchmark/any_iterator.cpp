// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include "../example/any_iterator.hpp"

#include <benchmark/benchmark.h>

#include <iterator>
#include <memory>
#include <vector>


template <typename Value, typename Reference = Value&>
struct handrolled_iterator {
  using value_type = Value;
  using reference = Reference;

  template <typename Iterator>
  explicit handrolled_iterator(Iterator it)
    : it_(std::make_unique<model_t<Iterator>>(it))
  { }

  friend bool operator==(handrolled_iterator const& a, handrolled_iterator const& b) {
    return a.it_->equal(*b.it_);
  }

  friend bool operator!=(handrolled_iterator const& a, handrolled_iterator const& b) {
    return !(a == b);
  }

  handrolled_iterator& operator++() {
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
    virtual void increment() override final { ++it_; }
    virtual reference dereference() override final { return *it_; }
    virtual bool equal(concept_t const& other_) const override final {
      model_t const& other = static_cast<model_t const&>(other_);
      return it_ == other.it_;
    }
    Iterator it_;
  };

  std::unique_ptr<concept_t> it_;
};


template <typename Iterator>
static void BM_iterator(benchmark::State& state) {
  using T = typename Iterator::value_type;
  std::vector<T> input(state.range(0)), output(state.range(0));

  while (state.KeepRunning()) {

    state.PauseTiming();
    Iterator first{input.begin()}, last{input.end()};
    Iterator result{output.begin()};

    state.ResumeTiming();
    for (; first != last; ++first, ++result) {
      *result = *first;
    }
  }
}

BENCHMARK_TEMPLATE(BM_iterator, std::vector<int>::iterator)->Arg(100);
BENCHMARK_TEMPLATE(BM_iterator, any_iterator<int, std::random_access_iterator_tag>)->Arg(100);
BENCHMARK_TEMPLATE(BM_iterator, handrolled_iterator<int>)->Arg(100);
BENCHMARK_MAIN();
