// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#ifndef DYNO_DETAIL_ERASE_FUNCTION_HPP
#define DYNO_DETAIL_ERASE_FUNCTION_HPP

#include <dyno/detail/empty_object.hpp>
#include <dyno/detail/eraser_traits.hpp>

#include <boost/callable_traits/function_type.hpp>

#include <utility>


namespace dyno { namespace detail {

template <typename Eraser, typename F, typename PlaceholderSig, typename ActualSig>
struct thunk;

template <typename Eraser, typename F, typename R_pl, typename ...Args_pl,
                                       typename R_ac, typename ...Args_ac>
struct thunk<Eraser, F, R_pl(Args_pl...), R_ac(Args_ac...)> {
  static constexpr auto
  apply(typename detail::erase_placeholder<Eraser, Args_pl>::type ...args)
    -> typename detail::erase_placeholder<Eraser, R_pl>::type
  {
    return detail::erase<Eraser, R_pl>::apply(
      detail::empty_object<F>::get()(
        detail::unerase<Eraser, Args_pl, Args_ac>::apply(
          std::forward<typename detail::erase_placeholder<Eraser, Args_pl>::type>(args)
        )...
      )
    );
  }
};

template <typename Eraser, typename F,    /* void */  typename ...Args_pl,
                                       typename R_ac, typename ...Args_ac>
struct thunk<Eraser, F, void(Args_pl...), R_ac(Args_ac...)> {
  static constexpr auto
  apply(typename detail::erase_placeholder<Eraser, Args_pl>::type ...args)
    -> void
  {
    detail::empty_object<F>::get()(
      detail::unerase<Eraser, Args_pl, Args_ac>::apply(
        std::forward<typename detail::erase_placeholder<Eraser, Args_pl>::type>(args)
      )...
    );
  }
};

// Transform an actual (stateless) function object with statically typed
// parameters into a type-erased function suitable for storage in a vtable.
//
// The pointer returned by `erase_function` is what's called a thunk; it
// makes a few adjustments to the arguments (usually 0-overhead static
// casts) and forwards them to another function.
//
// TODO:
//  - Would it be possible to erase a callable that's not a stateless function
//    object? Would that necessarily require additional storage?
//  - Should we be returning a lambda that erases its arguments?
template <typename Signature, typename Eraser = void, typename F>
constexpr auto erase_function(F const&) {
  using ActualSignature = boost::callable_traits::function_type_t<F>;
  using Thunk = detail::thunk<Eraser, F, Signature, ActualSignature>;
  return &Thunk::apply;
}

}} // end namespace dyno::detail

#endif // DYNO_DETAIL_ERASE_FUNCTION_HPP
