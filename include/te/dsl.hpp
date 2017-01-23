// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#ifndef TE_DSL_HPP
#define TE_DSL_HPP

#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/pair.hpp>
#include <boost/hana/string.hpp>
#include <boost/hana/type.hpp>

#include <type_traits>


namespace te {

// Right-hand-side of a clause in a concept that signifies a function with the
// given signature.
template <typename Signature>
constexpr boost::hana::basic_type<Signature> function{};

// Placeholder type representing the type of ref-unqualified `*this` when
// defining a clause in a concept.
struct T;

namespace detail {
  template <char ...c>
  struct string : boost::hana::string<c...> {
    template <typename Function>
    constexpr boost::hana::pair<string, Function>
    operator=(Function f) const {
      static_assert(std::is_empty<Function>{},
        "Only stateless function objects can be used to define vtables");
      return {{}, f};
    }
    using hana_tag = typename boost::hana::tag_of<boost::hana::string<c...>>::type;
  };
} // end namespace detail

inline namespace literals {
  // Creates a compile-time string that can be used as the left-hand-side when
  // defining clauses or filling concept maps.
  template <typename CharT, CharT ...c>
  constexpr auto operator""_s() { return detail::string<c...>{}; }
} // end namespace literals

} // end namespace te

#endif // TE_DSL_HPP
