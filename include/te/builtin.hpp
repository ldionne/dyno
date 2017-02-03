// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#ifndef TE_BUILTIN_HPP
#define TE_BUILTIN_HPP

#include <te/concept.hpp>
#include <te/concept_map.hpp>


namespace te {

struct DefaultConstructible : decltype(te::requires(
  "default-construct"_s = te::function<void (void*)>
)) { };

template <typename T>
auto const default_concept_map<DefaultConstructible, T> = te::make_default_concept_map<DefaultConstructible, T>(
  "default-construct"_s = [](void* p) {
    new (p) T();
  }
);


struct MoveConstructible : decltype(te::requires(
  "move-construct"_s = te::function<void (void*, te::T&&)>
)) { };

template <typename T>
auto const default_concept_map<MoveConstructible, T> = te::make_default_concept_map<MoveConstructible, T>(
  "move-construct"_s = [](void* p, T&& other) {
    new (p) T(std::move(other));
  }
);


struct CopyConstructible : decltype(te::requires(
  te::MoveConstructible{},
  "copy-construct"_s = te::function<void (void*, te::T const&)>
)) { };

template <typename T>
auto const default_concept_map<CopyConstructible, T> = te::make_default_concept_map<CopyConstructible, T>(
  "copy-construct"_s = [](void* p, T const& other) {
    new (p) T(other);
  }
);


struct MoveAssignable : decltype(te::requires(
  // No virtual function required to support this so far
)) { };


struct CopyAssignable : decltype(te::requires(
  te::MoveAssignable{}
  // No additional virtual functions required to support this so far
)) { };


struct Swappable : decltype(te::requires(
  // No virtual functions required to support this so far
)) { };


struct EqualityComparable : decltype(te::requires(
  "equal"_s = te::function<bool (te::T const&, te::T const&)>
)) { };

template <typename T>
auto const default_concept_map<EqualityComparable, T> = te::make_default_concept_map<EqualityComparable, T>(
  "equal"_s = [](T const& a, T const& b) -> bool { return a == b; }
);


struct Destructible : decltype(te::requires(
  "destruct"_s = te::function<void (te::T&)>
)) { };

template <typename T>
auto const default_concept_map<Destructible, T> = te::make_default_concept_map<Destructible, T>(
  "destruct"_s = [](T& self) { self.~T(); }
);

} // end namespace te

#endif // TE_BUILTIN_HPP
