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

template <typename ...Name, typename ...Clause>
struct local_vtable<boost::hana::pair<Name, Clause>...> {
  template <typename ConceptMap>
  constexpr explicit local_vtable(ConceptMap map)
    : vtbl_{boost::hana::make_map(
      boost::hana::make_pair(Name{}, detail::erase_function<typename Clause::type>(map[Name{}]))...
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
    constexpr bool contains_function = decltype(contains(name))::value;
    if constexpr (contains_function) {
      return vtbl_[name];
    } else {
      static_assert(contains_function,
        "dyno::local_vtable::operator[]: Request for a virtual function that is "
        "not in the vtable. Was this function specified in the concept that "
        "was used to instantiate this vtable? You can find the contents of the "
        "vtable and the function you were trying to access in the compiler "
        "error message, probably in the following format: "
        "`local_vtable<CONTENTS OF VTABLE>::operator[]<FUNCTION NAME>`");
    }
  }

  friend void swap(local_vtable& a, local_vtable& b) {
    boost::hana::for_each(boost::hana::keys(a.vtbl_), [&](auto key) {
      using std::swap;
      swap(a.vtbl_[key], b.vtbl_[key]);
    });
  }

private:
  boost::hana::map<
    boost::hana::pair<Name, typename detail::erase_signature<typename Clause::type>::type*>...
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
    auto first_contains_function = first_.contains(name);
    auto second_contains_function = second_.contains(name);

    if constexpr (first_contains_function && second_contains_function) {
      static_assert(!first_contains_function || !second_contains_function,
        "dyno::joined_vtable::operator[]: Request for a virtual function that is "
        "contained in both vtables of a joined vtable. Since this is most likely "
        "a programming error, this is not allowed. You can find the contents of "
        "the vtable and the function you were trying to access in the compiler "
        "error message, probably in the following format: "
        "`joined_vtable<VTABLE 1, VTABLE 2>::operator[]<FUNCTION NAME>`");

    } else if constexpr (!first_contains_function && !second_contains_function) {
      static_assert(first_contains_function || second_contains_function,
        "dyno::joined_vtable::operator[]: Request for a virtual function that is "
        "not present in any of the joined vtables. Make sure you meant to look "
        "this function up, and otherwise check whether the two sub-vtables look "
        "as expected. You can find the contents of the joined vtables and the "
        "function you were trying to access in the compiler error message, "
        "probably in the following format: "
        "`joined_vtable<VTABLE 1, VTABLE 2>::operator[]<FUNCTION NAME>`");

    } else if constexpr (first_contains_function) {
      return first_[name];

    } else {
      return second_[name];
    }
  }

private:
  First first_;
  Second second_;
};

//////////////////////////////////////////////////////////////////////////////
// Selectors
template <typename ...Functions>
struct only {
  template <typename All>
  constexpr auto operator()(All all) const {
    auto matched = boost::hana::make_set(Functions{}...);
    static_assert(decltype(boost::hana::is_subset(matched, all))::value,
      "dyno::only: Some functions specified in this selector are not part of "
      "the concept to which the selector was applied.");
    return boost::hana::make_pair(
      boost::hana::difference(all, matched),
      matched
    );
  }
};

template <typename ...Functions>
struct except {
  template <typename All>
  constexpr auto operator()(All all) const {
    auto not_matched = boost::hana::make_set(Functions{}...);
    static_assert(decltype(boost::hana::is_subset(not_matched, all))::value,
      "dyno::except: Some functions specified in this selector are not part of "
      "the concept to which the selector was applied.");
    return boost::hana::make_pair(
      not_matched,
      boost::hana::difference(all, not_matched)
    );
  }
};

struct everything {
  template <typename All>
  constexpr auto operator()(All all) const {
    return boost::hana::make_pair(boost::hana::make_set(), all);
  }
};

using everything_else = everything;

namespace detail {
  template <typename T>
  struct is_valid_selector : boost::hana::false_ { };

  template <typename ...Methods>
  struct is_valid_selector<dyno::only<Methods...>>
    : boost::hana::true_
  { };

