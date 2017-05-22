// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#ifndef DYNO_CONCEPT_HPP
#define DYNO_CONCEPT_HPP

#include <dyno/detail/dsl.hpp>

#include <boost/hana/at_key.hpp>
#include <boost/hana/basic_tuple.hpp>
#include <boost/hana/bool.hpp>
#include <boost/hana/core/to.hpp>
#include <boost/hana/filter.hpp>
#include <boost/hana/first.hpp>
#include <boost/hana/flatten.hpp>
#include <boost/hana/map.hpp>
#include <boost/hana/pair.hpp>
#include <boost/hana/type.hpp>
#include <boost/hana/unpack.hpp>

#include <type_traits>


namespace dyno {

template <typename ...Clauses>
struct concept;

namespace detail {
  template <typename Str, typename Fun>
  constexpr boost::hana::basic_tuple<boost::hana::pair<Str, Fun>>
    expand_clauses(boost::hana::pair<Str, Fun> const&)
  { return {}; }

  template <typename ...Clauses>
  constexpr auto expand_clauses(dyno::concept<Clauses...> const&) {
    return boost::hana::flatten(
      boost::hana::make_basic_tuple(detail::expand_clauses(Clauses{})...)
    );
  }

  struct concept_base { };
  struct is_concept {
    template <typename T, bool IsBase = std::is_base_of<detail::concept_base, T>::value>
    constexpr boost::hana::bool_<IsBase>
    operator()(boost::hana::basic_type<T>) const {
      return {};
    }
  };

  struct expand_all_clauses {
    template <typename ...Clauses>
    constexpr auto operator()(Clauses ...) const {
      return boost::hana::make_basic_tuple(
        detail::expand_clauses(typename Clauses::type{})...
      );
    }
  };

  struct get_clause_names {
    template <typename ...Clause>
    constexpr auto operator()(Clause ...c) const {
      return boost::hana::make_basic_tuple(boost::hana::first(c)...);
    }
  };
} // end namespace detail

// Returns a sequence containing all the clauses of the given concept and
// its derived concepts.
//
// In the returned sequence, each clause is a pair where the first element
// is the name of the clause and the second element is the clause itself
// (e.g. a `dyno::function`). The order of clauses is not specified.
template <typename Concept>
constexpr auto clauses(Concept c) {
  auto all = boost::hana::unpack(c.clauses_, detail::expand_all_clauses{});
  auto flat = boost::hana::flatten(all);
  return flat;
}

// Returns a sequence containing the names associated to all the claused of
// the given concept, and its derived concepts.
//
// The order of the clause names is not specified.
template <typename Concept>
constexpr auto clause_names(Concept c) {
  return boost::hana::unpack(dyno::clauses(c), detail::get_clause_names{});
}

// A `concept` is a collection of clauses and refined concepts representing
// requirements for a type to model the concept.
//
// A concept is created by using `dyno::requires`.
//
// From a `concept`, one can generate a virtual function table by looking at
// the signatures of the functions defined in the concept. In the future, it
// would also be possible to do much more, like getting a predicate that checks
// whether a type satisfies the concept.
template <typename ...Clauses>
struct concept : detail::concept_base {
  boost::hana::basic_tuple<boost::hana::basic_type<Clauses>...> clauses_;

  template <typename Name>
  constexpr auto get_signature(Name name) const {
    auto clauses = boost::hana::to_map(dyno::clauses(*this));
    return clauses[name];
  }
};

// Returns a sequence of the concepts refined by the given concept.
//
// Only the concepts that are refined directly by `c` are returned, i.e. we
// do not get the refined concepts of the refined concepts recursively. Also,
// the concepts are returned wrapped in `hana::basic_type`s, not straight
// concepts.
template <typename Concept>
constexpr auto refined_concepts(Concept c) {
  return boost::hana::filter(c.clauses_, detail::is_concept{});
}

// Creates a `concept` with the given clauses. Note that a clause may be a
// concept itself, in which case the clauses of that concept are used, and
// that, recursively. For example:
//
// ```
// template <typename Reference>
// struct Iterator : decltype(dyno::requires(
//   Incrementable{},
//   "dereference"_s = dyno::function<Reference (dyno::T&)>
//   ...
// )) { };
// ```
//
// It is recommended to make every concept its own structure (and not just an
// alias), as above, because that ensures the uniqueness of concepts that have
// the same clauses.
template <typename ...Clauses>
constexpr dyno::concept<Clauses...> requires(Clauses ...) {
  return {};
}

} // end namespace dyno

#endif // DYNO_CONCEPT_HPP
