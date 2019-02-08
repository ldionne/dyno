// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <dyno/concept.hpp>
#include <dyno/concept_map.hpp>
using namespace dyno::literals;


struct A : decltype(dyno::requires_(
  "f"_s = dyno::function<void (dyno::T&)>
)) { };

struct B : decltype(dyno::requires_(
  A{},
  "g"_s = dyno::function<void (dyno::T&)>
)) { };

struct C : decltype(dyno::requires_(B{})) { };

struct Foo { };
struct Bar { };
struct Baz { };

template <>
auto const dyno::concept_map<A, Foo> = dyno::make_concept_map("f"_s = [](Foo&) { });
template <>
auto const dyno::concept_map<B, Foo> = dyno::make_concept_map("g"_s = [](Foo&) { });

template <>
auto const dyno::concept_map<B, Bar> = dyno::make_concept_map("g"_s = [](Bar&) { });

template <>
auto const dyno::concept_map<A, Baz> = dyno::make_concept_map();

static_assert(dyno::models<A, Foo>, "");
static_assert(dyno::models<B, Foo>, "");
static_assert(dyno::models<C, Foo>, "");

static_assert(!dyno::models<A, Bar>, "");
static_assert(!dyno::models<B, Bar>, "");
static_assert(!dyno::models<C, Bar>, "");

static_assert(!dyno::models<A, Baz>, "");
static_assert(!dyno::models<B, Baz>, "");
static_assert(!dyno::models<C, Baz>, "");

static_assert(!dyno::models<A, int>, "");
static_assert(!dyno::models<B, int>, "");
static_assert(!dyno::models<C, int>, "");

static_assert(!dyno::models<A, void>, "");
static_assert(!dyno::models<B, void>, "");
static_assert(!dyno::models<C, void>, "");

int main() { }