  template <typename ...Methods>
  struct is_valid_selector<dyno::except<Methods...>>
    : boost::hana::true_
  { };

  template <>
  struct is_valid_selector<dyno::everything>
    : boost::hana::true_
  { };
} // end namespace detail

//////////////////////////////////////////////////////////////////////////////
// Vtable policies
template <typename Selector>
struct local {
  static_assert(detail::is_valid_selector<Selector>::value,
    "dyno::local: Provided invalid selector. Valid selectors are "
    "'dyno::only<METHODS...>', 'dyno::except<METHODS...>', "
    "'dyno::everything', and 'dyno::everything_else'.");

  template <typename Concept, typename Functions>
  static constexpr auto create(Concept, Functions functions) {
    return boost::hana::unpack(functions, [](auto ...f) {
      using VTable = dyno::local_vtable<
        boost::hana::pair<decltype(f), decltype(Concept{}.get_signature(f))>...
      >;
      return boost::hana::basic_type<VTable>{};
    });
  }

  Selector selector;
};

template <typename Selector>
struct remote {
  static_assert(detail::is_valid_selector<Selector>::value,
    "dyno::remote: Provided invalid selector. Valid selectors are "
    "'dyno::only<METHODS...>', 'dyno::except<METHODS...>', "
    "'dyno::everything', and 'dyno::everything_else'.");

  template <typename Concept, typename Functions>
  static constexpr auto create(Concept, Functions functions) {
    return boost::hana::template_<dyno::remote_vtable>(
      dyno::local<Selector>::create(Concept{}, functions)
    );
  }

  Selector selector;
};

namespace detail {
  // Returns whether a vtable is empty, such that we can completely skip it
  // when composing policies below.
  template <typename VTable>
  struct is_empty_vtable : boost::hana::false_ { };

  template <>
  struct is_empty_vtable<dyno::local_vtable<>> : boost::hana::true_ { };
} // end namespace detail

template <typename Concept, typename Policies>
constexpr auto generate_vtable(Policies policies) {
  auto functions = boost::hana::to_set(dyno::clause_names(Concept{}));
  auto state = boost::hana::make_pair(functions, boost::hana::basic_type<dyno::local_vtable<>>{});
  auto result = boost::hana::fold_left(policies, state, [](auto state, auto policy) {
    auto functions = boost::hana::first(state);
    auto vtable = boost::hana::second(state);

    auto selector_split = policy.selector(functions);
    auto remaining = boost::hana::first(selector_split);
    auto matched = boost::hana::second(selector_split);

    if constexpr (detail::is_empty_vtable<typename decltype(vtable)::type>{}) {
      auto new_vtable = decltype(policy.create(Concept{}, matched)){};
      return boost::hana::make_pair(remaining, new_vtable);
    } else {
      auto new_vtable = boost::hana::basic_type<
        dyno::joined_vtable<
          typename decltype(vtable)::type,
          typename decltype(policy.create(Concept{}, matched))::type
        >
      >{};
      return boost::hana::make_pair(remaining, new_vtable);
    }
  });

  constexpr bool all_functions_were_taken = decltype(boost::hana::length(boost::hana::first(result)))::value == 0;
  static_assert(all_functions_were_taken,
    "dyno::vtable: The policies specified in the vtable did not fully cover all "
    "the functions provided by the concept. Some functions were not mapped to "
    "any vtable, which is an error");
  return boost::hana::second(result);
}

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
// policy with a selector that picks everything (all that remains). Note that
// when multiple selectors are specified, functions picked by earlier selectors
// will effectively be removed from the concept for later selectors, which
// supports this use case. Otherwise, one would have to specify that the
// `dyno::local` contains everything except the `"f"` function, which is
// cumbersome. Selectors provided by the library are:
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
//
//  dyno::everything_else
//    Equivalent to `dyno::everything`, but prettier to read when other
//    policies are used before it.
template <typename ...Policies>
struct vtable {
  template <typename Concept>
  using apply = typename decltype(
    dyno::generate_vtable<Concept>(boost::hana::basic_tuple<Policies...>{})
  )::type;
};

} // end namespace dyno

#endif // DYNO_VTABLE_HPP
