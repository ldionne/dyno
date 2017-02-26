// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#ifndef TE_VTABLE_HPP
#define TE_VTABLE_HPP

#include <te/concept.hpp>
#include <te/detail/erase_function.hpp>
#include <te/detail/erase_signature.hpp>

#include <boost/hana/at_key.hpp>
#include <boost/hana/bool.hpp>
#include <boost/hana/contains.hpp>
#include <boost/hana/for_each.hpp>
#include <boost/hana/functional/on.hpp>
#include <boost/hana/keys.hpp>
#include <boost/hana/map.hpp>
#include <boost/hana/or.hpp>
#include <boost/hana/pair.hpp>
#include <boost/hana/type.hpp>

#include <utility>


namespace te {

// concept VTable
//
// A VTable is a mapping from statically-known function names to
// dynamically-known function pointers. In some sense, a vtable is
// a type-erased concept map.
//
// In addition to being `Swappable`, a type `Table` satisfying the `VTable`
// concept must provide the following functions as part of its interface:
//
// template <typename ConceptMap> explicit Table(ConceptMap);
//  Semantics: Construct a vtable with the functions from a concept map.
//             Note that the actual instance of the concept map being passed
//             as a parameter is not required to be used; if that is enough
//             for the purpose of the vtable, any instance of that concept
//             map sharing the same type may be used.
//
//             Note: Concept maps have unique types, so this wording is only
//                   a way of ensuring we can statically construct a vtable
//                   from just the type of that concept map.
//
// template <typename Name> constexpr auto contains(Name) const;
//  Semantics: Return whether the vtable contains a function with the given
//             name, which must be a compile-time string.
//
// template <typename Name> constexpr auto operator[](Name) const;
//  Semantics: Return the function with the given name in the vtable if there
//             is one. The behavior when no such function exists in the vtable
//             is implementation defined (in most cases that's a compile-time
//             error).

namespace detail {
  template <typename ...Mappings>
  struct local_vtable;

  template <typename ...Name, typename ...Signature>
  struct local_vtable<boost::hana::pair<Name, boost::hana::basic_type<Signature>>...> {
    template <typename ConceptMap>
    constexpr explicit local_vtable(ConceptMap map)
      : vtbl_{boost::hana::make_map(
        boost::hana::make_pair(Name{}, detail::erase_function<Signature>(map[Name{}]))...
      )}
    { }

    template <typename Name_>
    constexpr auto contains(Name_ name) const {
      return boost::hana::contains(vtbl_, name);
    }

    template <typename Name_>
    constexpr auto operator[](Name_ name) const {
      return get_function(name, contains(name));
    }

    friend void swap(local_vtable& a, local_vtable& b) {
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
    constexpr auto get_function(Name_ name, boost::hana::false_) const {
      constexpr bool always_false = sizeof(Name_) == 0;
      static_assert(always_false,
        "te::local_vtable::operator[]: Request for a virtual function that is "
        "not in the vtable. Was this function specified in the concept that "
        "was used to instantiate this vtable? You can find the contents of the "
        "vtable and the function you were trying to access in the compiler "
        "error message, probably in the following format: "
        "`local_vtable<CONTENTS OF VTABLE>::get_function<FUNCTION NAME>`");
    }

    boost::hana::map<
      boost::hana::pair<Name, typename detail::erase_signature<Signature>::type*>...
    > vtbl_;
  };
} // end namespace detail

// Class implementing a local vtable, i.e. a vtable whose storage is held
// right where the `local_vtable` is instantiated.
template <typename Concept>
using local_vtable = typename decltype(
  boost::hana::unpack(Concept::all_clauses(),
    boost::hana::template_<detail::local_vtable> ^boost::hana::on^ boost::hana::decltype_
  )
)::type;

namespace detail {
  template <typename VTable, typename ConceptMap>
  static VTable const static_vtable{ConceptMap{}};
}

// Class implementing a vtable whose storage is held remotely. This is
// basically a pointer to a static instance of the specified `VTable`.
template <typename VTable>
struct remote_vtable {
  template <typename ConceptMap>
  constexpr explicit remote_vtable(ConceptMap)
    : vptr_{&detail::static_vtable<VTable, ConceptMap>}
  { }

  template <typename Name>
  constexpr auto operator[](Name name) const {
    return (*vptr_)[name];
  }

  template <typename Name>
  constexpr auto contains(Name name) const {
    return vptr_->contains(name);
  }

  friend void swap(remote_vtable& a, remote_vtable& b) {
    using std::swap;
    swap(a.vptr_, b.vptr_);
  }

private:
  VTable const* vptr_;
};

// Class implementing a vtable that joins two other vtables.
//
// A function is first looked up in the first vtable, and in the second
// vtable if it can't be found in the first one. It is an error if a
// function is contained in both vtables, since this is most likely a
// programming error.
template <typename First, typename Second>
struct joined_vtable {
  template <typename ConceptMap>
  constexpr explicit joined_vtable(ConceptMap map)
    : first_{map}, second_{map}
  { }

  template <typename Name>
  constexpr auto contains(Name name) const {
    return first_.contains(name) || second_.contains(name);
  }

  template <typename Name>
  constexpr auto operator[](Name name) const {
    return get_function(name, first_.contains(name), second_.contains(name));
  }

private:
  template <typename Name>
  constexpr auto get_function(Name name, boost::hana::true_, boost::hana::true_) const {
    constexpr bool always_false = sizeof(Name) == 0;
    static_assert(always_false,
      "te::joined_vtable::operator[]: Request for a virtual function that is "
      "contained in both vtables of a joined vtable. Since this is most likely "
      "a programming error, this is not allowed. You can find the contents of "
      "the vtable and the function you were trying to access in the compiler "
      "error message, probably in the following format: "
      "`joined_vtable<VTABLE 1, VTABLE 2>::get_function<FUNCTION NAME>`");
  }

  template <typename Name>
  constexpr auto get_function(Name name, boost::hana::false_, boost::hana::false_) const {
    constexpr bool always_false = sizeof(Name) == 0;
    static_assert(always_false,
      "te::joined_vtable::operator[]: Request for a virtual function that is "
      "not present in any of the joined vtables. Make sure you meant to look "
      "this function up, and otherwise check whether the two sub-vtables look "
      "as expected. You can find the contents of the joined vtables and the "
      "function you were trying to access in the compiler error message, "
      "probably in the following format: "
      "`joined_vtable<VTABLE 1, VTABLE 2>::get_function<FUNCTION NAME>`");
  }

  template <typename Name>
  constexpr auto get_function(Name name, boost::hana::true_, boost::hana::false_) const {
    return first_[name];
  }

  template <typename Name>
  constexpr auto get_function(Name name, boost::hana::false_, boost::hana::true_) const {
    return second_[name];
  }

  First first_;
  Second second_;
};

} // end namespace te

#endif // TE_VTABLE_HPP
