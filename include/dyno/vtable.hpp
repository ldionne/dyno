// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#ifndef DYNO_VTABLE_HPP
#define DYNO_VTABLE_HPP

#include <dyno/concept.hpp>
#include <dyno/detail/erase_function.hpp>
#include <dyno/detail/erase_signature.hpp>

#include <boost/hana/at_key.hpp>
#include <boost/hana/bool.hpp>
#include <boost/hana/contains.hpp>
#include <boost/hana/difference.hpp>
#include <boost/hana/for_each.hpp>
#include <boost/hana/functional/on.hpp>
#include <boost/hana/keys.hpp>
#include <boost/hana/map.hpp>
#include <boost/hana/or.hpp>
#include <boost/hana/pair.hpp>
#include <boost/hana/set.hpp>
#include <boost/hana/type.hpp>
#include <boost/hana/unpack.hpp>

#include <utility>


namespace dyno {

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


//////////////////////////////////////////////////////////////////////////////
// Vtable implementations

// Class implementing a local vtable, i.e. a vtable whose storage is held
// right where the `local_vtable` is instantiated.
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
  constexpr auto get_function(Name_, boost::hana::false_) const {
    constexpr bool always_false = sizeof(Name_) == 0;
    static_assert(always_false,
      "dyno::local_vtable::operator[]: Request for a virtual function that is "
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
  constexpr auto get_function(Name, boost::hana::true_, boost::hana::true_) const {
    constexpr bool always_false = sizeof(Name) == 0;
    static_assert(always_false,
      "dyno::joined_vtable::operator[]: Request for a virtual function that is "
      "contained in both vtables of a joined vtable. Since this is most likely "
      "a programming error, this is not allowed. You can find the contents of "
      "the vtable and the function you were trying to access in the compiler "
      "error message, probably in the following format: "
      "`joined_vtable<VTABLE 1, VTABLE 2>::get_function<FUNCTION NAME>`");
  }

  template <typename Name>
  constexpr auto get_function(Name, boost::hana::false_, boost::hana::false_) const {
    constexpr bool always_false = sizeof(Name) == 0;
    static_assert(always_false,
      "dyno::joined_vtable::operator[]: Request for a virtual function that is "
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

//////////////////////////////////////////////////////////////////////////////
// Selectors
template <typename ...Functions>
struct only {
  template <typename Concept, template <typename ...> class VTable>
  using apply = VTable<
    boost::hana::pair<Functions, decltype(Concept{}.get_signature(Functions{}))>...
  >;
};

template <typename ...Functions>
struct except {
  template <typename Concept>
  static auto get_equivalent_only_selector() {
    auto all = boost::hana::to_set(boost::hana::keys(Concept::all_clauses()));
    auto ignored = boost::hana::make_set(Functions{}...);
    auto kept = boost::hana::difference(all, ignored);
    auto as_only = boost::hana::unpack(kept, [](auto ...f) {
      return dyno::only<decltype(f)...>{};
    });
    return as_only;
  }

  template <typename Concept, template <typename ...> class VTable>
  using apply = typename decltype(
    get_equivalent_only_selector<Concept>()
  )::template apply<Concept, VTable>;
};

struct everything {
  template <typename Concept, template <typename ...> class VTable>
  using apply = typename decltype(
    boost::hana::unpack(Concept::all_clauses(),
      boost::hana::template_<VTable> ^boost::hana::on^ boost::hana::decltype_
    )
  )::type;
};


//////////////////////////////////////////////////////////////////////////////
// Vtable policies
template <typename Selector>
struct local {
  template <typename Concept>
  using apply = typename Selector::template apply<Concept, dyno::local_vtable>;
};

template <typename Selector>
struct remote {
  template <typename Concept>
  using apply = dyno::remote_vtable<
    typename Selector::template apply<Concept, dyno::local_vtable>
  >;
};

// Policy-based interface for defining vtables.
//
// This type does not model the `VTable` concept itself; instead, it is used
// to generate a type that models that concept.
//
// A `vtable` is parameterized on one or more policies, which specify how
// the vtable is implemented under the hood. Some policies can be further
// parameterized using a `Selector`, in which case the functions specified
// by the `Selector` are the ones to which the policy applies. Policies
// provided by the library are:
//
//  dyno::remote<Selector>
//    All functions selected by `Selector` will be stored in a remote vtable.
//    The vtable object is just a pointer to an actual vtable, and each access
//    to the vtable requires one indirection. In vanilla C++, this is the usual
//    vtable implementation.
//
//  dyno::local<Selector>
//    All functions selected by `Selector` will be stored in a local vtable.
//    The vtable object will actually contain function pointers for all the
//    selected functions. When accessing a virtual function, no additional
//    indirection is required (compared to a vtable stored remotely), at the
//    cost of space inside the vtable object.
//
//
// A selector is a type that selects a subset of functions defined by a concept.
// Selectors are used to pick which policy applies to which functions when
// defining a `vtable`. For example, one might want to define a vtable where
// all the functions except one (say `"f"`) are stored remotely, with `"f"`
// being stored locally. This can be achieved by using the `dyno::remote` policy
// with a selector that picks all functions except `"f"`, and the `dyno::local`
// policy with a selector that picks only the function `"f"`. Selectors
// provided by the library are:
//
//  dyno::only<functions...>
//    Picks only the specified functions from a concept. `functions` must be
//    compile-time strings, such as `dyno::only<decltype("foo"_s), decltype("bar"_s)>`.
//
//  dyno::except<functions...>
//    Picks all but the specified functions from a concept. `functions` must
//    be compile-time strings, such as `dyno::except<decltype("foo"_s), decltype("bar"_s)>`.
//
//  dyno::everything
//    Picks all the functions from a concept.
template <typename ...Policies>
struct vtable;

template <typename Policy1>
struct vtable<Policy1> {
  template <typename Concept>
  using apply = typename Policy1::template apply<Concept>;
};

template <typename Policy1, typename Policy2>
struct vtable<Policy1, Policy2> {
  template <typename Concept>
  using apply = dyno::joined_vtable<
    typename Policy1::template apply<Concept>,
    typename Policy2::template apply<Concept>
  >;
};

template <typename Policy1, typename Policy2, typename ...Policies>
struct vtable<Policy1, Policy2, Policies...> {
  template <typename Concept>
  using apply = dyno::joined_vtable<
    typename Policy1::template apply<Concept>,
    typename vtable<Policy2, Policies...>::template apply<Concept>
  >;
};

} // end namespace dyno

#endif // DYNO_VTABLE_HPP
