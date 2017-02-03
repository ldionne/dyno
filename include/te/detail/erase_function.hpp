// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#ifndef TE_DETAIL_ERASE_FUNCTION_HPP
#define TE_DETAIL_ERASE_FUNCTION_HPP

#include <te/detail/dsl.hpp>
#include <te/detail/erase_signature.hpp>

#include <boost/callable_traits/function_type.hpp>

#include <type_traits>
#include <utility>


namespace te { namespace detail {

// Cast an argument from a generic representation to the actual type expected
// by a statically typed equivalent.
template <typename Erased, typename Actual>
struct unerase {
  template <typename Arg>
  static constexpr decltype(auto) apply(Arg&& arg)
  { return std::forward<Arg>(arg); }
};

template <typename Actual>
struct unerase<te::T const&, Actual const&> {
  static constexpr Actual const& apply(void const* arg)
  { return *static_cast<Actual const*>(arg); }
};

template <typename Actual>
struct unerase<te::T&, Actual&> {
  static constexpr Actual& apply(void* arg)
  { return *static_cast<Actual*>(arg); }
};

template <typename Actual>
struct unerase<te::T&&, Actual&&> {
  static constexpr Actual&& apply(void* arg)
  { return std::move(*static_cast<Actual*>(arg)); }
};

template <typename Actual>
struct unerase<te::T*, Actual*> {
  static constexpr Actual* apply(void* arg)
  { return static_cast<Actual*>(arg); }
};

template <typename Actual>
struct unerase<te::T const*, Actual const*> {
  static constexpr Actual* apply(void const* arg)
  { return static_cast<Actual const*>(arg); }
};

template <typename F, typename PlaceholderSig, typename ActualSig>
struct thunk;

template <typename F, typename R_pl, typename ...Args_pl, typename R_ac, typename ...Args_ac>
struct thunk<F, R_pl(Args_pl...), R_ac(Args_ac...)> {
  static_assert(std::is_empty<F>{},
    "This trick won't work if `F` is not an empty function object.");

  static constexpr auto apply(typename detail::erase_placeholder<Args_pl>::type ...args)
    -> typename detail::erase_placeholder<R_pl>::type
  {
    return detail::unerase<R_pl, R_ac>::apply(
      (*static_cast<F*>(nullptr))( // <-------------- UB ALERT
        detail::unerase<Args_pl, Args_ac>::apply(
          std::forward<typename detail::erase_placeholder<Args_pl>::type>(args)
        )...
      )
    );
  }
};

template <typename F, typename ...Args_pl, typename R_ac, typename ...Args_ac>
struct thunk<F, void(Args_pl...), R_ac(Args_ac...)> {
  static_assert(std::is_empty<F>{},
    "This trick won't work if `F` is not an empty function object.");

  static constexpr auto apply(typename detail::erase_placeholder<Args_pl>::type ...args)
    -> void
  {
    return (*static_cast<F*>(nullptr))( // <-------------- UB ALERT
      detail::unerase<Args_pl, Args_ac>::apply(
        std::forward<typename detail::erase_placeholder<Args_pl>::type>(args)
      )...
    );
  }
};

// Transform an actual (stateless) function object with statically typed
// parameters into a type-erased function object suitable for storage in
// a vtable.
//
// In a sense, this is the runtime equivalent of `detail::erase_signature`,
// which only produces the type of the erased function. In other words,
// `erase_function` takes a function and transforms it into a pointer to
// a function whose signature is determined by `erase_signature`.
//
// The pointer returned by `erase_function` is what's called a thunk; it
// makes a few adjustments to the arguments (in our case 0-overhead static
// casts) and forwards them to another function.
//
// TODO:
//  - Allow models to differ slightly from the required concept, i.e. if
//    a concept requires a `const&` it should probably be valid to implement
//    it by taking by value.
//  - Would it be possible to erase a callable that's not a stateless function
//    object? Would that necessarily require additional storage?
template <typename Signature, typename F>
constexpr typename detail::erase_signature<Signature>::type* erase_function(F const&) {
  using Thunk = detail::thunk<F, Signature, boost::callable_traits::function_type_t<F>>;
  return &Thunk::apply;
}

}} // end namespace te::detail

#endif // TE_DETAIL_ERASE_FUNCTION_HPP
