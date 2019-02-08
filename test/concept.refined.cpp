// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <dyno/concept.hpp>

#include <boost/hana/core/to.hpp>
#include <boost/hana/equal.hpp>
#include <boost/hana/set.hpp>
#include <boost/hana/transform.hpp>
#include <boost/hana/type.hpp>
using namespace dyno::literals;


struct A : decltype(dyno::requires_(
  "f"_s = dyno::function<void (dyno::T&)>
)) { };

struct B : decltype(dyno::requires_(
  A{},
  "g"_s = dyno::function<int (dyno::T&)>
)) { };

struct C : decltype(dyno::requires_(
  B{}
)) { };

struct D : decltype(dyno::requires_(
  "h"_s = dyno::function<void (dyno::T&)>
)) { };

struct E : decltype(dyno::requires_(
  C{},
  "i"_s = dyno::function<void (dyno::T&)>,
  D{},
  "j"_s = dyno::function<void (dyno::T&)>
)) { };

template <typename Concept>
constexpr auto refined_helper(Concept c) {
  auto refined = dyno::refined_concepts(c);
  // We wrap concepts into `hana::type`s so that we can compare them.
  auto as_types = boost::hana::transform(refined, boost::hana::typeid_);
  return boost::hana::to_set(as_types);
}

static_assert(refined_helper(A{}) ==
              boost::hana::make_set(), "");

static_assert(refined_helper(B{}) ==
              boost::hana::make_set(boost::hana::type<A>{}), "");

static_assert(refined_helper(C{}) ==
              boost::hana::make_set(boost::hana::type<B>{}), "");

static_assert(refined_helper(D{}) ==
              boost::hana::make_set(), "");

static_assert(refined_helper(E{}) ==
              boost::hana::make_set(boost::hana::type<C>{},
                                    boost::hana::type<D>{}), "");

int main() { }
