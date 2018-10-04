// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#ifndef DYNO_BUILTIN_HPP
#define DYNO_BUILTIN_HPP

#include <dyno/concept.hpp>
#include <dyno/concept_map.hpp>

#include <cstddef>
#include <type_traits>
#include <typeinfo>


namespace dyno {

// Encapsulates the minimal amount of information required to allocate
// storage for an object of a given type.
//
// This should never be created explicitly; always use `dyno::storage_info_for`.
struct storage_info {
  std::size_t size;
  std::size_t alignment;
};

template <typename T>
constexpr auto storage_info_for = storage_info{sizeof(T), alignof(T)};

struct Storable : decltype(dyno::requires(
  "storage_info"_dyno = dyno::function<dyno::storage_info()>
)) { };

template <typename T>
auto const default_concept_map<Storable, T> = dyno::make_concept_map(
  "storage_info"_dyno = []() { return dyno::storage_info_for<T>; }
);


struct TypeId : decltype(dyno::requires(
  "typeid"_dyno = dyno::function<std::type_info const&()>
)) { };

template <typename T>
auto const default_concept_map<TypeId, T> = dyno::make_concept_map(
  "typeid"_dyno = []() -> std::type_info const& { return typeid(T); }
);


struct DefaultConstructible : decltype(dyno::requires(
  "default-construct"_dyno = dyno::function<void (void*)>
)) { };

template <typename T>
auto const default_concept_map<DefaultConstructible, T,
  std::enable_if_t<std::is_default_constructible<T>::value>
> = dyno::make_concept_map(
  "default-construct"_dyno = [](void* p) {
    new (p) T();
  }
);


struct MoveConstructible : decltype(dyno::requires(
  "move-construct"_dyno = dyno::function<void (void*, dyno::T&&)>
)) { };

template <typename T>
auto const default_concept_map<MoveConstructible, T,
  std::enable_if_t<std::is_move_constructible<T>::value>
> = dyno::make_concept_map(
  "move-construct"_dyno = [](void* p, T&& other) {
    new (p) T(std::move(other));
  }
);


struct CopyConstructible : decltype(dyno::requires(
  dyno::MoveConstructible{},
  "copy-construct"_dyno = dyno::function<void (void*, dyno::T const&)>
)) { };

template <typename T>
auto const default_concept_map<CopyConstructible, T,
  std::enable_if_t<std::is_copy_constructible<T>::value>
> = dyno::make_concept_map(
  "copy-construct"_dyno = [](void* p, T const& other) {
    new (p) T(other);
  }
);


struct MoveAssignable : decltype(dyno::requires(
  // No virtual function required to support this so far
)) { };


struct CopyAssignable : decltype(dyno::requires(
  dyno::MoveAssignable{}
  // No additional virtual functions required to support this so far
)) { };


struct Swappable : decltype(dyno::requires(
  // No virtual functions required to support this so far
)) { };


struct EqualityComparable : decltype(dyno::requires(
  "equal"_dyno = dyno::function<bool (dyno::T const&, dyno::T const&)>
)) { };

template <typename T>
auto const default_concept_map<EqualityComparable, T,
  decltype((void)(std::declval<T>() == std::declval<T>()))
> = dyno::make_concept_map(
  "equal"_dyno = [](T const& a, T const& b) -> bool { return a == b; }
);


struct Destructible : decltype(dyno::requires(
  "destruct"_dyno = dyno::function<void (dyno::T&)>
)) { };

template <typename T>
auto const default_concept_map<Destructible, T,
  std::enable_if_t<std::is_destructible<T>::value>
> = dyno::make_concept_map(
  "destruct"_dyno = [](T& self) { self.~T(); }
);

} // end namespace dyno

#endif // DYNO_BUILTIN_HPP
