// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#ifndef TE_BUILTIN_HPP
#define TE_BUILTIN_HPP

#include <te/concept.hpp>
#include <te/dsl.hpp>


namespace te {

struct MoveConstructible : decltype(te::requires(
  "move-construct"_s = te::function<void (void*, te::T&&)>
)) { };

struct CopyConstructible : decltype(te::requires(
  MoveConstructible{},
  "copy-construct"_s = te::function<void (void*, te::T const&)>
)) { };

struct EqualityComparable : decltype(te::requires(
  "equal"_s = te::function<bool (te::T const&, te::T const&)>
)) { };

struct Destructible : decltype(te::requires(
  "destruct"_s = te::function<void (te::T&)>
)) { };

} // end namespace te

#endif // TE_BUILTIN_HPP
