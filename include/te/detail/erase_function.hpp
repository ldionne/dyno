// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#ifndef TE_DETAIL_ERASE_FUNCTION_HPP
#define TE_DETAIL_ERASE_FUNCTION_HPP

#include <te/detail/erase_signature.hpp>
#include <te/dsl.hpp>

#include <boost/hana/type.hpp>

#include <boost/callable_traits/function_type.hpp>

#include <type_traits>
#include <utility>


namespace te { namespace detail {

// Cast an argument from a generic representation to the actual type expected
// by a statically typed equivalent.
//
// In what's below, `Ac` stands for `Actual`, i.e. the actual static type
// being requested by the function as defined in the concept map.
template <typename Ac>
constexpr Ac const& special_cast_impl(boost::hana::basic_type<te::T const&>,
                                      boost::hana::basic_type<Ac const&>,
                                      void const* arg)
{ return *static_cast<Ac const*>(arg); }
template <typename Ac>
constexpr Ac& special_cast_impl(boost::hana::basic_type<te::T &>,
                                boost::hana::basic_type<Ac &>,
                                void* arg)
{ return *static_cast<Ac*>(arg); }
template <typename Ac>
constexpr Ac&& special_cast_impl(boost::hana::basic_type<te::T &&>,
                                 boost::hana::basic_type<Ac &&>,
                                 void* arg)
{ return std::move(*static_cast<Ac*>(arg)); }
template <typename Ac>
constexpr Ac* special_cast_impl(boost::hana::basic_type<te::T *>,
                                boost::hana::basic_type<Ac *>,
                                void* arg)
{ return static_cast<Ac*>(arg); }
template <typename Ac>
constexpr Ac const* special_cast_impl(boost::hana::basic_type<te::T const*>,
                                      boost::hana::basic_type<Ac const*>,
                                      void const* arg)
{ return static_cast<Ac const*>(arg); }
template <typename Req, typename Ac, typename Arg>
constexpr Req special_cast_impl(boost::hana::basic_type<Req>,
                                boost::hana::basic_type<Ac>,
                                Arg&& arg)
{ return std::forward<Arg>(arg); }
template <typename Pl, typename Ac, typename Arg>
constexpr decltype(auto) special_cast(Arg&& arg) {
  return detail::special_cast_impl(boost::hana::basic_type<Pl>{},
                                   boost::hana::basic_type<Ac>{},
                                   std::forward<Arg>(arg));
}

template <typename F, typename PlaceholderSig, typename ActualSig>
struct thunk;

template <typename F, typename R_pl, typename ...Args_pl, typename R_ac, typename ...Args_ac>
struct thunk<F, R_pl(Args_pl...), R_ac(Args_ac...)> {
  static_assert(std::is_empty<F>{},
    "This trick won't work if `F` is not an empty function object.");

  static constexpr auto apply(typename detail::erase_placeholder<Args_pl>::type ...args)
    -> typename detail::erase_placeholder<R_pl>::type
  {
    return detail::special_cast<R_pl, R_ac>(
      (*static_cast<F*>(nullptr))( // <-------------- UB ALERT
        detail::special_cast<Args_pl, Args_ac>(args)...
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
      detail::special_cast<Args_pl, Args_ac>(args)...
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
//  - Thunks should implement perfect forwarding.
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
