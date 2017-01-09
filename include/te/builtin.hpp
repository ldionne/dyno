// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#ifndef TE_BUILTIN_HPP
#define TE_BUILTIN_HPP

#include <te/dsl.hpp>

#include <cassert>
#include <utility>


namespace te {

// Befriend this class to allow the library to access private methods like
// `virtual_` and `storage` inside your custom interface.
class access {
public:
  template <typename T, typename Name>
  static constexpr decltype(auto) virtual_(T&& t, Name name) {
    return std::forward<T>(t).virtual_(name);
  }

  template <typename T>
  static constexpr decltype(auto) storage(T&& t) {
    return std::forward<T>(t).storage();
  }
};

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
    access::virtual_(static_cast<Derived&>(*this), "destruct"_s)(
      access::storage(static_cast<Derived&>(*this))
    );
  }
};

template <typename Derived>
struct comparable {
  friend bool operator==(Derived const& a, Derived const& b) {
    using te::literals::operator""_s;
    assert(access::virtual_(a, "equal"_s) == access::virtual_(b, "equal"_s));
    return access::virtual_(a, "equal"_s)(access::storage(a), access::storage(b));
  }

  friend bool operator!=(Derived const& a, Derived const& b) {
    return !(a == b);
  }
};

} // end namespace te

#endif // TE_BUILTIN_HPP
