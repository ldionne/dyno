// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#ifndef TE_CONCEPT_MAP_HPP
#define TE_CONCEPT_MAP_HPP

#include <boost/hana/at_key.hpp>
#include <boost/hana/map.hpp>
#include <boost/hana/pair.hpp>


namespace te {

// A `concept_map` is a statically-known mapping from functions implemented by
// a type `T` to functions defined by a concept. A `concept_map` is what's being
// used to fill the vtable of the concept it represents. A `concept_map` is
// never created as-is; `te::make_concept_map` should always be used.
//
// Note that everything in the concept map is known statically. The transformation
// from a concept map to a vtable is what's known as type-erasure, and this is
// where static information is lost.
template <typename ...Mappings>
struct concept_map;

template <typename ...Name, typename ...Function>
struct concept_map<boost::hana::pair<Name, Function>...> {
  constexpr explicit concept_map(boost::hana::pair<Name, Function> ...mappings)
    : map_{mappings...}
  { }

  template <typename Name_>
  constexpr auto operator[](Name_ name) const {
    return map_[name];
  }

private:
  boost::hana::map<
    boost::hana::pair<Name, Function>...
  > map_;
};

// Creates a `concept_map` containing the given mappings from names
// (compile-time strings) to functions.
template <typename ...Name, typename ...Function>
constexpr auto make_concept_map(boost::hana::pair<Name, Function> ...mappings) {
  return te::concept_map<boost::hana::pair<Name, Function>...>{mappings...};
}

} // end namespace te

#endif // TE_CONCEPT_MAP_HPP
