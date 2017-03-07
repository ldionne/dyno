// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#ifndef DYNO_CONCEPT_MAP_HPP
#define DYNO_CONCEPT_MAP_HPP

#include <dyno/detail/bind_signature.hpp>
#include <dyno/detail/dsl.hpp>
#include <dyno/detail/empty_object.hpp>

#include <boost/hana/at_key.hpp>
#include <boost/hana/bool.hpp>
#include <boost/hana/contains.hpp>
#include <boost/hana/difference.hpp>
#include <boost/hana/fold_left.hpp>
#include <boost/hana/insert.hpp>
#include <boost/hana/is_subset.hpp>
#include <boost/hana/keys.hpp>
#include <boost/hana/map.hpp>
#include <boost/hana/pair.hpp>
#include <boost/hana/set.hpp>
#include <boost/hana/unpack.hpp>

#include <type_traits>
#include <utility>


namespace dyno {

namespace detail {
  // We wrap all lambdas and function objects passed to the library using this
  // hack, so that we can pretend stateless lambdas are default constructible
  // in the rest of the library.
  template <typename F, typename Signature>
  struct default_constructible_lambda;

  template <typename F, typename R, typename ...Args>
  struct default_constructible_lambda<F, R(Args...)> {
    constexpr R operator()(Args ...args) const {
      auto lambda = detail::empty_object<F>::get();
      return lambda(std::forward<Args>(args)...);
    }
  };

  template <typename F, typename ...Args>
  struct default_constructible_lambda<F, void(Args...)> {
    constexpr void operator()(Args ...args) const {
      auto lambda = detail::empty_object<F>::get();
      lambda(std::forward<Args>(args)...);
    }
  };
} // end namespace detail

// A concept map is a statically-known mapping from functions implemented by
// a type `T` to functions defined by a concept. A concept map is what's being
// used to fill the vtable extracted from a concept definition. An instance of
// this type is never created as-is; `dyno::make_concept_map` must always be used.
//
// Note that everything in the concept map is known statically. Specifically,
// the types of the functions in the concept map are known statically, and
// e.g. lambdas will be stored as-is (not as function pointers).
template <typename Concept, typename T, typename ...Mappings>
struct concept_map_t;

template <typename Concept, typename T, typename ...Name, typename ...Function>
struct concept_map_t<Concept, T, boost::hana::pair<Name, Function>...> {
  constexpr concept_map_t() = default;

  template <typename Name_>
  constexpr auto operator[](Name_ name) const {
    return get_function(name, boost::hana::contains(as_hana_map{}, name));
  }

private:
  using as_hana_map = boost::hana::map<
    boost::hana::pair<
      Name,
      detail::default_constructible_lambda<
        Function,
        typename detail::bind_signature<
          typename decltype(Concept{}.get_signature(Name{}))::type, T
        >::type
      >
    >...
  >;

  template <typename Name_>
  static constexpr auto get_function(Name_ name, boost::hana::true_) {
    return boost::hana::at_key(as_hana_map{}, name);
  }

  template <typename Name_, bool function_is_in_the_map = false>
  static constexpr auto get_function(Name_ name, boost::hana::false_) {
    static_assert(function_is_in_the_map,
      "dyno::concept_map_t::operator[]: Request for the implementation of a "
      "function that was not provided in the concept map. Make sure the "
      "concept map contains the proper functions, and that you're requesting "
      "the right function from the concept map. You can find the contents of "
      "the concept map and the function you were trying to access in the "
      "compiler error message, probably in the following format: "
      "`concept_map_t<CONCEPT, MODEL, CONTENTS OF CONCEPT MAP>::get_function<FUNCTION NAME>`");
  }
};

// Creates a concept map associating function names to function implementations.
//
// The exact contents of the map must be pairs where the first element is a
// function name (represented as a compile-time string), and the second element
// is the implementation of that function (as a stateless function object).
//
// Note that a concept map created with this function can be incomplete. Before
// being used, it must be completed using `dyno::complete_concept_map`.
template <typename ...Name, typename ...Function>
constexpr auto make_concept_map(boost::hana::pair<Name, Function> ...mappings) {
  return boost::hana::make_map(mappings...);
}

// Customization point for concept writers to provide default models of
// their concepts.
//
// This can be specialized by concept authors to provide a concept map that
// will be used when no custom concept map is specified. The third parameter
// can be used to define a default concept map for a family of type, by using
// `std::enable_if`.
template <typename Concept, typename T, typename = void>
auto const default_concept_map = dyno::make_concept_map();

// Customization point for users to define their models of concepts.
//
// This can be specialized by clients to provide concept maps for the concepts
// and types they wish. The third parameter can be used to define a concept
// map for a family of type, by using `std::enable_if`.
template <typename Concept, typename T, typename = void>
auto const concept_map = dyno::make_concept_map();

namespace detail {
  // TODO: This should be `boost::hana::union_` for maps, I think.
  template <typename Map1, typename Map2>
  constexpr auto merge(Map1 map1, Map2 map2) {
    return boost::hana::fold_left(map2, map1, boost::hana::insert);
  }

  // Takes a Hana map, and completes it by interpreting it as a concept map
  // for fulfilling the given `Concept` for the given type `T`.
  template <typename Concept, typename T, typename Map>
  constexpr auto complete_concept_map_impl(Map map) {
    // 1. Bring in the functions provided in the default concept map.
    auto with_defaults = detail::merge(map, dyno::default_concept_map<Concept, T>);

    // 2. For each refined concept, recursively complete the concept map for
    //    that Concept and merge that into the current concept map.
    auto refined = Concept::refined_concepts();
    auto merged = boost::hana::fold_left(refined, with_defaults, [](auto m, auto c) {
      using C = typename decltype(c)::type;
      auto completed = detail::complete_concept_map_impl<C, T>(dyno::concept_map<C, T>);
      return detail::merge(m, completed);
    });

    return merged;
  }

