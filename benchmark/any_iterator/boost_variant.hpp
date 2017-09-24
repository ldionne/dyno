// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#ifndef BENCHMARK_ANY_ITERATOR_BOOST_VARIANT_HPP
#define BENCHMARK_ANY_ITERATOR_BOOST_VARIANT_HPP

#include <boost/variant/variant.hpp>

#include <utility>


namespace boost_variant {
  template <typename T>
  static T static_object{};

  template <typename ValueType>
  struct dummy_iterator {
    dummy_iterator& operator++() { return *this; }
    ValueType& operator*() { return static_object<ValueType>; }
    bool friend operator==(dummy_iterator const&, dummy_iterator const&) {
      return true;
    }
  };

  template <typename Iterator>
  struct any_iterator {
    using value_type = typename Iterator::value_type;
    using reference = typename Iterator::reference;

    template <typename It>
    explicit any_iterator(It it)
      : v_{std::move(it)}
    { }

    any_iterator(any_iterator&& other)
      : v_{std::move(other.v_)}
    { }

    friend bool operator==(any_iterator const& a, any_iterator const& b)
    { return a.v_ == b.v_; }

    any_iterator& operator++() {
      boost::apply_visitor([](auto& x) { ++x; }, v_);
      return *this;
    }

    reference operator*() {
      return boost::apply_visitor([](auto& x) -> decltype(auto) { return *x; }, v_);
    }

  private:
    boost::variant<
      Iterator,
      dummy_iterator<value_type>
    > v_;
  };
} // end namespace boost_variant

#endif // BENCHMARK_ANY_ITERATOR_BOOST_VARIANT_HPP
