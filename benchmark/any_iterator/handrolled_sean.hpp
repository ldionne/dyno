// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#ifndef BENCHMARK_ANY_ITERATOR_HANDROLLED_SEAN_HPP
#define BENCHMARK_ANY_ITERATOR_HANDROLLED_SEAN_HPP

#include <memory>
#include <utility>


namespace handrolled_sean {
  template <typename Value, typename Reference = Value&>
  struct any_iterator {
    using value_type = Value;
    using reference = Reference;

    template <typename Iterator>
    explicit any_iterator(Iterator it)
      : self_{std::make_unique<model_t<Iterator>>(std::move(it))}
    { }

    any_iterator(any_iterator&& other)
      : self_{std::move(other.self_)}
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

    ~any_iterator() {
      self_->vptr_->dtor(self_.get());
    }

  private:
    struct concept_t {
      HandrolledVTable<reference> const* vptr_;
    };

    template <typename Iterator>
    struct model_t : concept_t {
      using value_type = Value;
      using reference = Reference;
      explicit model_t(Iterator it) : concept_t{&vtable_for<model_t>}, it_{std::move(it)} { }
      void operator++() { ++it_; }
      reference operator*() { return *it_; }
      friend bool operator==(model_t const& a, model_t const& b)
      { return a.it_ == b.it_; }
      Iterator it_;
    };

    std::unique_ptr<concept_t> self_;
  };
} // end namespace handrolled_sean

#endif // BENCHMARK_ANY_ITERATOR_HANDROLLED_SEAN_HPP
