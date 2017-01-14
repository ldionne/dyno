// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#ifndef TE_DETAIL_FUNCTION_CAST_HPP
#define TE_DETAIL_FUNCTION_CAST_HPP

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

// Transform an actual (stateless) function object with statically typed
// parameters into a type-erased function object suitable for storage in
// a vtable.
//
// TODO:
//  - We should allow moving from rvalue-reference arguments that we
//    receive in the adapter.
//  - Allow models to differ slightly from the required concept, i.e. if
//    a concept requires a `const&` it should probably be valid to implement
//    it by taking by value.
template <typename R_pl, typename ...Args_pl,
          typename R_ac, typename ...Args_ac,
          typename Function>
constexpr auto fun_replace(boost::hana::basic_type<R_pl(Args_pl...)> /*placeholder_sig*/,
                           boost::hana::basic_type<R_ac(Args_ac...)> /*actual_sig*/,
                           Function)
{
  using Storage = typename detail::erase_signature<R_pl(Args_pl...)>::type*;
  auto adapter = [](typename detail::erase_placeholder<Args_pl>::type ...args)
    -> typename detail::erase_placeholder<R_pl>::type
  {
    static_assert(std::is_empty<Function>{},
      "This trick won't work if `Function` is not empty.");
    return detail::special_cast<R_pl, R_ac>(
      (*static_cast<Function*>(nullptr))( // <-------------- UB ALERT
        detail::special_cast<Args_pl, Args_ac>(args)...
      )
    );
  };
  return static_cast<Storage>(adapter);
}
template <typename ...Args_pl, typename ...Args_ac, typename Function>
constexpr auto fun_replace(boost::hana::basic_type<void(Args_pl...)> /*placeholder_sig*/,
                           boost::hana::basic_type<void(Args_ac...)> /*actual_sig*/,
                           Function)
{
  using Storage = typename detail::erase_signature<void(Args_pl...)>::type*;
  auto adapter = [](typename detail::erase_placeholder<Args_pl>::type ...args) -> void {
    static_assert(std::is_empty<Function>{},
      "This trick won't work if `Function` is not empty.");
    (*static_cast<Function*>(nullptr))( // <-------------- UB ALERT
      detail::special_cast<Args_pl, Args_ac>(args)...
    );
  };
  return static_cast<Storage>(adapter);
}

template <typename Signature, typename Function>
constexpr auto function_cast(Function f) {
  return detail::fun_replace(
    boost::hana::basic_type<Signature>{},
    boost::hana::basic_type<boost::callable_traits::function_type_t<Function>>{},
    f
  );
}

}} // end namespace te::detail

#endif // TE_DETAIL_FUNCTION_CAST_HPP
