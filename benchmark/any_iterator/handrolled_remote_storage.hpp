// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#ifndef BENCHMARK_ANY_ITERATOR_HANDROLLED_REMOTE_STORAGE_HPP
#define BENCHMARK_ANY_ITERATOR_HANDROLLED_REMOTE_STORAGE_HPP

#include "handrolled_vtable.hpp"

#include <memory>
#include <utility>


namespace handrolled_remote_storage {
  struct null_deleter { void operator()(void*) const { } };

  template <typename Value, typename Reference = Value&>
  struct any_iterator {
    using value_type = Value;
    using reference = Reference;

    template <typename Iterator>
    explicit any_iterator(Iterator it)
      : vptr_{&vtable_for<Iterator>}
      , self_{new Iterator{std::move(it)}}
    { }

    any_iterator(any_iterator&& other)
      : self_{std::move(other.self_)}
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

    ~any_iterator() {
      vptr_->delete_(self_.release());
    }

  private:
    HandrolledVTable<reference> const* vptr_;
    std::unique_ptr<void, null_deleter> self_;
  };
} // end namespace handrolled_remote_storage

#endif // BENCHMARK_ANY_ITERATOR_HANDROLLED_REMOTE_STORAGE_HPP
