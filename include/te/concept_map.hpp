// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#ifndef TE_CONCEPT_MAP_HPP
#define TE_CONCEPT_MAP_HPP

#include <te/detail/erase_function.hpp>

#include <boost/hana/at_key.hpp>
#include <boost/hana/map.hpp>
#include <boost/hana/pair.hpp>


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

private:
  boost::hana::map<boost::hana::pair<Name, Function>...> map_;
};

// Creates a concept map for the given `Concept` mapping the given function
// names (compile-time strings) to the given implementations.
template <typename Concept, typename ...Name, typename ...Function>
constexpr auto make_concept_map(boost::hana::pair<Name, Function> ...mappings) {
  return te::concept_map_t<Concept, boost::hana::pair<Name, Function>...>{mappings...};
}

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
// auto const te::concept_map<my::Drawable, Foo> = te::make_concept_map<my::Drawable>(
//   ...
// );
// ```
template <typename Concept, typename T, typename = void>
auto const concept_map = ERROR::no_concept_map_defined_for<Concept, T>{};

} // end namespace te

#endif // TE_CONCEPT_MAP_HPP