  // Turns a Hana map into a concept map.
  template <typename Concept, typename T, typename Map>
  constexpr auto to_concept_map(Map map) {
    return boost::hana::unpack(map, [](auto ...m) {
      return dyno::concept_map_t<Concept, T, decltype(m)...>{};
    });
  }

  // Returns whether a Hana map, when interpreted as a concept map for fulfilling
  // the given `Concept`, is missing any functions.
  template <typename Concept, typename T, typename Map>
  struct concept_map_is_complete : decltype(boost::hana::is_subset(
      boost::hana::keys(Concept::all_clauses()),
      boost::hana::keys(std::declval<Map>())
  )) { };
} // end namespace detail

namespace diagnostic {
  template <typename ...> struct ________________THE_CONCEPT_IS;
  template <typename ...> struct ________________YOUR_MODEL_IS;
  template <typename ...> struct ________________FUNCTIONS_MISSING_FROM_YOUR_CONCEPT_MAP;
  template <typename ...> struct ________________FUNCTIONS_DECLARED_IN_YOUR_CONCEPT_MAP;
  template <typename ...> struct ________________FUNCTIONS_REQUIRED_BY_THE_CONCEPT;
  template <typename ...> struct ________________EXACT_TYPE_OF_YOUR_CONCEPT_MAP;

  template <typename ..., bool concept_map_is_complete = false>
  constexpr void INCOMPLEDYNO_CONCEPT_MAP() {
    static_assert(concept_map_is_complete,
      "dyno::concept_map: Incomplete definition of your concept map. Despite "
      "looking at the default concept map for this concept and the concept "
      "maps for all the concepts this concept refines, I can't find definitions "
      "for all the functions that the concept requires. Please make sure you did "
      "not forget to define a function in your concept map, and otherwise make "
      "sure the proper default concept maps are kicking in. You can find information "
      "to help you debug this error in the compiler error message, probably in "
      "the instantiation of the INCOMPLEDYNO_CONCEPT_MAP<.....> function. Good luck!");
  }
} // end namespace diagnostic

// Turns a Hana map into a fully cooked concept map ready for consumption
// by a vtable.
//
// The concept maps for all the concepts that `Concept` refines are merged with
// the mappings provided explicitly. For example:
// ```
// struct A : decltype(dyno::requires(
//   "f"_s = dyno::function<void (dyno::T&)>
// )) { };
//
// struct B : decltype(dyno::requires(
//   A{},
//   "g"_s = dyno::function<int (dyno::T&)>
// )) { };
//
// struct Foo { };
//
// template <>
// auto const dyno::concept_map<A, Foo> = dyno::make_concept_map(
//   "f"_s = [](Foo&) { }
// );
//
// template <>
// auto const dyno::concept_map<B, Foo> = dyno::make_concept_map(
//   "g"_s = [](Foo&) { return 0; }
// );
//
// auto complete = dyno::complete_concept_map<B, Foo>(dyno::concept_map<B, Foo>);
// // `f` is automatically pulled from `concept<A, Foo>`
// ```
//
// Furthermore, if the same function is defined in more than one concept map
// in the full refinement tree, it is undefined which one is used. Therefore,
// all of the implementations better be the same! This is easy to enforce by
// never defining a function in a concept map where the concept does not
// require that function.
//
// Despite the above, which relates to functions defined in different concepts
// that have a refinement relation, if a function is provided both in the
// default concept map and in a customized concept map for the same concept,
// the function in the customized map is preferred.
//
// Also, after looking at the whole refinement tree, including the default
// concept maps, it is an error if any function required by the concept can't
// be resolved.
template <typename Concept, typename T, typename Map,
  typename Complete = decltype(detail::complete_concept_map_impl<Concept, T>(std::declval<Map>())),
  bool is_complete = detail::concept_map_is_complete<Concept, T, Complete>::value,
  typename = std::enable_if_t<is_complete>
>
constexpr auto complete_concept_map(Map) {
  return decltype(detail::to_concept_map<Concept, T>(std::declval<Complete>())){};
}

template <typename Concept, typename T, typename Map,
  typename Complete = decltype(detail::complete_concept_map_impl<Concept, T>(std::declval<Map>())),
  bool is_complete = detail::concept_map_is_complete<Concept, T, Complete>::value,
  typename = std::enable_if_t<!is_complete>
>
constexpr void complete_concept_map(Map map) {
  auto complete_map = detail::complete_concept_map_impl<Concept, T>(map);
  auto required = boost::hana::to_set(boost::hana::keys(Concept::all_clauses()));
  auto declared = boost::hana::to_set(boost::hana::keys(complete_map));
  auto missing = boost::hana::difference(required, declared);
  auto as_concept_map = detail::to_concept_map<Concept, T>(complete_map);
  diagnostic::INCOMPLEDYNO_CONCEPT_MAP<
    diagnostic::________________THE_CONCEPT_IS<Concept>,
    diagnostic::________________YOUR_MODEL_IS<T>,
    diagnostic::________________FUNCTIONS_MISSING_FROM_YOUR_CONCEPT_MAP<decltype(missing)>,
    diagnostic::________________FUNCTIONS_DECLARED_IN_YOUR_CONCEPT_MAP<decltype(declared)>,
    diagnostic::________________FUNCTIONS_REQUIRED_BY_THE_CONCEPT<decltype(required)>,
    diagnostic::________________EXACT_TYPE_OF_YOUR_CONCEPT_MAP<decltype(as_concept_map)>
  >();
}

} // end namespace dyno

#endif // DYNO_CONCEPT_MAP_HPP
