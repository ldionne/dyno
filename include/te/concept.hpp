// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#ifndef TE_CONCEPT_HPP
#define TE_CONCEPT_HPP

#include <te/detail/dsl.hpp>
#include <te/detail/erase_signature.hpp>

#include <boost/hana/at_key.hpp>
#include <boost/hana/bool.hpp>
#include <boost/hana/filter.hpp>
#include <boost/hana/flatten.hpp>
#include <boost/hana/map.hpp>
#include <boost/hana/pair.hpp>
#include <boost/hana/tuple.hpp>
#include <boost/hana/type.hpp>
#include <boost/hana/unpack.hpp>

#include <type_traits>
#include <utility>


namespace te {

template <typename ...Clauses>
struct concept;

namespace detail {
  template <typename Str, typename Fun>
  constexpr auto expand_clauses(boost::hana::pair<Str, Fun> const& p) {
    return boost::hana::make_tuple(p);
  }

  template <typename ...Clauses>
  constexpr auto expand_clauses(te::concept<Clauses...> const&) {
    return boost::hana::flatten(
      boost::hana::make_tuple(detail::expand_clauses(Clauses{})...)
    );
  }

  struct concept_base { };
  struct is_concept {
    template <typename T>
    constexpr auto operator()(boost::hana::basic_type<T> const&) const {
      return boost::hana::bool_<std::is_base_of<detail::concept_base, T>{}>{};
    }
  };
} // end namespace detail

// A `concept` is a collection of clauses and refined concepts representing
// requirements for a type to model the concept.
//
// A concept is created by using `te::requires`.
//
// From a `concept`, one can generate a virtual function table using
// `unpack_vtable_layout`. In the future, it would also be possible to
// do much more, like getting a predicate that checks whether a type
// satisfies the concept.
template <typename ...Clauses>
struct concept : detail::concept_base {
  template <typename Name_>
  constexpr auto get_signature(Name_ name) const {
    auto clauses = all_clauses();
    return clauses[name];
  }

  static constexpr auto refined_concepts() {
    auto clauses = boost::hana::make_tuple(boost::hana::basic_type<Clauses>{}...);
    return boost::hana::filter(clauses, detail::is_concept{});
  }

  static constexpr auto all_clauses() {
    auto all = boost::hana::make_tuple(detail::expand_clauses(Clauses{})...);
    auto flat = boost::hana::flatten(all);
    return boost::hana::to_map(flat);
  }
};

namespace detail {
  template <template <typename ...> class VTable>
  struct unpack_vtable_layout {
    template <typename ...Name, typename ...Signature>
    constexpr auto operator()(boost::hana::pair<Name, boost::hana::basic_type<Signature>> ...) const {
      return boost::hana::type<VTable<
        std::pair<Name, typename detail::erase_signature<Signature>::type*>...
      >>{};
    }
  };
} // end namespace detail

// Provides the layout required for a vtable to hold all the functions defined
// by the given `Concept`. The vtable layout is provided as a parameter pack of
// `std::pair`s where the first element is the name of the function (as a compile-
// time string), and the second element is a function pointer with the right type
// to store in the vtable.
template <typename Concept, template <typename ...> class VTable>
using unpack_vtable_layout = typename decltype(
  boost::hana::unpack(Concept::all_clauses(), detail::unpack_vtable_layout<VTable>{})
)::type;

// Creates a `concept` with the given clauses. Note that a clause may be a
// concept itself, in which case the clauses of that concept are used, and
// that, recursively. For example:
//
// ```
// template <typename Reference>
// struct Iterator : decltype(te::requires(
//   Incrementable{},
//   "dereference"_s = te::function<Reference (te::T&)>
//   ...
// )) { };
// ```
//
// It is recommended to make every concept its own structure (and not just an
// alias), as above, because that ensures the uniqueness of concepts that have
// the same clauses.
template <typename ...Clauses>
constexpr te::concept<Clauses...> requires(Clauses ...) {
  return {};
}

} // end namespace te

#endif // TE_CONCEPT_HPP
