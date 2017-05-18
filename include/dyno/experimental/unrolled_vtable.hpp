// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#ifndef DYNO_EXPERIMENTAL_UNROLLED_VTABLE_HPP
#define DYNO_EXPERIMENTAL_UNROLLED_VTABLE_HPP

#include <dyno/concept.hpp>
#include <dyno/detail/erase_function.hpp>
#include <dyno/detail/erase_signature.hpp>

#include <boost/hana/functional/on.hpp>
#include <boost/hana/pair.hpp>
#include <boost/hana/type.hpp>
#include <boost/hana/unpack.hpp>


namespace dyno { namespace experimental {

namespace detail {
  template <typename ...Mappings>
  struct unrolled_vtable_impl;
}

template <typename Concept>
using unrolled_vtable = typename decltype(
  boost::hana::unpack(dyno::clauses(Concept{}),
    boost::hana::template_<detail::unrolled_vtable_impl> ^boost::hana::on^ boost::hana::decltype_
  )
)::type;

/*
What follows is a script to generate the specializations of `unrolled_vtable_impl`.
Run the script as

  awk '/SCRIPTBEGIN/{flag=1;next}/SCRIPTEND/{flag=0}flag' ${thisfile} | erb

SCRIPTBEGIN
<% (0..10).each do |n| %>
template <
  <%= (0...n).map {|i| "typename Name#{i}, typename Sig#{i}" }.join(",\n  ") %>
> struct unrolled_vtable_impl<
  <%= (0...n).map {|i| "boost::hana::pair<Name#{i}, boost::hana::basic_type<Sig#{i}>>" }.join(",\n  ") %>
> {
  template <typename ConceptMap>
  constexpr explicit unrolled_vtable_impl(ConceptMap map)
    <%= ": " unless n == 0 %><%= (0...n).map {|i| "fptr#{i}_(dyno::detail::erase_function<Sig#{i}>(map[Name#{i}{}]))" }.join("\n    , ") %>
  { }
  <%= (0...n).map {|i| "constexpr auto operator[](Name#{i}) const { return fptr#{i}_; };" }.join("\n  ") %>

private:
  <%= (0...n).map {|i| "typename detail::erase_signature<Sig#{i}>::type* fptr#{i}_;" }.join("\n  ") %>
};
<% end %>
SCRIPTEND */

namespace detail {
  ////////////////////////////////////////////////////////////////////////////
  // BEGIN GENERATED CODE
  ////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////
  // END GENERATED CODE
  ////////////////////////////////////////////////////////////////////////////
} // end namespace detail

}} // end namespace dyno::experimental

#endif // DYNO_EXPERIMENTAL_UNROLLED_VTABLE_HPP
