// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#ifndef DYNO_DETAIL_HAS_DUPLICATES_HPP
#define DYNO_DETAIL_HAS_DUPLICATES_HPP

#include <boost/hana/core/to.hpp>
#include <boost/hana/length.hpp>
#include <boost/hana/not_equal.hpp>
#include <boost/hana/set.hpp>


namespace dyno { namespace detail {

// Returns whether a Foldable contains duplicate elements, i.e. elements
// that compare equal to each other.
//
// TODO: Lift this into the public interface of Hana.
template <typename Foldable>
constexpr auto has_duplicates(Foldable const& foldable) {
  return boost::hana::not_equal(
    boost::hana::length(boost::hana::to_set(foldable)),
    boost::hana::length(foldable)
  );
}

}} // end namespace dyno::detail

#endif // DYNO_DETAIL_HAS_DUPLICATES_HPP
