// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#ifndef BENCHMARK_ANY_ITERATOR_SEAN_HPP
#define BENCHMARK_ANY_ITERATOR_SEAN_HPP

#include <memory>
#include <utility>


namespace sean {
  template <typename Value, typename Reference = Value&>
  struct any_iterator {
    using value_type = Value;
    using reference = Reference;

    template <typename Iterator>
    explicit any_iterator(Iterator it)
      : it_{std::make_unique<model_t<Iterator>>(it)}
    { }

    any_iterator(any_iterator&& other)
      : it_{std::move(other.it_)}
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
      virtual ~concept_t() { }
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
} // end namespace sean

#endif // BENCHMARK_ANY_ITERATOR_SEAN_HPP
