// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#ifndef DYNO_CONCEPT_HPP
#define DYNO_CONCEPT_HPP

#include <dyno/detail/dsl.hpp>
#include <dyno/detail/has_duplicates.hpp>

#include <boost/hana/any_of.hpp>
#include <boost/hana/at_key.hpp>
#include <boost/hana/basic_tuple.hpp>
#include <boost/hana/bool.hpp>
#include <boost/hana/contains.hpp>
#include <boost/hana/core/to.hpp>
#include <boost/hana/filter.hpp>
#include <boost/hana/first.hpp>
#include <boost/hana/flatten.hpp>
#include <boost/hana/map.hpp>
#include <boost/hana/pair.hpp>
#include <boost/hana/transform.hpp>

#include <type_traits>
#include <utility>


namespace dyno {

template <typename ...Clauses>
struct concept_;

namespace detail {
  template <typename Str, typename Fun>
  constexpr boost::hana::basic_tuple<boost::hana::pair<Str, Fun>>
    expand_clauses(boost::hana::pair<Str, Fun> const&)
  { return {}; }

  template <typename ...Clauses>
  constexpr auto expand_clauses(dyno::concept_<Clauses...> const&) {
    return boost::hana::flatten(
      boost::hana::make_basic_tuple(detail::expand_clauses(Clauses{})...)
    );
  }

  struct concept_base { };
} // end namespace detail

// Returns a sequence containing all the clauses of the given concept and
// its derived concepts.
//
// In the returned sequence, each clause is a pair where the first element
// is the name of the clause and the second element is the clause itself
// (e.g. a `dyno::function`). The order of clauses is not specified.
template <typename ...Clauses>
constexpr auto clauses(dyno::concept_<Clauses...> const&) {
  auto all = boost::hana::make_basic_tuple(detail::expand_clauses(Clauses{})...);
  return boost::hana::flatten(all);
}

// Returns a sequence containing the names associated to all the claused of
// the given concept, and its derived concepts.
//
// The order of the clause names is not specified.
template <typename ...Clauses>
constexpr auto clause_names(dyno::concept_<Clauses...> const& c) {
  return boost::hana::transform(dyno::clauses(c), boost::hana::first);
}

// Returns a sequence of the concepts refined by the given concept.
//
// Only the concepts that are refined directly by `c` are returned, i.e. we
// do not get the refined concepts of the refined concepts recursively.
template <typename ...Clauses>
constexpr auto refined_concepts(dyno::concept_<Clauses...> const&) {
  return boost::hana::filter(boost::hana::make_basic_tuple(Clauses{}...), [](auto t) {
    constexpr bool IsBase = std::is_base_of<detail::concept_base, decltype(t)>::value;
    return boost::hana::bool_c<IsBase>;
  });
}

namespace detail {
  template <typename ...Clauses>
  constexpr auto direct_clauses(dyno::concept_<Clauses...> const&) {
    return boost::hana::filter(boost::hana::make_basic_tuple(Clauses{}...), [](auto t) {
      constexpr bool IsBase = std::is_base_of<detail::concept_base, decltype(t)>::value;
      return boost::hana::bool_c<!IsBase>;
    });
  }

  template <typename ...Clauses>
  constexpr auto has_duplicate_clause(dyno::concept_<Clauses...> const& c) {
    auto direct = detail::direct_clauses(c);
    return detail::has_duplicates(boost::hana::transform(direct, boost::hana::first));
  }

  template <typename ...Clauses>
  constexpr auto is_redefining_base_concept_clause(dyno::concept_<Clauses...> const& c) {
    auto bases = dyno::refined_concepts(c);
    auto base_clause_names = boost::hana::unpack(bases, [](auto ...bases) {
      auto all = boost::hana::flatten(boost::hana::make_basic_tuple(dyno::clauses(bases)...));
      return boost::hana::transform(all, boost::hana::first);
    });
    return boost::hana::any_of(detail::direct_clauses(c), [=](auto clause) {
      return boost::hana::contains(base_clause_names, boost::hana::first(clause));
    });
  }
} // end namespace detail

// A `concept_` is a collection of clauses and refined concepts representing
// requirements for a type to model the concept.
//
// A concept is created by using `dyno::requires_`.
//
// From a `concept_`, one can generate a virtual function table by looking at
// the signatures of the functions defined in the concept. In the future, it
// would also be possible to do much more, like getting a predicate that checks
// whether a type satisfies the concept.
template <typename ...Clauses>
struct concept_ : detail::concept_base {
  static_assert(!decltype(detail::has_duplicate_clause(std::declval<concept_>())){},
    "dyno::concept_: It looks like you have multiple clauses with the same "
    "name in your concept definition. This is not allowed; each clause must "
    "have a different name.");

  static_assert(!decltype(detail::is_redefining_base_concept_clause(std::declval<concept_>())){},
    "dyno::concept_: It looks like you are redefining a clause that is already "
    "defined in a base concept. This is not allowed; clauses defined in a "
    "concept must have a distinct name from clauses defined in base concepts "
    "if there are any.");

  template <typename Name>
  constexpr auto get_signature(Name name) const {
    auto clauses = boost::hana::to_map(dyno::clauses(*this));
    return clauses[name];
  }
};

// Creates a `concept_` with the given clauses. Note that a clause may be a
// concept itself, in which case the clauses of that concept are used, and
// that, recursively. For example:
//
// ```
// template <typename Reference>
// struct Iterator : decltype(dyno::requires_(
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
constexpr dyno::concept_<Clauses...> requires_(Clauses ...) {
  return {};
}

} // end namespace dyno

#endif // DYNO_CONCEPT_HPP
