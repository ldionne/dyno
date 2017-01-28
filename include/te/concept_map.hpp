// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#ifndef TE_CONCEPT_MAP_HPP
#define TE_CONCEPT_MAP_HPP

#include <te/detail/erase_function.hpp>

#include <boost/hana/at_key.hpp>
#include <boost/hana/fold_left.hpp>
#include <boost/hana/insert.hpp>
#include <boost/hana/map.hpp>
#include <boost/hana/pair.hpp>
#include <boost/hana/unpack.hpp>


namespace te {

namespace ERROR {
  template <typename ...>
  struct no_concept_map_defined_for;
}

// A concept map is a statically-known mapping from functions implemented by
// a type `T` to functions defined by a concept. A concept map is what's being
// used to fill the vtable of the concept it represents. An instance of this
// type is never created as-is; `te::make_concept_map` should always be used.
//
// Note that everything in the concept map is known statically. Specifically,
// the types of the functions in the concept map are known statically, and
// e.g. lambdas will be stored as-is (not as function pointers). To retrieve
// a function with an erased representation instead, use the `erased` method.
template <typename Concept, typename ...Mappings>
struct concept_map_t;

template <typename Concept, typename ...Name, typename ...Function>
struct concept_map_t<Concept, boost::hana::pair<Name, Function>...> {
  constexpr explicit concept_map_t(boost::hana::pair<Name, Function> ...mappings)
    : map_{mappings...}
  { }

  template <typename Name_>
  constexpr auto operator[](Name_ name) const {
    return map_[name];
  }

  template <typename Name_>
  constexpr auto erased(Name_ name) const {
    using Signature = typename decltype(Concept{}.get_signature(name))::type;
    return detail::erase_function<Signature>(map_[name]);
  }

public: // TODO: Make this private
  boost::hana::map<boost::hana::pair<Name, Function>...> map_;
};

// Customization point for users to define their models of concepts.
//
// This can be specialized by clients to provide concept maps for the concepts
// and types they wish. The third parameter can be used to define a concept
// map for a family of type, by using `std::enable_if`.
//
// Example usage:
// ```
// namespace my {
//   struct Drawable : decltype(te::requires(
//     "draw"_s = te::function<void (std::ostream&, te::T const&)>
//   )) { };
// }
//
// struct Foo { ... };
//
// template <>
// auto const te::concept_map<my::Drawable, Foo> = te::make_concept_map<my::Drawable, Foo>(
//   ...
// );
// ```
template <typename Concept, typename T, typename = void>
auto const concept_map = ERROR::no_concept_map_defined_for<Concept, T>{};

namespace detail {
  // TODO: This should be `boost::hana::union_` for maps, I think.
  template <typename Map1, typename Map2>
  constexpr auto merge(Map1 map1, Map2 map2) {
    return boost::hana::fold_left(map2, map1, boost::hana::insert);
  }
} // end namespace detail

// Creates a concept map for how the type `T` models the given `Concept`.
//
// This is achieved by providing a mapping from function names (as compile-time
// strings) to function implementations (as stateless function objects).
//
// Note that the concept maps for all the concepts that `Concept` refines are
// merged with the mappings provided explicitly. For example:
// ```
// struct A : decltype(te::requires(
//   "f"_s = te::function<void (te::T&)>
// )) { };
//
// struct B : decltype(te::requires(
//   A{},
//   "g"_s = te::function<int (te::T&)>
// )) { };
//
// struct Foo { };
//
// template <>
// auto const te::concept_map<A, Foo> = te::make_concept_map<A, Foo>(
//   "f"_s = [](Foo&) { }
// );
//
// template <>
// auto const te::concept_map<B, Foo> = te::make_concept_map<B, Foo>(
//   "g"_s = [](Foo&) { return 0; }
//   // `f` is automatically pulled from the concept map for `A`
// );
// ```
//
// Furthermore, if the same function is defined in more than one concept map
// in the full refinement tree, it is undefined which one is used. Therefore,
// all of the implementations better be the same! This is easy to enforce by
// never defining a function in a concept map where the concept does not
// require that function.
template <typename Concept, typename T, typename ...Name, typename ...Function>
constexpr auto make_concept_map(boost::hana::pair<Name, Function> ...mappings) {
  auto mappings_ = boost::hana::make_map(mappings...);
  auto refined = Concept::refined_concepts();
  auto merged = boost::hana::fold_left(refined, mappings_, [](auto mappings, auto c) {
    using C = typename decltype(c)::type;
    return detail::merge(mappings, te::concept_map<C, T>.map_);
  });
  return boost::hana::unpack(merged, [](auto ...m) {
    return te::concept_map_t<Concept, decltype(m)...>{m...};
  });
}

} // end namespace te

#endif // TE_CONCEPT_MAP_HPP
