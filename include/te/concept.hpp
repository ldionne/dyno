// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#ifndef TE_CONCEPT_HPP
#define TE_CONCEPT_HPP

#include <boost/hana/flatten.hpp>
#include <boost/hana/pair.hpp>
#include <boost/hana/set.hpp>
#include <boost/hana/tuple.hpp>
#include <boost/hana/unpack.hpp>


namespace te {

// A `concept` is a collection of clauses representing requirements for a type
// to model the concept.
//
// From a `concept`, one can generate a virtual function table, but possibly
// much more, like get a predicate that checks whether a type satisfies the
// concept. When generating the vtable, one has the choice of which vtable
// implementation to use. A concept is created by using `te::requires`.
//
// TODO:
// - Creating a vtable from a concept is very clunky right now; fix this.
template <typename ...Clauses>
struct concept {
  template <template <typename ...> class VTable>
  using make_vtable = VTable<Clauses...>;
};

namespace detail {
  template <typename ...Clauses>
  constexpr auto expand_clauses(te::concept<Clauses...> const&) {
    return boost::hana::tuple<Clauses...>{};
  }

  template <typename Str, typename Fun>
  constexpr auto expand_clauses(boost::hana::pair<Str, Fun> const& p) {
    return boost::hana::make_tuple(p);
  }

  struct make_concept {
    template <typename ...Clauses>
    constexpr te::concept<Clauses...> operator()(Clauses ...) const {
      return {};
    }
  };
} // end namespace detail

// Creates a `concept` with the given clauses. Note that a clause may be a
// concept itself, in which case the clauses of that concept are used, and
// that, recursively. For example:
//
// ```
// template <typename Reference>
// auto Iterator = te::requires(
//   Incrementable,
//   "dereference"_s = te::function<Reference (te::T&)>
//   ...
// );
// ```
template <typename ...Clauses>
constexpr auto requires(Clauses ...clauses) {
  auto all = boost::hana::make_tuple(detail::expand_clauses(clauses)...);
  auto flat = boost::hana::flatten(all);
  auto uniqued = boost::hana::to_set(flat); // TODO: Oh my, this is going to be slow
  return boost::hana::unpack(uniqued, detail::make_concept{});
}

} // end namespace te

#endif // TE_CONCEPT_HPP
