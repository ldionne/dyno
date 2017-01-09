// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#ifndef TE_VTABLE_HPP
#define TE_VTABLE_HPP

#include <boost/hana/map.hpp>
#include <boost/hana/pair.hpp>
#include <boost/hana/type.hpp>


namespace te {

// A `vtable` is a mapping from statically-known function names to
// dynamically-known function pointers. In some sense, a vtable is
// a type-erased `concept_map`.
//
// There are many different ways of implementing a virtual table. The most
// common one, used by the compiler, is to map every function to an index
// and use an array. A polymorphic object then holds a pointer to this array,
// and looks up the actual implementation of a method in that array when it
// gets called.
//
// Another possibility is to use a compile-time map from the names of functions
// to function pointers. This is the only implementation strategy currently
// provided by the library.
template <typename ...Mappings>
struct vtable;

template <typename ...Name, typename ...Fptr>
struct vtable<boost::hana::pair<Name, boost::hana::basic_type<Fptr>>...> {
  template <typename ConceptMap>
  constexpr explicit vtable(ConceptMap map)
    : vtbl_{boost::hana::make_map(
      boost::hana::make_pair(Name{}, map.erased(Name{}))...
    )}
  { }

  template <typename Name_>
  constexpr auto operator[](Name_ name) const {
    return vtbl_[name];
  }

private:
  boost::hana::map<boost::hana::pair<Name, Fptr>...> vtbl_;
};

} // end namespace te

#endif // TE_VTABLE_HPP
