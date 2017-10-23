// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#ifndef DYNO_VTABLE_HPP
#define DYNO_VTABLE_HPP

#include <dyno/concept.hpp>
#include <dyno/detail/erase_function.hpp>
#include <dyno/detail/erase_signature.hpp>

#include <boost/hana/at_key.hpp>
#include <boost/hana/basic_tuple.hpp>
#include <boost/hana/bool.hpp>
#include <boost/hana/contains.hpp>
#include <boost/hana/core/to.hpp>
#include <boost/hana/difference.hpp>
#include <boost/hana/first.hpp>
#include <boost/hana/fold_left.hpp>
#include <boost/hana/for_each.hpp>
#include <boost/hana/is_subset.hpp>
#include <boost/hana/length.hpp>
#include <boost/hana/map.hpp>
#include <boost/hana/or.hpp>
#include <boost/hana/pair.hpp>
#include <boost/hana/second.hpp>
#include <boost/hana/set.hpp>
#include <boost/hana/type.hpp>
#include <boost/hana/unpack.hpp>

#include <type_traits>
#include <utility>


namespace dyno { namespace experimental {

template <typename ...Mappings>
struct switch_vtable;

template <typename ...Name, typename ...Signature>
struct switch_vtable<boost::hana::pair<Name, boost::hana::basic_type<Signature>>...> {
  template <typename ConceptMap>
  constexpr explicit switch_vtable(ConceptMap map)
    : vtbl_{boost::hana::make_map(
      boost::hana::make_pair(Name{}, detail::erase_function<Signature>(map[Name{}]))...
    )} {
    // suppress "unused" warnings for empty parameter packs
    (void) map;
  }

  template <typename Name_>
  constexpr auto contains(Name_ name) const {
    return boost::hana::contains(vtbl_, name);
  }

  template <typename Name_>
  constexpr auto operator[](Name_ name) const {
    return get_function(name, contains(name));
  }

  friend void swap(switch_vtable& a, switch_vtable& b) {
    boost::hana::for_each(boost::hana::keys(a.vtbl_), [&](auto key) {
      using std::swap;
      swap(a.vtbl_[key], b.vtbl_[key]);
    });
  }

private:
  template <typename Name_>
  constexpr auto get_function(Name_ name, boost::hana::true_) const {
    return vtbl_[name];
  }

  template <typename Name_>
  constexpr auto get_function(Name_, boost::hana::false_) const {
    constexpr bool always_false = sizeof(Name_) == 0;
    static_assert(always_false,
      "dyno::switch_vtable::operator[]: Request for a virtual function that is "
      "not in the vtable. Was this function specified in the concept that "
      "was used to instantiate this vtable? You can find the contents of the "
      "vtable and the function you were trying to access in the compiler "
      "error message, probably in the following format: "
      "`switch_vtable<CONTENTS OF VTABLE>::get_function<FUNCTION NAME>`");
  }

  boost::hana::map<
    boost::hana::pair<Name, typename detail::erase_signature<Signature>::type*>...
  > vtbl_;
};

}} // end namespace dyno::experimental

#endif // DYNO_VTABLE_HPP
