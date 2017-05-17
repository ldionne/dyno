// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <dyno/concept.hpp>

#include <boost/hana/core/to.hpp>
#include <boost/hana/equal.hpp>
#include <boost/hana/set.hpp>
#include <boost/hana/type.hpp>
using namespace dyno::literals;


struct A : decltype(dyno::requires(
  "f"_s = dyno::function<void (dyno::T&)>
)) { };

struct B : decltype(dyno::requires(
  A{},
  "g"_s = dyno::function<int (dyno::T&)>
)) { };

struct C : decltype(dyno::requires(
  B{}
)) { };

static_assert(boost::hana::to_set(dyno::refined_concepts(A{})) ==
              boost::hana::make_set(), "");

static_assert(boost::hana::to_set(dyno::refined_concepts(B{})) ==
              boost::hana::make_set(boost::hana::type<A>{}), "");

static_assert(boost::hana::to_set(dyno::refined_concepts(C{})) ==
              boost::hana::make_set(boost::hana::type<B>{}), "");

int main() { }
