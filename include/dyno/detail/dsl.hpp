// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#ifndef DYNO_DETAIL_DSL_HPP
#define DYNO_DETAIL_DSL_HPP

#include <boost/hana/bool.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/pair.hpp>
#include <boost/hana/string.hpp>
#include <boost/hana/tuple.hpp>
#include <boost/hana/type.hpp>

#include <type_traits>
#include <utility>


namespace dyno {

template <typename Signature>
struct function_t { using type = Signature; };

template <typename Sig1, typename Sig2>
constexpr auto operator==(function_t<Sig1>, function_t<Sig2>) {
  return boost::hana::bool_c<std::is_same<Sig1, Sig2>::value>;
}

template <typename Sig1, typename Sig2>
constexpr auto operator!=(function_t<Sig1> m1, function_t<Sig2> m2) {
  return !(m1 == m2);
}

// Right-hand-side of a clause in a concept that signifies a function with the
// given signature.
template <typename Signature>
constexpr function_t<Signature> function{};

template <typename Signature>
struct method_t;

// Right-hand-side of a clause in a concept that signifies a method with the
// given signature. The first parameter of the resulting function is implicitly
// `dyno::T&` for a non-const method, and `dyno::T const&` for a const method.
template <typename Signature>
constexpr method_t<Signature> method{};

// Placeholder type representing the type of ref-unqualified `*this` when
// defining a clause in a concept.
struct T;

template <typename R, typename ...Args>
struct method_t<R(Args...)> { using type = R (dyno::T&, Args...); };
template <typename R, typename ...Args>
struct method_t<R(Args...) &> { using type = R (dyno::T&, Args...); };
template <typename R, typename ...Args>
struct method_t<R(Args...) &&> { using type = R (dyno::T&&, Args...); };

template <typename R, typename ...Args>
struct method_t<R(Args...) const> { using type = R (dyno::T const&, Args...); };
template <typename R, typename ...Args>
struct method_t<R(Args...) const&> { using type = R (dyno::T const&, Args...); };
// const&& not supported because it's stupid

template <typename Sig1, typename Sig2>
constexpr auto operator==(method_t<Sig1>, method_t<Sig2>) {
  return boost::hana::bool_c<std::is_same<Sig1, Sig2>::value>;
}

template <typename Sig1, typename Sig2>
constexpr auto operator!=(method_t<Sig1> m1, method_t<Sig2> m2) {
  return !(m1 == m2);
}

namespace detail {
  template <typename Name, typename ...Args>
  struct delayed_call {
    boost::hana::tuple<Args...> args;

    // All the constructors are private so that only `dyno::string` can
    // construct an instance of this. The intent is that we can only
    // manipulate temporaries of this type.
  private:
    template <char ...c> friend struct string;

    template <typename ...T>
    constexpr delayed_call(T&& ...t) : args{std::forward<T>(t)...} { }
    delayed_call(delayed_call const&) = default;
    delayed_call(delayed_call&&) = default;
  };

  template <char ...c>
  struct string : boost::hana::string<c...> {
    template <typename Function>
    constexpr boost::hana::pair<string, Function>
    operator=(Function f) const {
      static_assert(std::is_empty<Function>{},
        "Only stateless function objects can be used to define vtables");
      return {{}, f};
    }

    template <typename ...Args>
    constexpr auto operator()(Args&& ...args) const {
      return detail::delayed_call<string, Args&&...>{std::forward<Args>(args)...};
    }

    using hana_tag = typename boost::hana::tag_of<boost::hana::string<c...>>::type;
  };

  template <typename S, std::size_t ...N>
  constexpr detail::string<S::get()[N]...> prepare_string_impl(std::index_sequence<N...>)
  { return {}; }

  template <typename S>
  constexpr auto prepare_string(S) {
    return detail::prepare_string_impl<S>(std::make_index_sequence<S::size()>{});
  }
} // end namespace detail

inline namespace literals {
  // Creates a compile-time string that can be used as the left-hand-side when
  // defining clauses or filling concept maps.
  template <typename CharT, CharT ...c>
  constexpr auto operator""_s() { return detail::string<c...>{}; }
} // end namespace literals

// Creates a Dyno compile-time string without requiring the use of a
// user-defined literal.
//
// The user-defined literal is non-standard as of C++17, and it requires
// brining the literal in scope (through a using declaration or such),
// which is not always convenient or possible.
#define DYNO_STRING(s)                                                      \
  (::dyno::detail::prepare_string([]{                                       \
      struct tmp {                                                          \
          /* exclude null terminator in size() */                           \
          static constexpr std::size_t size() { return sizeof(s) - 1; }     \
          static constexpr char const* get() { return s; }                  \
      };                                                                    \
      return tmp{};                                                         \
  }()))                                                                     \
/**/

} // end namespace dyno

#endif // DYNO_DETAIL_DSL_HPP
