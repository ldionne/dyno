// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#ifndef TE_HPP
#define TE_HPP

#include <te/concept.hpp>
#include <te/concept_map.hpp>
#include <te/dsl.hpp>
#include <te/storage.hpp>
#include <te/vtable.hpp>

#include <boost/hana/at_key.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/flatten.hpp>
#include <boost/hana/map.hpp>
#include <boost/hana/pair.hpp>
#include <boost/hana/set.hpp>
#include <boost/hana/string.hpp>
#include <boost/hana/tuple.hpp>
#include <boost/hana/type.hpp>
#include <boost/hana/unpack.hpp>

#include <boost/callable_traits/function_type.hpp>

#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <type_traits>
#include <utility>


namespace te {

//////////////////////////////////////////////////////////////////////////////
// Basic concepts provided by the library
//////////////////////////////////////////////////////////////////////////////
template <typename Derived>
struct swappable {
  // TODO: That is NOT a proper implementation of swap!
  void swap(Derived& other) {
    Derived tmp(std::move(other));

    other.~Derived();
    new (&other) Derived(std::move(static_cast<Derived&>(*this)));

    static_cast<Derived*>(this)->~Derived();
    new (this) Derived(std::move(tmp));
  }
};

template <typename Derived>
struct destructible {
  ~destructible() {
    using literals::operator""_s;
    static_cast<Derived&>(*this).virtual_("destruct"_s)(
      static_cast<Derived&>(*this).storage()
    );
  }
};

template <typename Derived>
struct comparable {
  friend bool operator==(Derived const& a, Derived const& b) {
    using literals::operator""_s;
    assert(a.virtual_("equal"_s) == b.virtual_("equal"_s));
    return a.virtual_("equal"_s)(a.storage(), b.storage());
  }

  friend bool operator!=(Derived const& a, Derived const& b) {
    return !(a == b);
  }
};

} // end namespace te

#endif // TE_HPP
