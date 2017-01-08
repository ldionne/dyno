// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#ifndef TE_BUILTIN_HPP
#define TE_BUILTIN_HPP

#include <te/dsl.hpp>

#include <cassert>
#include <utility>


namespace te {

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
    using te::literals::operator""_s;
    static_cast<Derived&>(*this).virtual_("destruct"_s)(
      static_cast<Derived&>(*this).storage()
    );
  }
};

template <typename Derived>
struct comparable {
  friend bool operator==(Derived const& a, Derived const& b) {
    using te::literals::operator""_s;
    assert(a.virtual_("equal"_s) == b.virtual_("equal"_s));
    return a.virtual_("equal"_s)(a.storage(), b.storage());
  }

  friend bool operator!=(Derived const& a, Derived const& b) {
    return !(a == b);
  }
};

} // end namespace te

#endif // TE_BUILTIN_HPP
