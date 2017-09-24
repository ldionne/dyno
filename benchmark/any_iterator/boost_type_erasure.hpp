// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#ifndef BENCHMARK_ANY_ITERATOR_BOOST_TYPE_ERASURE_HPP
#define BENCHMARK_ANY_ITERATOR_BOOST_TYPE_ERASURE_HPP

#include <boost/mpl/vector.hpp>
#include <boost/type_erasure/any.hpp>
#include <boost/type_erasure/iterator.hpp>
#include <boost/type_erasure/same_type.hpp>


namespace boost_type_erasure {
  template <typename Value, typename Reference = Value&>
  using any_iterator = boost::type_erasure::any<
    boost::mpl::vector<
      boost::type_erasure::forward_iterator<>,
      boost::type_erasure::same_type<
        boost::type_erasure::forward_iterator<>::value_type,
        Value
      >
    >
  >;
} // end namespace boost_type_erasure

#endif // BENCHMARK_ANY_ITERATOR_BOOST_TYPE_ERASURE_HPP
