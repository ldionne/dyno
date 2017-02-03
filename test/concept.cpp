// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <te/concept.hpp>

#include <boost/hana/core/to.hpp>
#include <boost/hana/equal.hpp>
#include <boost/hana/set.hpp>
#include <boost/hana/type.hpp>
using namespace te::literals;


struct A : decltype(te::requires(
  "f"_s = te::function<void (te::T&)>
)) { };

struct B : decltype(te::requires(
  A{},
  "g"_s = te::function<int (te::T&)>
)) { };

struct C : decltype(te::requires(
  B{}
)) { };

static_assert(boost::hana::to_set(A::refined_concepts()) ==
              boost::hana::make_set(), "");

static_assert(boost::hana::to_set(B::refined_concepts()) ==
              boost::hana::make_set(boost::hana::type<A>{}), "");

static_assert(boost::hana::to_set(C::refined_concepts()) ==
              boost::hana::make_set(boost::hana::type<B>{}), "");

int main() { }
