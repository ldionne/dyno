// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <dyno/builtin.hpp>
#include <dyno/concept.hpp>
#include <dyno/concept_map.hpp>

// This test makes sure that our builtin concepts properly report that types
// that do not model them do not, instead of failing because of lack of
// SFINAE-friendliness.

struct non_default_constructible { non_default_constructible() = delete; };
struct non_move_constructible { non_move_constructible(non_move_constructible&&) = delete; };
struct non_copy_constructible { non_copy_constructible(non_copy_constructible const&) = delete; };
struct non_move_assignable { non_move_assignable& operator=(non_move_assignable&&) = delete; };
struct non_copy_assignable { non_copy_assignable& operator=(non_copy_assignable const&) = delete; };
struct non_equality_comparable { friend bool operator==(non_equality_comparable const&, non_equality_comparable const&) = delete; };
struct non_destructible { ~non_destructible() = delete; };

static_assert(!dyno::models<dyno::DefaultConstructible, non_default_constructible>, "");
static_assert(!dyno::models<dyno::MoveConstructible, non_move_constructible>, "");
static_assert(!dyno::models<dyno::CopyConstructible, non_copy_constructible>, "");
static_assert(dyno::models<dyno::MoveAssignable, non_move_assignable>, "");
static_assert(dyno::models<dyno::CopyAssignable, non_copy_assignable>, "");
static_assert(!dyno::models<dyno::EqualityComparable, non_equality_comparable>, "");
static_assert(!dyno::models<dyno::Destructible, non_destructible>, "");

int main() { }
