// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#ifndef TE_CONCEPT_HPP
#define TE_CONCEPT_HPP

#include <te/detail/erase_signature.hpp>

#include <boost/hana/at_key.hpp>
#include <boost/hana/flatten.hpp>
#include <boost/hana/map.hpp>
#include <boost/hana/pair.hpp>
#include <boost/hana/set.hpp>
#include <boost/hana/tuple.hpp>
#include <boost/hana/type.hpp>
#include <boost/hana/unpack.hpp>

#include <utility>


namespace te {

// A `concept` is a collection of clauses representing requirements for a type
// to model the concept.
//
// A concept is created by using `te::requires`.
//
// From a `concept`, one can generate a virtual function table using
// `unpack_vtable_layout`. In the future, it would also be possible to
// do much more, like getting a predicate that checks whether a type
// satisfies the concept.
template <typename ...Clauses>
struct concept;

template <typename ...Name, typename ...Signature>
struct concept<boost::hana::pair<Name, boost::hana::basic_type<Signature>>...> {
  template <typename Name_>
  constexpr auto get_signature(Name_ name) const {
    boost::hana::map<
      boost::hana::pair<Name, boost::hana::basic_type<Signature>>...
    > clauses;
    return clauses[name];
  }

  template <template <typename ...> class VTable>
  using unpack_vtable_layout_impl = VTable<
    std::pair<Name, typename detail::erase_signature<Signature>::type*>...
  >;
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

// Provides the layout required for a vtable to hold all the functions defined
// by the given `Concept`. The vtable layout is provided as a parameter pack of
// `std::pair`s where the first element is the name of the function (as a compile-
// time string), and the second element is a function pointer with the right type
// to store in the vtable.
template <typename Concept, template <typename ...> class VTable>
using unpack_vtable_layout = typename Concept::template unpack_vtable_layout_impl<VTable>;

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
