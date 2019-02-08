// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#ifndef DYNO_MACRO_HPP
#define DYNO_MACRO_HPP

//////////////////////////////////////////////////////////////////////////////
// THIS FILE WAS GENERATED; DO NOT EDIT DIRECTLY.
//
//
// This file is generated from the <dyno/detail/macro.hpp.erb> ERB[1] template
// file. The maximum number of methods that can be handled by the macros can
// be controlled with the 'MAX_NUMBER_OF_METHODS' variable, which can be set
// when calling ERB to generate the header:
//
//    export MAX_NUMBER_OF_METHODS=55
//    erb include/dyno/detail/macro.hpp.erb > include/dyno/macro.hpp
//
// Due to the limits of some preprocessor macros we're using in the implementation,
// 'MAX_NUMBER_OF_METHODS' must be <= 62, otherwise an error is triggered.
// If 'MAX_NUMBER_OF_METHODS' is not specified, it defaults to 20.
//
// [1]: http://en.wikipedia.org/wiki/ERuby
//////////////////////////////////////////////////////////////////////////////



#include <dyno/concept.hpp>
#include <dyno/concept_map.hpp>
#include <dyno/detail/dsl.hpp>
#include <dyno/detail/preprocessor.hpp>
#include <dyno/poly.hpp>

#include <boost/callable_traits/function_type.hpp>
#include <boost/callable_traits/is_const_member.hpp>
#include <boost/callable_traits/return_type.hpp>

#include <type_traits>
#include <utility>


// TODOS
// - Allow specifying custom base concepts and base interfaces. By default, a
//   concept could provide a default interface (e.g. a copy constructor for
//   CopyConstructible, etc..).
// - Handle const and non-const more gracefully
// - Try to get rid of commas in the method definition. Use a BOOST_PP_SEQ

#define DYNO_INTERFACE(name, ...) \
  DYNO_PP_CONCAT(DYNO_PP_INTERFACE_IMPL_, DYNO_PP_NARG(__VA_ARGS__))(name, __VA_ARGS__)



#define DYNO_PP_INTERFACE_IMPL_0(name)\
  struct DYNO_PP_CONCAT(dyno_concept_for_, name) {                            \
    static auto make_type() {                                                 \
      return ::dyno::requires_(                                                \
                                                                     \
      );                                                                      \
    }                                                                         \
  };                                                                          \
                                                                              \
  class name {                                                                \
    struct concept_t                                                          \
      : decltype(DYNO_PP_CONCAT(dyno_concept_for_, name)::make_type())        \
    { };                                                                      \
  public:                                                                     \
    template <typename T>                                                     \
    name(T&& x)                                                               \
      : poly_{static_cast<T&&>(x), ::dyno::make_concept_map(                  \
                                                                     \
      )}                                                                      \
    { }                                                                       \
                                                                     \
  private:                                                                    \
    ::dyno::poly<concept_t> poly_;                                            \
  }



#define DYNO_PP_INTERFACE_IMPL_1(name, arg1)\
  struct DYNO_PP_CONCAT(dyno_concept_for_, name) {                            \
    static auto make_type() {                                                 \
      return ::dyno::requires_(                                                \
                                        \
                                                           \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg1)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg1>\
                                                                     \
      );                                                                      \
    }                                                                         \
  };                                                                          \
                                                                              \
  class name {                                                                \
    struct concept_t                                                          \
      : decltype(DYNO_PP_CONCAT(dyno_concept_for_, name)::make_type())        \
    { };                                                                      \
  public:                                                                     \
    template <typename T>                                                     \
    name(T&& x)                                                               \
      : poly_{static_cast<T&&>(x), ::dyno::make_concept_map(                  \
                                        \
                                                           \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg1)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg1                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                                                     \
      )}                                                                      \
    { }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg1>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg1>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg1>\
      DYNO_PP_VARIADIC_HEAD arg1(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg1)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg1>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg1>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg1>\
      DYNO_PP_VARIADIC_HEAD arg1(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg1)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                                                     \
  private:                                                                    \
    ::dyno::poly<concept_t> poly_;                                            \
  }



#define DYNO_PP_INTERFACE_IMPL_2(name, arg1, arg2)\
  struct DYNO_PP_CONCAT(dyno_concept_for_, name) {                            \
    static auto make_type() {                                                 \
      return ::dyno::requires_(                                                \
                                        \
                                                           \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg1)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg1>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg2)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg2>\
                                                                     \
      );                                                                      \
    }                                                                         \
  };                                                                          \
                                                                              \
  class name {                                                                \
    struct concept_t                                                          \
      : decltype(DYNO_PP_CONCAT(dyno_concept_for_, name)::make_type())        \
    { };                                                                      \
  public:                                                                     \
    template <typename T>                                                     \
    name(T&& x)                                                               \
      : poly_{static_cast<T&&>(x), ::dyno::make_concept_map(                  \
                                        \
                                                           \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg1)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg1                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg2)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg2                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                                                     \
      )}                                                                      \
    { }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg1>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg1>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg1>\
      DYNO_PP_VARIADIC_HEAD arg1(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg1)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg1>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg1>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg1>\
      DYNO_PP_VARIADIC_HEAD arg1(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg1)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg2>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg2>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg2>\
      DYNO_PP_VARIADIC_HEAD arg2(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg2)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg2>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg2>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg2>\
      DYNO_PP_VARIADIC_HEAD arg2(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg2)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                                                     \
  private:                                                                    \
    ::dyno::poly<concept_t> poly_;                                            \
  }



#define DYNO_PP_INTERFACE_IMPL_3(name, arg1, arg2, arg3)\
  struct DYNO_PP_CONCAT(dyno_concept_for_, name) {                            \
    static auto make_type() {                                                 \
      return ::dyno::requires_(                                                \
                                        \
                                                           \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg1)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg1>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg2)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg2>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg3)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg3>\
                                                                     \
      );                                                                      \
    }                                                                         \
  };                                                                          \
                                                                              \
  class name {                                                                \
    struct concept_t                                                          \
      : decltype(DYNO_PP_CONCAT(dyno_concept_for_, name)::make_type())        \
    { };                                                                      \
  public:                                                                     \
    template <typename T>                                                     \
    name(T&& x)                                                               \
      : poly_{static_cast<T&&>(x), ::dyno::make_concept_map(                  \
                                        \
                                                           \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg1)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg1                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg2)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg2                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg3)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg3                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                                                     \
      )}                                                                      \
    { }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg1>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg1>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg1>\
      DYNO_PP_VARIADIC_HEAD arg1(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg1)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg1>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg1>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg1>\
      DYNO_PP_VARIADIC_HEAD arg1(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg1)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg2>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg2>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg2>\
      DYNO_PP_VARIADIC_HEAD arg2(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg2)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg2>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg2>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg2>\
      DYNO_PP_VARIADIC_HEAD arg2(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg2)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg3>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg3>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg3>\
      DYNO_PP_VARIADIC_HEAD arg3(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg3)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg3>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg3>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg3>\
      DYNO_PP_VARIADIC_HEAD arg3(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg3)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                                                     \
  private:                                                                    \
    ::dyno::poly<concept_t> poly_;                                            \
  }



#define DYNO_PP_INTERFACE_IMPL_4(name, arg1, arg2, arg3, arg4)\
  struct DYNO_PP_CONCAT(dyno_concept_for_, name) {                            \
    static auto make_type() {                                                 \
      return ::dyno::requires_(                                                \
                                        \
                                                           \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg1)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg1>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg2)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg2>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg3)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg3>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg4)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg4>\
                                                                     \
      );                                                                      \
    }                                                                         \
  };                                                                          \
                                                                              \
  class name {                                                                \
    struct concept_t                                                          \
      : decltype(DYNO_PP_CONCAT(dyno_concept_for_, name)::make_type())        \
    { };                                                                      \
  public:                                                                     \
    template <typename T>                                                     \
    name(T&& x)                                                               \
      : poly_{static_cast<T&&>(x), ::dyno::make_concept_map(                  \
                                        \
                                                           \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg1)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg1                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg2)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg2                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg3)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg3                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg4)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg4                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                                                     \
      )}                                                                      \
    { }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg1>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg1>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg1>\
      DYNO_PP_VARIADIC_HEAD arg1(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg1)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg1>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg1>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg1>\
      DYNO_PP_VARIADIC_HEAD arg1(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg1)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg2>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg2>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg2>\
      DYNO_PP_VARIADIC_HEAD arg2(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg2)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg2>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg2>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg2>\
      DYNO_PP_VARIADIC_HEAD arg2(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg2)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg3>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg3>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg3>\
      DYNO_PP_VARIADIC_HEAD arg3(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg3)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg3>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg3>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg3>\
      DYNO_PP_VARIADIC_HEAD arg3(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg3)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg4>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg4>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg4>\
      DYNO_PP_VARIADIC_HEAD arg4(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg4)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg4>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg4>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg4>\
      DYNO_PP_VARIADIC_HEAD arg4(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg4)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                                                     \
  private:                                                                    \
    ::dyno::poly<concept_t> poly_;                                            \
  }



#define DYNO_PP_INTERFACE_IMPL_5(name, arg1, arg2, arg3, arg4, arg5)\
  struct DYNO_PP_CONCAT(dyno_concept_for_, name) {                            \
    static auto make_type() {                                                 \
      return ::dyno::requires_(                                                \
                                        \
                                                           \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg1)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg1>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg2)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg2>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg3)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg3>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg4)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg4>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg5)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg5>\
                                                                     \
      );                                                                      \
    }                                                                         \
  };                                                                          \
                                                                              \
  class name {                                                                \
    struct concept_t                                                          \
      : decltype(DYNO_PP_CONCAT(dyno_concept_for_, name)::make_type())        \
    { };                                                                      \
  public:                                                                     \
    template <typename T>                                                     \
    name(T&& x)                                                               \
      : poly_{static_cast<T&&>(x), ::dyno::make_concept_map(                  \
                                        \
                                                           \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg1)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg1                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg2)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg2                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg3)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg3                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg4)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg4                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg5)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg5                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                                                     \
      )}                                                                      \
    { }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg1>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg1>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg1>\
      DYNO_PP_VARIADIC_HEAD arg1(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg1)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg1>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg1>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg1>\
      DYNO_PP_VARIADIC_HEAD arg1(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg1)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg2>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg2>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg2>\
      DYNO_PP_VARIADIC_HEAD arg2(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg2)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg2>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg2>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg2>\
      DYNO_PP_VARIADIC_HEAD arg2(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg2)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg3>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg3>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg3>\
      DYNO_PP_VARIADIC_HEAD arg3(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg3)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg3>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg3>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg3>\
      DYNO_PP_VARIADIC_HEAD arg3(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg3)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg4>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg4>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg4>\
      DYNO_PP_VARIADIC_HEAD arg4(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg4)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg4>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg4>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg4>\
      DYNO_PP_VARIADIC_HEAD arg4(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg4)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg5>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg5>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg5>\
      DYNO_PP_VARIADIC_HEAD arg5(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg5)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg5>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg5>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg5>\
      DYNO_PP_VARIADIC_HEAD arg5(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg5)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                                                     \
  private:                                                                    \
    ::dyno::poly<concept_t> poly_;                                            \
  }



#define DYNO_PP_INTERFACE_IMPL_6(name, arg1, arg2, arg3, arg4, arg5, arg6)\
  struct DYNO_PP_CONCAT(dyno_concept_for_, name) {                            \
    static auto make_type() {                                                 \
      return ::dyno::requires_(                                                \
                                        \
                                                           \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg1)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg1>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg2)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg2>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg3)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg3>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg4)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg4>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg5)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg5>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg6)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg6>\
                                                                     \
      );                                                                      \
    }                                                                         \
  };                                                                          \
                                                                              \
  class name {                                                                \
    struct concept_t                                                          \
      : decltype(DYNO_PP_CONCAT(dyno_concept_for_, name)::make_type())        \
    { };                                                                      \
  public:                                                                     \
    template <typename T>                                                     \
    name(T&& x)                                                               \
      : poly_{static_cast<T&&>(x), ::dyno::make_concept_map(                  \
                                        \
                                                           \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg1)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg1                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg2)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg2                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg3)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg3                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg4)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg4                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg5)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg5                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg6)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg6                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                                                     \
      )}                                                                      \
    { }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg1>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg1>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg1>\
      DYNO_PP_VARIADIC_HEAD arg1(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg1)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg1>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg1>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg1>\
      DYNO_PP_VARIADIC_HEAD arg1(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg1)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg2>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg2>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg2>\
      DYNO_PP_VARIADIC_HEAD arg2(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg2)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg2>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg2>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg2>\
      DYNO_PP_VARIADIC_HEAD arg2(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg2)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg3>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg3>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg3>\
      DYNO_PP_VARIADIC_HEAD arg3(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg3)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg3>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg3>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg3>\
      DYNO_PP_VARIADIC_HEAD arg3(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg3)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg4>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg4>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg4>\
      DYNO_PP_VARIADIC_HEAD arg4(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg4)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg4>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg4>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg4>\
      DYNO_PP_VARIADIC_HEAD arg4(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg4)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg5>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg5>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg5>\
      DYNO_PP_VARIADIC_HEAD arg5(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg5)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg5>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg5>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg5>\
      DYNO_PP_VARIADIC_HEAD arg5(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg5)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg6>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg6>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg6>\
      DYNO_PP_VARIADIC_HEAD arg6(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg6)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg6>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg6>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg6>\
      DYNO_PP_VARIADIC_HEAD arg6(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg6)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                                                     \
  private:                                                                    \
    ::dyno::poly<concept_t> poly_;                                            \
  }



#define DYNO_PP_INTERFACE_IMPL_7(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7)\
  struct DYNO_PP_CONCAT(dyno_concept_for_, name) {                            \
    static auto make_type() {                                                 \
      return ::dyno::requires_(                                                \
                                        \
                                                           \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg1)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg1>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg2)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg2>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg3)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg3>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg4)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg4>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg5)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg5>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg6)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg6>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg7)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg7>\
                                                                     \
      );                                                                      \
    }                                                                         \
  };                                                                          \
                                                                              \
  class name {                                                                \
    struct concept_t                                                          \
      : decltype(DYNO_PP_CONCAT(dyno_concept_for_, name)::make_type())        \
    { };                                                                      \
  public:                                                                     \
    template <typename T>                                                     \
    name(T&& x)                                                               \
      : poly_{static_cast<T&&>(x), ::dyno::make_concept_map(                  \
                                        \
                                                           \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg1)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg1                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg2)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg2                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg3)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg3                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg4)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg4                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg5)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg5                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg6)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg6                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg7)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg7                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                                                     \
      )}                                                                      \
    { }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg1>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg1>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg1>\
      DYNO_PP_VARIADIC_HEAD arg1(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg1)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg1>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg1>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg1>\
      DYNO_PP_VARIADIC_HEAD arg1(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg1)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg2>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg2>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg2>\
      DYNO_PP_VARIADIC_HEAD arg2(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg2)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg2>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg2>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg2>\
      DYNO_PP_VARIADIC_HEAD arg2(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg2)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg3>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg3>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg3>\
      DYNO_PP_VARIADIC_HEAD arg3(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg3)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg3>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg3>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg3>\
      DYNO_PP_VARIADIC_HEAD arg3(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg3)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg4>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg4>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg4>\
      DYNO_PP_VARIADIC_HEAD arg4(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg4)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg4>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg4>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg4>\
      DYNO_PP_VARIADIC_HEAD arg4(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg4)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg5>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg5>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg5>\
      DYNO_PP_VARIADIC_HEAD arg5(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg5)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg5>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg5>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg5>\
      DYNO_PP_VARIADIC_HEAD arg5(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg5)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg6>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg6>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg6>\
      DYNO_PP_VARIADIC_HEAD arg6(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg6)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg6>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg6>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg6>\
      DYNO_PP_VARIADIC_HEAD arg6(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg6)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg7>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg7>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg7>\
      DYNO_PP_VARIADIC_HEAD arg7(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg7)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg7>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg7>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg7>\
      DYNO_PP_VARIADIC_HEAD arg7(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg7)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                                                     \
  private:                                                                    \
    ::dyno::poly<concept_t> poly_;                                            \
  }



#define DYNO_PP_INTERFACE_IMPL_8(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8)\
  struct DYNO_PP_CONCAT(dyno_concept_for_, name) {                            \
    static auto make_type() {                                                 \
      return ::dyno::requires_(                                                \
                                        \
                                                           \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg1)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg1>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg2)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg2>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg3)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg3>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg4)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg4>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg5)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg5>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg6)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg6>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg7)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg7>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg8)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg8>\
                                                                     \
      );                                                                      \
    }                                                                         \
  };                                                                          \
                                                                              \
  class name {                                                                \
    struct concept_t                                                          \
      : decltype(DYNO_PP_CONCAT(dyno_concept_for_, name)::make_type())        \
    { };                                                                      \
  public:                                                                     \
    template <typename T>                                                     \
    name(T&& x)                                                               \
      : poly_{static_cast<T&&>(x), ::dyno::make_concept_map(                  \
                                        \
                                                           \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg1)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg1                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg2)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg2                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg3)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg3                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg4)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg4                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg5)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg5                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg6)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg6                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg7)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg7                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg8)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg8                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                                                     \
      )}                                                                      \
    { }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg1>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg1>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg1>\
      DYNO_PP_VARIADIC_HEAD arg1(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg1)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg1>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg1>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg1>\
      DYNO_PP_VARIADIC_HEAD arg1(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg1)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg2>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg2>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg2>\
      DYNO_PP_VARIADIC_HEAD arg2(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg2)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg2>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg2>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg2>\
      DYNO_PP_VARIADIC_HEAD arg2(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg2)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg3>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg3>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg3>\
      DYNO_PP_VARIADIC_HEAD arg3(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg3)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg3>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg3>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg3>\
      DYNO_PP_VARIADIC_HEAD arg3(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg3)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg4>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg4>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg4>\
      DYNO_PP_VARIADIC_HEAD arg4(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg4)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg4>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg4>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg4>\
      DYNO_PP_VARIADIC_HEAD arg4(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg4)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg5>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg5>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg5>\
      DYNO_PP_VARIADIC_HEAD arg5(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg5)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg5>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg5>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg5>\
      DYNO_PP_VARIADIC_HEAD arg5(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg5)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg6>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg6>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg6>\
      DYNO_PP_VARIADIC_HEAD arg6(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg6)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg6>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg6>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg6>\
      DYNO_PP_VARIADIC_HEAD arg6(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg6)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg7>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg7>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg7>\
      DYNO_PP_VARIADIC_HEAD arg7(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg7)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg7>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg7>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg7>\
      DYNO_PP_VARIADIC_HEAD arg7(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg7)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg8>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg8>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg8>\
      DYNO_PP_VARIADIC_HEAD arg8(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg8)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg8>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg8>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg8>\
      DYNO_PP_VARIADIC_HEAD arg8(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg8)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                                                     \
  private:                                                                    \
    ::dyno::poly<concept_t> poly_;                                            \
  }



#define DYNO_PP_INTERFACE_IMPL_9(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9)\
  struct DYNO_PP_CONCAT(dyno_concept_for_, name) {                            \
    static auto make_type() {                                                 \
      return ::dyno::requires_(                                                \
                                        \
                                                           \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg1)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg1>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg2)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg2>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg3)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg3>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg4)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg4>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg5)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg5>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg6)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg6>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg7)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg7>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg8)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg8>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg9)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg9>\
                                                                     \
      );                                                                      \
    }                                                                         \
  };                                                                          \
                                                                              \
  class name {                                                                \
    struct concept_t                                                          \
      : decltype(DYNO_PP_CONCAT(dyno_concept_for_, name)::make_type())        \
    { };                                                                      \
  public:                                                                     \
    template <typename T>                                                     \
    name(T&& x)                                                               \
      : poly_{static_cast<T&&>(x), ::dyno::make_concept_map(                  \
                                        \
                                                           \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg1)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg1                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg2)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg2                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg3)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg3                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg4)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg4                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg5)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg5                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg6)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg6                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg7)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg7                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg8)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg8                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg9)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg9                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                                                     \
      )}                                                                      \
    { }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg1>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg1>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg1>\
      DYNO_PP_VARIADIC_HEAD arg1(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg1)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg1>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg1>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg1>\
      DYNO_PP_VARIADIC_HEAD arg1(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg1)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg2>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg2>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg2>\
      DYNO_PP_VARIADIC_HEAD arg2(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg2)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg2>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg2>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg2>\
      DYNO_PP_VARIADIC_HEAD arg2(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg2)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg3>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg3>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg3>\
      DYNO_PP_VARIADIC_HEAD arg3(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg3)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg3>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg3>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg3>\
      DYNO_PP_VARIADIC_HEAD arg3(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg3)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg4>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg4>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg4>\
      DYNO_PP_VARIADIC_HEAD arg4(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg4)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg4>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg4>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg4>\
      DYNO_PP_VARIADIC_HEAD arg4(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg4)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg5>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg5>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg5>\
      DYNO_PP_VARIADIC_HEAD arg5(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg5)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg5>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg5>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg5>\
      DYNO_PP_VARIADIC_HEAD arg5(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg5)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg6>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg6>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg6>\
      DYNO_PP_VARIADIC_HEAD arg6(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg6)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg6>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg6>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg6>\
      DYNO_PP_VARIADIC_HEAD arg6(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg6)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg7>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg7>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg7>\
      DYNO_PP_VARIADIC_HEAD arg7(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg7)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg7>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg7>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg7>\
      DYNO_PP_VARIADIC_HEAD arg7(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg7)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg8>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg8>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg8>\
      DYNO_PP_VARIADIC_HEAD arg8(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg8)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg8>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg8>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg8>\
      DYNO_PP_VARIADIC_HEAD arg8(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg8)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg9>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg9>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg9>\
      DYNO_PP_VARIADIC_HEAD arg9(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg9)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg9>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg9>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg9>\
      DYNO_PP_VARIADIC_HEAD arg9(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg9)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                                                     \
  private:                                                                    \
    ::dyno::poly<concept_t> poly_;                                            \
  }



#define DYNO_PP_INTERFACE_IMPL_10(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10)\
  struct DYNO_PP_CONCAT(dyno_concept_for_, name) {                            \
    static auto make_type() {                                                 \
      return ::dyno::requires_(                                                \
                                        \
                                                           \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg1)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg1>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg2)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg2>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg3)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg3>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg4)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg4>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg5)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg5>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg6)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg6>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg7)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg7>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg8)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg8>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg9)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg9>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg10)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg10>\
                                                                     \
      );                                                                      \
    }                                                                         \
  };                                                                          \
                                                                              \
  class name {                                                                \
    struct concept_t                                                          \
      : decltype(DYNO_PP_CONCAT(dyno_concept_for_, name)::make_type())        \
    { };                                                                      \
  public:                                                                     \
    template <typename T>                                                     \
    name(T&& x)                                                               \
      : poly_{static_cast<T&&>(x), ::dyno::make_concept_map(                  \
                                        \
                                                           \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg1)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg1                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg2)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg2                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg3)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg3                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg4)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg4                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg5)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg5                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg6)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg6                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg7)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg7                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg8)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg8                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg9)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg9                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg10)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg10                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                                                     \
      )}                                                                      \
    { }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg1>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg1>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg1>\
      DYNO_PP_VARIADIC_HEAD arg1(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg1)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg1>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg1>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg1>\
      DYNO_PP_VARIADIC_HEAD arg1(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg1)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg2>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg2>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg2>\
      DYNO_PP_VARIADIC_HEAD arg2(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg2)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg2>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg2>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg2>\
      DYNO_PP_VARIADIC_HEAD arg2(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg2)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg3>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg3>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg3>\
      DYNO_PP_VARIADIC_HEAD arg3(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg3)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg3>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg3>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg3>\
      DYNO_PP_VARIADIC_HEAD arg3(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg3)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg4>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg4>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg4>\
      DYNO_PP_VARIADIC_HEAD arg4(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg4)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg4>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg4>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg4>\
      DYNO_PP_VARIADIC_HEAD arg4(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg4)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg5>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg5>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg5>\
      DYNO_PP_VARIADIC_HEAD arg5(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg5)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg5>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg5>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg5>\
      DYNO_PP_VARIADIC_HEAD arg5(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg5)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg6>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg6>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg6>\
      DYNO_PP_VARIADIC_HEAD arg6(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg6)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg6>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg6>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg6>\
      DYNO_PP_VARIADIC_HEAD arg6(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg6)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg7>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg7>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg7>\
      DYNO_PP_VARIADIC_HEAD arg7(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg7)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg7>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg7>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg7>\
      DYNO_PP_VARIADIC_HEAD arg7(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg7)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg8>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg8>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg8>\
      DYNO_PP_VARIADIC_HEAD arg8(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg8)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg8>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg8>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg8>\
      DYNO_PP_VARIADIC_HEAD arg8(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg8)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg9>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg9>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg9>\
      DYNO_PP_VARIADIC_HEAD arg9(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg9)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg9>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg9>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg9>\
      DYNO_PP_VARIADIC_HEAD arg9(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg9)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg10>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg10>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg10>\
      DYNO_PP_VARIADIC_HEAD arg10(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg10)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg10>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg10>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg10>\
      DYNO_PP_VARIADIC_HEAD arg10(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg10)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                                                     \
  private:                                                                    \
    ::dyno::poly<concept_t> poly_;                                            \
  }



#define DYNO_PP_INTERFACE_IMPL_11(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11)\
  struct DYNO_PP_CONCAT(dyno_concept_for_, name) {                            \
    static auto make_type() {                                                 \
      return ::dyno::requires_(                                                \
                                        \
                                                           \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg1)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg1>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg2)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg2>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg3)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg3>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg4)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg4>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg5)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg5>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg6)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg6>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg7)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg7>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg8)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg8>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg9)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg9>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg10)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg10>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg11)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg11>\
                                                                     \
      );                                                                      \
    }                                                                         \
  };                                                                          \
                                                                              \
  class name {                                                                \
    struct concept_t                                                          \
      : decltype(DYNO_PP_CONCAT(dyno_concept_for_, name)::make_type())        \
    { };                                                                      \
  public:                                                                     \
    template <typename T>                                                     \
    name(T&& x)                                                               \
      : poly_{static_cast<T&&>(x), ::dyno::make_concept_map(                  \
                                        \
                                                           \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg1)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg1                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg2)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg2                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg3)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg3                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg4)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg4                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg5)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg5                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg6)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg6                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg7)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg7                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg8)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg8                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg9)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg9                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg10)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg10                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg11)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg11                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                                                     \
      )}                                                                      \
    { }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg1>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg1>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg1>\
      DYNO_PP_VARIADIC_HEAD arg1(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg1)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg1>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg1>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg1>\
      DYNO_PP_VARIADIC_HEAD arg1(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg1)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg2>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg2>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg2>\
      DYNO_PP_VARIADIC_HEAD arg2(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg2)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg2>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg2>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg2>\
      DYNO_PP_VARIADIC_HEAD arg2(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg2)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg3>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg3>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg3>\
      DYNO_PP_VARIADIC_HEAD arg3(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg3)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg3>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg3>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg3>\
      DYNO_PP_VARIADIC_HEAD arg3(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg3)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg4>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg4>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg4>\
      DYNO_PP_VARIADIC_HEAD arg4(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg4)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg4>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg4>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg4>\
      DYNO_PP_VARIADIC_HEAD arg4(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg4)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg5>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg5>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg5>\
      DYNO_PP_VARIADIC_HEAD arg5(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg5)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg5>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg5>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg5>\
      DYNO_PP_VARIADIC_HEAD arg5(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg5)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg6>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg6>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg6>\
      DYNO_PP_VARIADIC_HEAD arg6(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg6)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg6>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg6>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg6>\
      DYNO_PP_VARIADIC_HEAD arg6(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg6)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg7>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg7>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg7>\
      DYNO_PP_VARIADIC_HEAD arg7(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg7)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg7>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg7>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg7>\
      DYNO_PP_VARIADIC_HEAD arg7(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg7)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg8>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg8>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg8>\
      DYNO_PP_VARIADIC_HEAD arg8(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg8)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg8>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg8>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg8>\
      DYNO_PP_VARIADIC_HEAD arg8(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg8)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg9>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg9>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg9>\
      DYNO_PP_VARIADIC_HEAD arg9(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg9)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg9>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg9>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg9>\
      DYNO_PP_VARIADIC_HEAD arg9(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg9)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg10>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg10>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg10>\
      DYNO_PP_VARIADIC_HEAD arg10(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg10)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg10>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg10>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg10>\
      DYNO_PP_VARIADIC_HEAD arg10(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg10)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg11>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg11>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg11>\
      DYNO_PP_VARIADIC_HEAD arg11(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg11)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg11>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg11>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg11>\
      DYNO_PP_VARIADIC_HEAD arg11(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg11)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                                                     \
  private:                                                                    \
    ::dyno::poly<concept_t> poly_;                                            \
  }



#define DYNO_PP_INTERFACE_IMPL_12(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12)\
  struct DYNO_PP_CONCAT(dyno_concept_for_, name) {                            \
    static auto make_type() {                                                 \
      return ::dyno::requires_(                                                \
                                        \
                                                           \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg1)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg1>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg2)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg2>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg3)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg3>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg4)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg4>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg5)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg5>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg6)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg6>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg7)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg7>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg8)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg8>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg9)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg9>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg10)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg10>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg11)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg11>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg12)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg12>\
                                                                     \
      );                                                                      \
    }                                                                         \
  };                                                                          \
                                                                              \
  class name {                                                                \
    struct concept_t                                                          \
      : decltype(DYNO_PP_CONCAT(dyno_concept_for_, name)::make_type())        \
    { };                                                                      \
  public:                                                                     \
    template <typename T>                                                     \
    name(T&& x)                                                               \
      : poly_{static_cast<T&&>(x), ::dyno::make_concept_map(                  \
                                        \
                                                           \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg1)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg1                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg2)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg2                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg3)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg3                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg4)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg4                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg5)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg5                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg6)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg6                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg7)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg7                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg8)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg8                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg9)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg9                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg10)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg10                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg11)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg11                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg12)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg12                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                                                     \
      )}                                                                      \
    { }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg1>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg1>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg1>\
      DYNO_PP_VARIADIC_HEAD arg1(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg1)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg1>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg1>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg1>\
      DYNO_PP_VARIADIC_HEAD arg1(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg1)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg2>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg2>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg2>\
      DYNO_PP_VARIADIC_HEAD arg2(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg2)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg2>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg2>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg2>\
      DYNO_PP_VARIADIC_HEAD arg2(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg2)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg3>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg3>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg3>\
      DYNO_PP_VARIADIC_HEAD arg3(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg3)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg3>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg3>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg3>\
      DYNO_PP_VARIADIC_HEAD arg3(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg3)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg4>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg4>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg4>\
      DYNO_PP_VARIADIC_HEAD arg4(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg4)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg4>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg4>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg4>\
      DYNO_PP_VARIADIC_HEAD arg4(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg4)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg5>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg5>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg5>\
      DYNO_PP_VARIADIC_HEAD arg5(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg5)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg5>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg5>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg5>\
      DYNO_PP_VARIADIC_HEAD arg5(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg5)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg6>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg6>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg6>\
      DYNO_PP_VARIADIC_HEAD arg6(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg6)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg6>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg6>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg6>\
      DYNO_PP_VARIADIC_HEAD arg6(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg6)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg7>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg7>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg7>\
      DYNO_PP_VARIADIC_HEAD arg7(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg7)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg7>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg7>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg7>\
      DYNO_PP_VARIADIC_HEAD arg7(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg7)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg8>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg8>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg8>\
      DYNO_PP_VARIADIC_HEAD arg8(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg8)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg8>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg8>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg8>\
      DYNO_PP_VARIADIC_HEAD arg8(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg8)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg9>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg9>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg9>\
      DYNO_PP_VARIADIC_HEAD arg9(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg9)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg9>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg9>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg9>\
      DYNO_PP_VARIADIC_HEAD arg9(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg9)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg10>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg10>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg10>\
      DYNO_PP_VARIADIC_HEAD arg10(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg10)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg10>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg10>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg10>\
      DYNO_PP_VARIADIC_HEAD arg10(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg10)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg11>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg11>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg11>\
      DYNO_PP_VARIADIC_HEAD arg11(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg11)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg11>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg11>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg11>\
      DYNO_PP_VARIADIC_HEAD arg11(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg11)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg12>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg12>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg12>\
      DYNO_PP_VARIADIC_HEAD arg12(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg12)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg12>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg12>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg12>\
      DYNO_PP_VARIADIC_HEAD arg12(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg12)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                                                     \
  private:                                                                    \
    ::dyno::poly<concept_t> poly_;                                            \
  }



#define DYNO_PP_INTERFACE_IMPL_13(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13)\
  struct DYNO_PP_CONCAT(dyno_concept_for_, name) {                            \
    static auto make_type() {                                                 \
      return ::dyno::requires_(                                                \
                                        \
                                                           \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg1)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg1>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg2)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg2>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg3)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg3>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg4)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg4>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg5)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg5>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg6)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg6>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg7)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg7>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg8)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg8>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg9)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg9>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg10)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg10>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg11)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg11>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg12)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg12>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg13)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg13>\
                                                                     \
      );                                                                      \
    }                                                                         \
  };                                                                          \
                                                                              \
  class name {                                                                \
    struct concept_t                                                          \
      : decltype(DYNO_PP_CONCAT(dyno_concept_for_, name)::make_type())        \
    { };                                                                      \
  public:                                                                     \
    template <typename T>                                                     \
    name(T&& x)                                                               \
      : poly_{static_cast<T&&>(x), ::dyno::make_concept_map(                  \
                                        \
                                                           \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg1)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg1                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg2)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg2                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg3)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg3                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg4)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg4                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg5)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg5                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg6)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg6                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg7)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg7                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg8)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg8                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg9)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg9                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg10)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg10                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg11)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg11                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg12)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg12                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg13)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg13                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                                                     \
      )}                                                                      \
    { }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg1>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg1>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg1>\
      DYNO_PP_VARIADIC_HEAD arg1(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg1)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg1>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg1>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg1>\
      DYNO_PP_VARIADIC_HEAD arg1(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg1)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg2>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg2>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg2>\
      DYNO_PP_VARIADIC_HEAD arg2(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg2)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg2>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg2>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg2>\
      DYNO_PP_VARIADIC_HEAD arg2(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg2)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg3>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg3>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg3>\
      DYNO_PP_VARIADIC_HEAD arg3(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg3)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg3>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg3>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg3>\
      DYNO_PP_VARIADIC_HEAD arg3(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg3)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg4>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg4>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg4>\
      DYNO_PP_VARIADIC_HEAD arg4(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg4)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg4>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg4>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg4>\
      DYNO_PP_VARIADIC_HEAD arg4(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg4)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg5>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg5>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg5>\
      DYNO_PP_VARIADIC_HEAD arg5(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg5)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg5>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg5>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg5>\
      DYNO_PP_VARIADIC_HEAD arg5(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg5)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg6>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg6>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg6>\
      DYNO_PP_VARIADIC_HEAD arg6(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg6)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg6>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg6>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg6>\
      DYNO_PP_VARIADIC_HEAD arg6(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg6)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg7>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg7>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg7>\
      DYNO_PP_VARIADIC_HEAD arg7(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg7)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg7>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg7>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg7>\
      DYNO_PP_VARIADIC_HEAD arg7(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg7)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg8>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg8>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg8>\
      DYNO_PP_VARIADIC_HEAD arg8(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg8)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg8>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg8>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg8>\
      DYNO_PP_VARIADIC_HEAD arg8(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg8)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg9>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg9>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg9>\
      DYNO_PP_VARIADIC_HEAD arg9(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg9)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg9>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg9>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg9>\
      DYNO_PP_VARIADIC_HEAD arg9(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg9)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg10>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg10>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg10>\
      DYNO_PP_VARIADIC_HEAD arg10(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg10)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg10>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg10>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg10>\
      DYNO_PP_VARIADIC_HEAD arg10(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg10)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg11>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg11>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg11>\
      DYNO_PP_VARIADIC_HEAD arg11(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg11)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg11>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg11>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg11>\
      DYNO_PP_VARIADIC_HEAD arg11(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg11)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg12>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg12>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg12>\
      DYNO_PP_VARIADIC_HEAD arg12(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg12)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg12>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg12>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg12>\
      DYNO_PP_VARIADIC_HEAD arg12(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg12)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg13>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg13>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg13>\
      DYNO_PP_VARIADIC_HEAD arg13(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg13)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg13>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg13>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg13>\
      DYNO_PP_VARIADIC_HEAD arg13(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg13)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                                                     \
  private:                                                                    \
    ::dyno::poly<concept_t> poly_;                                            \
  }



#define DYNO_PP_INTERFACE_IMPL_14(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14)\
  struct DYNO_PP_CONCAT(dyno_concept_for_, name) {                            \
    static auto make_type() {                                                 \
      return ::dyno::requires_(                                                \
                                        \
                                                           \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg1)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg1>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg2)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg2>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg3)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg3>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg4)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg4>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg5)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg5>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg6)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg6>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg7)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg7>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg8)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg8>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg9)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg9>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg10)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg10>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg11)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg11>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg12)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg12>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg13)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg13>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg14)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg14>\
                                                                     \
      );                                                                      \
    }                                                                         \
  };                                                                          \
                                                                              \
  class name {                                                                \
    struct concept_t                                                          \
      : decltype(DYNO_PP_CONCAT(dyno_concept_for_, name)::make_type())        \
    { };                                                                      \
  public:                                                                     \
    template <typename T>                                                     \
    name(T&& x)                                                               \
      : poly_{static_cast<T&&>(x), ::dyno::make_concept_map(                  \
                                        \
                                                           \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg1)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg1                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg2)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg2                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg3)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg3                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg4)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg4                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg5)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg5                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg6)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg6                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg7)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg7                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg8)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg8                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg9)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg9                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg10)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg10                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg11)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg11                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg12)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg12                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg13)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg13                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg14)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg14                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                                                     \
      )}                                                                      \
    { }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg1>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg1>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg1>\
      DYNO_PP_VARIADIC_HEAD arg1(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg1)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg1>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg1>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg1>\
      DYNO_PP_VARIADIC_HEAD arg1(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg1)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg2>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg2>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg2>\
      DYNO_PP_VARIADIC_HEAD arg2(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg2)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg2>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg2>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg2>\
      DYNO_PP_VARIADIC_HEAD arg2(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg2)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg3>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg3>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg3>\
      DYNO_PP_VARIADIC_HEAD arg3(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg3)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg3>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg3>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg3>\
      DYNO_PP_VARIADIC_HEAD arg3(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg3)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg4>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg4>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg4>\
      DYNO_PP_VARIADIC_HEAD arg4(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg4)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg4>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg4>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg4>\
      DYNO_PP_VARIADIC_HEAD arg4(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg4)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg5>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg5>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg5>\
      DYNO_PP_VARIADIC_HEAD arg5(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg5)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg5>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg5>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg5>\
      DYNO_PP_VARIADIC_HEAD arg5(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg5)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg6>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg6>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg6>\
      DYNO_PP_VARIADIC_HEAD arg6(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg6)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg6>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg6>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg6>\
      DYNO_PP_VARIADIC_HEAD arg6(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg6)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg7>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg7>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg7>\
      DYNO_PP_VARIADIC_HEAD arg7(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg7)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg7>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg7>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg7>\
      DYNO_PP_VARIADIC_HEAD arg7(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg7)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg8>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg8>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg8>\
      DYNO_PP_VARIADIC_HEAD arg8(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg8)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg8>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg8>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg8>\
      DYNO_PP_VARIADIC_HEAD arg8(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg8)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg9>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg9>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg9>\
      DYNO_PP_VARIADIC_HEAD arg9(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg9)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg9>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg9>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg9>\
      DYNO_PP_VARIADIC_HEAD arg9(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg9)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg10>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg10>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg10>\
      DYNO_PP_VARIADIC_HEAD arg10(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg10)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg10>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg10>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg10>\
      DYNO_PP_VARIADIC_HEAD arg10(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg10)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg11>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg11>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg11>\
      DYNO_PP_VARIADIC_HEAD arg11(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg11)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg11>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg11>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg11>\
      DYNO_PP_VARIADIC_HEAD arg11(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg11)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg12>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg12>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg12>\
      DYNO_PP_VARIADIC_HEAD arg12(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg12)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg12>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg12>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg12>\
      DYNO_PP_VARIADIC_HEAD arg12(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg12)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg13>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg13>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg13>\
      DYNO_PP_VARIADIC_HEAD arg13(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg13)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg13>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg13>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg13>\
      DYNO_PP_VARIADIC_HEAD arg13(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg13)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg14>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg14>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg14>\
      DYNO_PP_VARIADIC_HEAD arg14(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg14)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg14>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg14>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg14>\
      DYNO_PP_VARIADIC_HEAD arg14(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg14)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                                                     \
  private:                                                                    \
    ::dyno::poly<concept_t> poly_;                                            \
  }



#define DYNO_PP_INTERFACE_IMPL_15(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15)\
  struct DYNO_PP_CONCAT(dyno_concept_for_, name) {                            \
    static auto make_type() {                                                 \
      return ::dyno::requires_(                                                \
                                        \
                                                           \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg1)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg1>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg2)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg2>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg3)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg3>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg4)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg4>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg5)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg5>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg6)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg6>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg7)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg7>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg8)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg8>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg9)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg9>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg10)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg10>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg11)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg11>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg12)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg12>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg13)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg13>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg14)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg14>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg15)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg15>\
                                                                     \
      );                                                                      \
    }                                                                         \
  };                                                                          \
                                                                              \
  class name {                                                                \
    struct concept_t                                                          \
      : decltype(DYNO_PP_CONCAT(dyno_concept_for_, name)::make_type())        \
    { };                                                                      \
  public:                                                                     \
    template <typename T>                                                     \
    name(T&& x)                                                               \
      : poly_{static_cast<T&&>(x), ::dyno::make_concept_map(                  \
                                        \
                                                           \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg1)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg1                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg2)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg2                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg3)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg3                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg4)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg4                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg5)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg5                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg6)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg6                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg7)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg7                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg8)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg8                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg9)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg9                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg10)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg10                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg11)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg11                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg12)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg12                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg13)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg13                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg14)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg14                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg15)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg15                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                                                     \
      )}                                                                      \
    { }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg1>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg1>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg1>\
      DYNO_PP_VARIADIC_HEAD arg1(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg1)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg1>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg1>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg1>\
      DYNO_PP_VARIADIC_HEAD arg1(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg1)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg2>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg2>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg2>\
      DYNO_PP_VARIADIC_HEAD arg2(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg2)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg2>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg2>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg2>\
      DYNO_PP_VARIADIC_HEAD arg2(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg2)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg3>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg3>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg3>\
      DYNO_PP_VARIADIC_HEAD arg3(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg3)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg3>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg3>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg3>\
      DYNO_PP_VARIADIC_HEAD arg3(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg3)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg4>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg4>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg4>\
      DYNO_PP_VARIADIC_HEAD arg4(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg4)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg4>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg4>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg4>\
      DYNO_PP_VARIADIC_HEAD arg4(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg4)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg5>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg5>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg5>\
      DYNO_PP_VARIADIC_HEAD arg5(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg5)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg5>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg5>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg5>\
      DYNO_PP_VARIADIC_HEAD arg5(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg5)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg6>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg6>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg6>\
      DYNO_PP_VARIADIC_HEAD arg6(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg6)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg6>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg6>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg6>\
      DYNO_PP_VARIADIC_HEAD arg6(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg6)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg7>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg7>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg7>\
      DYNO_PP_VARIADIC_HEAD arg7(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg7)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg7>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg7>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg7>\
      DYNO_PP_VARIADIC_HEAD arg7(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg7)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg8>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg8>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg8>\
      DYNO_PP_VARIADIC_HEAD arg8(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg8)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg8>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg8>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg8>\
      DYNO_PP_VARIADIC_HEAD arg8(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg8)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg9>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg9>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg9>\
      DYNO_PP_VARIADIC_HEAD arg9(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg9)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg9>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg9>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg9>\
      DYNO_PP_VARIADIC_HEAD arg9(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg9)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg10>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg10>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg10>\
      DYNO_PP_VARIADIC_HEAD arg10(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg10)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg10>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg10>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg10>\
      DYNO_PP_VARIADIC_HEAD arg10(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg10)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg11>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg11>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg11>\
      DYNO_PP_VARIADIC_HEAD arg11(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg11)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg11>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg11>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg11>\
      DYNO_PP_VARIADIC_HEAD arg11(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg11)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg12>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg12>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg12>\
      DYNO_PP_VARIADIC_HEAD arg12(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg12)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg12>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg12>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg12>\
      DYNO_PP_VARIADIC_HEAD arg12(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg12)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg13>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg13>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg13>\
      DYNO_PP_VARIADIC_HEAD arg13(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg13)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg13>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg13>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg13>\
      DYNO_PP_VARIADIC_HEAD arg13(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg13)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg14>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg14>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg14>\
      DYNO_PP_VARIADIC_HEAD arg14(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg14)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg14>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg14>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg14>\
      DYNO_PP_VARIADIC_HEAD arg14(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg14)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg15>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg15>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg15>\
      DYNO_PP_VARIADIC_HEAD arg15(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg15)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg15>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg15>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg15>\
      DYNO_PP_VARIADIC_HEAD arg15(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg15)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                                                     \
  private:                                                                    \
    ::dyno::poly<concept_t> poly_;                                            \
  }



#define DYNO_PP_INTERFACE_IMPL_16(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16)\
  struct DYNO_PP_CONCAT(dyno_concept_for_, name) {                            \
    static auto make_type() {                                                 \
      return ::dyno::requires_(                                                \
                                        \
                                                           \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg1)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg1>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg2)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg2>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg3)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg3>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg4)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg4>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg5)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg5>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg6)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg6>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg7)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg7>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg8)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg8>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg9)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg9>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg10)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg10>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg11)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg11>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg12)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg12>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg13)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg13>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg14)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg14>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg15)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg15>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg16)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg16>\
                                                                     \
      );                                                                      \
    }                                                                         \
  };                                                                          \
                                                                              \
  class name {                                                                \
    struct concept_t                                                          \
      : decltype(DYNO_PP_CONCAT(dyno_concept_for_, name)::make_type())        \
    { };                                                                      \
  public:                                                                     \
    template <typename T>                                                     \
    name(T&& x)                                                               \
      : poly_{static_cast<T&&>(x), ::dyno::make_concept_map(                  \
                                        \
                                                           \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg1)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg1                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg2)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg2                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg3)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg3                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg4)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg4                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg5)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg5                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg6)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg6                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg7)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg7                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg8)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg8                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg9)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg9                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg10)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg10                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg11)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg11                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg12)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg12                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg13)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg13                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg14)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg14                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg15)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg15                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg16)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg16                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                                                     \
      )}                                                                      \
    { }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg1>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg1>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg1>\
      DYNO_PP_VARIADIC_HEAD arg1(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg1)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg1>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg1>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg1>\
      DYNO_PP_VARIADIC_HEAD arg1(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg1)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg2>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg2>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg2>\
      DYNO_PP_VARIADIC_HEAD arg2(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg2)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg2>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg2>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg2>\
      DYNO_PP_VARIADIC_HEAD arg2(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg2)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg3>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg3>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg3>\
      DYNO_PP_VARIADIC_HEAD arg3(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg3)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg3>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg3>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg3>\
      DYNO_PP_VARIADIC_HEAD arg3(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg3)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg4>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg4>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg4>\
      DYNO_PP_VARIADIC_HEAD arg4(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg4)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg4>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg4>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg4>\
      DYNO_PP_VARIADIC_HEAD arg4(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg4)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg5>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg5>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg5>\
      DYNO_PP_VARIADIC_HEAD arg5(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg5)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg5>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg5>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg5>\
      DYNO_PP_VARIADIC_HEAD arg5(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg5)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg6>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg6>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg6>\
      DYNO_PP_VARIADIC_HEAD arg6(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg6)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg6>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg6>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg6>\
      DYNO_PP_VARIADIC_HEAD arg6(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg6)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg7>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg7>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg7>\
      DYNO_PP_VARIADIC_HEAD arg7(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg7)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg7>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg7>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg7>\
      DYNO_PP_VARIADIC_HEAD arg7(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg7)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg8>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg8>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg8>\
      DYNO_PP_VARIADIC_HEAD arg8(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg8)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg8>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg8>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg8>\
      DYNO_PP_VARIADIC_HEAD arg8(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg8)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg9>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg9>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg9>\
      DYNO_PP_VARIADIC_HEAD arg9(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg9)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg9>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg9>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg9>\
      DYNO_PP_VARIADIC_HEAD arg9(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg9)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg10>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg10>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg10>\
      DYNO_PP_VARIADIC_HEAD arg10(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg10)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg10>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg10>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg10>\
      DYNO_PP_VARIADIC_HEAD arg10(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg10)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg11>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg11>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg11>\
      DYNO_PP_VARIADIC_HEAD arg11(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg11)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg11>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg11>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg11>\
      DYNO_PP_VARIADIC_HEAD arg11(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg11)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg12>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg12>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg12>\
      DYNO_PP_VARIADIC_HEAD arg12(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg12)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg12>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg12>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg12>\
      DYNO_PP_VARIADIC_HEAD arg12(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg12)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg13>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg13>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg13>\
      DYNO_PP_VARIADIC_HEAD arg13(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg13)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg13>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg13>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg13>\
      DYNO_PP_VARIADIC_HEAD arg13(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg13)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg14>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg14>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg14>\
      DYNO_PP_VARIADIC_HEAD arg14(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg14)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg14>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg14>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg14>\
      DYNO_PP_VARIADIC_HEAD arg14(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg14)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg15>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg15>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg15>\
      DYNO_PP_VARIADIC_HEAD arg15(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg15)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg15>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg15>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg15>\
      DYNO_PP_VARIADIC_HEAD arg15(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg15)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg16>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg16>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg16>\
      DYNO_PP_VARIADIC_HEAD arg16(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg16)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg16>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg16>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg16>\
      DYNO_PP_VARIADIC_HEAD arg16(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg16)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                                                     \
  private:                                                                    \
    ::dyno::poly<concept_t> poly_;                                            \
  }



#define DYNO_PP_INTERFACE_IMPL_17(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16, arg17)\
  struct DYNO_PP_CONCAT(dyno_concept_for_, name) {                            \
    static auto make_type() {                                                 \
      return ::dyno::requires_(                                                \
                                        \
                                                           \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg1)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg1>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg2)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg2>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg3)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg3>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg4)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg4>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg5)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg5>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg6)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg6>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg7)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg7>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg8)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg8>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg9)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg9>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg10)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg10>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg11)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg11>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg12)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg12>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg13)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg13>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg14)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg14>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg15)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg15>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg16)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg16>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg17)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg17>\
                                                                     \
      );                                                                      \
    }                                                                         \
  };                                                                          \
                                                                              \
  class name {                                                                \
    struct concept_t                                                          \
      : decltype(DYNO_PP_CONCAT(dyno_concept_for_, name)::make_type())        \
    { };                                                                      \
  public:                                                                     \
    template <typename T>                                                     \
    name(T&& x)                                                               \
      : poly_{static_cast<T&&>(x), ::dyno::make_concept_map(                  \
                                        \
                                                           \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg1)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg1                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg2)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg2                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg3)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg3                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg4)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg4                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg5)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg5                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg6)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg6                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg7)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg7                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg8)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg8                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg9)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg9                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg10)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg10                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg11)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg11                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg12)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg12                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg13)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg13                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg14)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg14                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg15)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg15                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg16)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg16                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg17)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg17                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                                                     \
      )}                                                                      \
    { }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg1>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg1>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg1>\
      DYNO_PP_VARIADIC_HEAD arg1(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg1)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg1>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg1>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg1>\
      DYNO_PP_VARIADIC_HEAD arg1(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg1)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg2>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg2>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg2>\
      DYNO_PP_VARIADIC_HEAD arg2(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg2)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg2>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg2>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg2>\
      DYNO_PP_VARIADIC_HEAD arg2(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg2)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg3>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg3>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg3>\
      DYNO_PP_VARIADIC_HEAD arg3(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg3)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg3>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg3>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg3>\
      DYNO_PP_VARIADIC_HEAD arg3(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg3)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg4>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg4>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg4>\
      DYNO_PP_VARIADIC_HEAD arg4(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg4)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg4>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg4>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg4>\
      DYNO_PP_VARIADIC_HEAD arg4(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg4)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg5>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg5>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg5>\
      DYNO_PP_VARIADIC_HEAD arg5(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg5)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg5>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg5>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg5>\
      DYNO_PP_VARIADIC_HEAD arg5(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg5)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg6>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg6>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg6>\
      DYNO_PP_VARIADIC_HEAD arg6(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg6)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg6>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg6>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg6>\
      DYNO_PP_VARIADIC_HEAD arg6(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg6)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg7>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg7>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg7>\
      DYNO_PP_VARIADIC_HEAD arg7(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg7)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg7>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg7>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg7>\
      DYNO_PP_VARIADIC_HEAD arg7(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg7)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg8>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg8>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg8>\
      DYNO_PP_VARIADIC_HEAD arg8(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg8)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg8>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg8>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg8>\
      DYNO_PP_VARIADIC_HEAD arg8(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg8)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg9>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg9>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg9>\
      DYNO_PP_VARIADIC_HEAD arg9(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg9)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg9>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg9>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg9>\
      DYNO_PP_VARIADIC_HEAD arg9(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg9)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg10>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg10>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg10>\
      DYNO_PP_VARIADIC_HEAD arg10(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg10)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg10>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg10>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg10>\
      DYNO_PP_VARIADIC_HEAD arg10(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg10)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg11>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg11>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg11>\
      DYNO_PP_VARIADIC_HEAD arg11(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg11)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg11>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg11>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg11>\
      DYNO_PP_VARIADIC_HEAD arg11(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg11)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg12>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg12>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg12>\
      DYNO_PP_VARIADIC_HEAD arg12(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg12)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg12>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg12>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg12>\
      DYNO_PP_VARIADIC_HEAD arg12(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg12)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg13>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg13>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg13>\
      DYNO_PP_VARIADIC_HEAD arg13(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg13)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg13>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg13>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg13>\
      DYNO_PP_VARIADIC_HEAD arg13(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg13)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg14>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg14>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg14>\
      DYNO_PP_VARIADIC_HEAD arg14(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg14)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg14>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg14>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg14>\
      DYNO_PP_VARIADIC_HEAD arg14(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg14)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg15>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg15>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg15>\
      DYNO_PP_VARIADIC_HEAD arg15(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg15)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg15>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg15>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg15>\
      DYNO_PP_VARIADIC_HEAD arg15(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg15)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg16>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg16>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg16>\
      DYNO_PP_VARIADIC_HEAD arg16(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg16)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg16>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg16>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg16>\
      DYNO_PP_VARIADIC_HEAD arg16(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg16)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg17>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg17>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg17>\
      DYNO_PP_VARIADIC_HEAD arg17(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg17)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg17>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg17>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg17>\
      DYNO_PP_VARIADIC_HEAD arg17(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg17)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                                                     \
  private:                                                                    \
    ::dyno::poly<concept_t> poly_;                                            \
  }



#define DYNO_PP_INTERFACE_IMPL_18(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16, arg17, arg18)\
  struct DYNO_PP_CONCAT(dyno_concept_for_, name) {                            \
    static auto make_type() {                                                 \
      return ::dyno::requires_(                                                \
                                        \
                                                           \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg1)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg1>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg2)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg2>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg3)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg3>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg4)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg4>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg5)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg5>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg6)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg6>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg7)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg7>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg8)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg8>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg9)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg9>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg10)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg10>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg11)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg11>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg12)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg12>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg13)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg13>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg14)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg14>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg15)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg15>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg16)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg16>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg17)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg17>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg18)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg18>\
                                                                     \
      );                                                                      \
    }                                                                         \
  };                                                                          \
                                                                              \
  class name {                                                                \
    struct concept_t                                                          \
      : decltype(DYNO_PP_CONCAT(dyno_concept_for_, name)::make_type())        \
    { };                                                                      \
  public:                                                                     \
    template <typename T>                                                     \
    name(T&& x)                                                               \
      : poly_{static_cast<T&&>(x), ::dyno::make_concept_map(                  \
                                        \
                                                           \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg1)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg1                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg2)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg2                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg3)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg3                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg4)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg4                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg5)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg5                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg6)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg6                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg7)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg7                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg8)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg8                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg9)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg9                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg10)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg10                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg11)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg11                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg12)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg12                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg13)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg13                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg14)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg14                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg15)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg15                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg16)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg16                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg17)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg17                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg18)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg18                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                                                     \
      )}                                                                      \
    { }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg1>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg1>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg1>\
      DYNO_PP_VARIADIC_HEAD arg1(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg1)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg1>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg1>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg1>\
      DYNO_PP_VARIADIC_HEAD arg1(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg1)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg2>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg2>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg2>\
      DYNO_PP_VARIADIC_HEAD arg2(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg2)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg2>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg2>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg2>\
      DYNO_PP_VARIADIC_HEAD arg2(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg2)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg3>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg3>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg3>\
      DYNO_PP_VARIADIC_HEAD arg3(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg3)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg3>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg3>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg3>\
      DYNO_PP_VARIADIC_HEAD arg3(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg3)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg4>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg4>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg4>\
      DYNO_PP_VARIADIC_HEAD arg4(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg4)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg4>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg4>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg4>\
      DYNO_PP_VARIADIC_HEAD arg4(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg4)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg5>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg5>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg5>\
      DYNO_PP_VARIADIC_HEAD arg5(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg5)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg5>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg5>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg5>\
      DYNO_PP_VARIADIC_HEAD arg5(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg5)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg6>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg6>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg6>\
      DYNO_PP_VARIADIC_HEAD arg6(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg6)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg6>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg6>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg6>\
      DYNO_PP_VARIADIC_HEAD arg6(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg6)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg7>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg7>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg7>\
      DYNO_PP_VARIADIC_HEAD arg7(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg7)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg7>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg7>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg7>\
      DYNO_PP_VARIADIC_HEAD arg7(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg7)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg8>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg8>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg8>\
      DYNO_PP_VARIADIC_HEAD arg8(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg8)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg8>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg8>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg8>\
      DYNO_PP_VARIADIC_HEAD arg8(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg8)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg9>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg9>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg9>\
      DYNO_PP_VARIADIC_HEAD arg9(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg9)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg9>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg9>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg9>\
      DYNO_PP_VARIADIC_HEAD arg9(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg9)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg10>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg10>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg10>\
      DYNO_PP_VARIADIC_HEAD arg10(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg10)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg10>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg10>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg10>\
      DYNO_PP_VARIADIC_HEAD arg10(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg10)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg11>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg11>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg11>\
      DYNO_PP_VARIADIC_HEAD arg11(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg11)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg11>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg11>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg11>\
      DYNO_PP_VARIADIC_HEAD arg11(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg11)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg12>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg12>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg12>\
      DYNO_PP_VARIADIC_HEAD arg12(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg12)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg12>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg12>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg12>\
      DYNO_PP_VARIADIC_HEAD arg12(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg12)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg13>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg13>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg13>\
      DYNO_PP_VARIADIC_HEAD arg13(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg13)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg13>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg13>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg13>\
      DYNO_PP_VARIADIC_HEAD arg13(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg13)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg14>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg14>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg14>\
      DYNO_PP_VARIADIC_HEAD arg14(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg14)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg14>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg14>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg14>\
      DYNO_PP_VARIADIC_HEAD arg14(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg14)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg15>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg15>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg15>\
      DYNO_PP_VARIADIC_HEAD arg15(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg15)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg15>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg15>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg15>\
      DYNO_PP_VARIADIC_HEAD arg15(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg15)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg16>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg16>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg16>\
      DYNO_PP_VARIADIC_HEAD arg16(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg16)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg16>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg16>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg16>\
      DYNO_PP_VARIADIC_HEAD arg16(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg16)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg17>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg17>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg17>\
      DYNO_PP_VARIADIC_HEAD arg17(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg17)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg17>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg17>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg17>\
      DYNO_PP_VARIADIC_HEAD arg17(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg17)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg18>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg18>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg18>\
      DYNO_PP_VARIADIC_HEAD arg18(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg18)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg18>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg18>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg18>\
      DYNO_PP_VARIADIC_HEAD arg18(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg18)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                                                     \
  private:                                                                    \
    ::dyno::poly<concept_t> poly_;                                            \
  }



#define DYNO_PP_INTERFACE_IMPL_19(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16, arg17, arg18, arg19)\
  struct DYNO_PP_CONCAT(dyno_concept_for_, name) {                            \
    static auto make_type() {                                                 \
      return ::dyno::requires_(                                                \
                                        \
                                                           \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg1)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg1>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg2)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg2>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg3)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg3>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg4)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg4>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg5)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg5>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg6)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg6>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg7)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg7>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg8)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg8>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg9)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg9>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg10)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg10>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg11)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg11>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg12)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg12>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg13)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg13>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg14)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg14>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg15)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg15>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg16)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg16>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg17)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg17>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg18)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg18>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg19)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg19>\
                                                                     \
      );                                                                      \
    }                                                                         \
  };                                                                          \
                                                                              \
  class name {                                                                \
    struct concept_t                                                          \
      : decltype(DYNO_PP_CONCAT(dyno_concept_for_, name)::make_type())        \
    { };                                                                      \
  public:                                                                     \
    template <typename T>                                                     \
    name(T&& x)                                                               \
      : poly_{static_cast<T&&>(x), ::dyno::make_concept_map(                  \
                                        \
                                                           \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg1)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg1                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg2)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg2                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg3)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg3                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg4)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg4                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg5)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg5                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg6)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg6                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg7)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg7                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg8)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg8                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg9)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg9                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg10)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg10                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg11)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg11                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg12)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg12                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg13)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg13                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg14)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg14                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg15)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg15                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg16)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg16                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg17)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg17                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg18)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg18                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg19)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg19                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                                                     \
      )}                                                                      \
    { }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg1>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg1>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg1>\
      DYNO_PP_VARIADIC_HEAD arg1(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg1)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg1>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg1>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg1>\
      DYNO_PP_VARIADIC_HEAD arg1(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg1)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg2>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg2>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg2>\
      DYNO_PP_VARIADIC_HEAD arg2(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg2)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg2>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg2>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg2>\
      DYNO_PP_VARIADIC_HEAD arg2(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg2)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg3>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg3>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg3>\
      DYNO_PP_VARIADIC_HEAD arg3(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg3)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg3>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg3>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg3>\
      DYNO_PP_VARIADIC_HEAD arg3(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg3)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg4>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg4>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg4>\
      DYNO_PP_VARIADIC_HEAD arg4(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg4)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg4>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg4>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg4>\
      DYNO_PP_VARIADIC_HEAD arg4(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg4)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg5>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg5>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg5>\
      DYNO_PP_VARIADIC_HEAD arg5(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg5)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg5>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg5>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg5>\
      DYNO_PP_VARIADIC_HEAD arg5(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg5)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg6>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg6>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg6>\
      DYNO_PP_VARIADIC_HEAD arg6(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg6)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg6>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg6>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg6>\
      DYNO_PP_VARIADIC_HEAD arg6(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg6)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg7>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg7>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg7>\
      DYNO_PP_VARIADIC_HEAD arg7(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg7)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg7>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg7>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg7>\
      DYNO_PP_VARIADIC_HEAD arg7(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg7)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg8>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg8>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg8>\
      DYNO_PP_VARIADIC_HEAD arg8(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg8)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg8>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg8>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg8>\
      DYNO_PP_VARIADIC_HEAD arg8(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg8)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg9>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg9>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg9>\
      DYNO_PP_VARIADIC_HEAD arg9(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg9)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg9>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg9>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg9>\
      DYNO_PP_VARIADIC_HEAD arg9(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg9)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg10>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg10>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg10>\
      DYNO_PP_VARIADIC_HEAD arg10(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg10)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg10>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg10>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg10>\
      DYNO_PP_VARIADIC_HEAD arg10(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg10)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg11>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg11>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg11>\
      DYNO_PP_VARIADIC_HEAD arg11(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg11)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg11>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg11>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg11>\
      DYNO_PP_VARIADIC_HEAD arg11(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg11)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg12>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg12>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg12>\
      DYNO_PP_VARIADIC_HEAD arg12(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg12)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg12>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg12>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg12>\
      DYNO_PP_VARIADIC_HEAD arg12(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg12)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg13>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg13>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg13>\
      DYNO_PP_VARIADIC_HEAD arg13(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg13)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg13>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg13>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg13>\
      DYNO_PP_VARIADIC_HEAD arg13(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg13)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg14>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg14>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg14>\
      DYNO_PP_VARIADIC_HEAD arg14(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg14)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg14>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg14>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg14>\
      DYNO_PP_VARIADIC_HEAD arg14(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg14)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg15>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg15>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg15>\
      DYNO_PP_VARIADIC_HEAD arg15(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg15)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg15>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg15>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg15>\
      DYNO_PP_VARIADIC_HEAD arg15(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg15)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg16>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg16>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg16>\
      DYNO_PP_VARIADIC_HEAD arg16(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg16)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg16>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg16>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg16>\
      DYNO_PP_VARIADIC_HEAD arg16(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg16)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg17>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg17>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg17>\
      DYNO_PP_VARIADIC_HEAD arg17(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg17)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg17>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg17>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg17>\
      DYNO_PP_VARIADIC_HEAD arg17(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg17)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg18>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg18>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg18>\
      DYNO_PP_VARIADIC_HEAD arg18(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg18)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg18>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg18>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg18>\
      DYNO_PP_VARIADIC_HEAD arg18(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg18)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg19>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg19>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg19>\
      DYNO_PP_VARIADIC_HEAD arg19(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg19)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg19>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg19>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg19>\
      DYNO_PP_VARIADIC_HEAD arg19(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg19)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                                                     \
  private:                                                                    \
    ::dyno::poly<concept_t> poly_;                                            \
  }



#define DYNO_PP_INTERFACE_IMPL_20(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16, arg17, arg18, arg19, arg20)\
  struct DYNO_PP_CONCAT(dyno_concept_for_, name) {                            \
    static auto make_type() {                                                 \
      return ::dyno::requires_(                                                \
                                        \
                                                           \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg1)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg1>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg2)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg2>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg3)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg3>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg4)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg4>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg5)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg5>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg6)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg6>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg7)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg7>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg8)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg8>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg9)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg9>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg10)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg10>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg11)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg11>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg12)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg12>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg13)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg13>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg14)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg14>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg15)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg15>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg16)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg16>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg17)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg17>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg18)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg18>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg19)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg19>\
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg20)) = ::dyno::method<DYNO_PP_VARIADIC_TAIL arg20>\
                                                                     \
      );                                                                      \
    }                                                                         \
  };                                                                          \
                                                                              \
  class name {                                                                \
    struct concept_t                                                          \
      : decltype(DYNO_PP_CONCAT(dyno_concept_for_, name)::make_type())        \
    { };                                                                      \
  public:                                                                     \
    template <typename T>                                                     \
    name(T&& x)                                                               \
      : poly_{static_cast<T&&>(x), ::dyno::make_concept_map(                  \
                                        \
                                                           \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg1)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg1                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg2)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg2                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg3)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg3                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg4)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg4                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg5)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg5                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg6)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg6                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg7)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg7                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg8)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg8                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg9)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg9                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg10)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg10                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg11)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg11                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg12)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg12                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg13)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg13                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg14)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg14                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg15)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg15                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg16)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg16                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg17)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg17                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg18)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg18                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg19)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg19                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                        \
          ,                                                 \
          DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg20)) = [](auto&& self, auto&& ...args) -> decltype(auto) {\
              return static_cast<decltype(self)&&>(self)                      \
                .DYNO_PP_VARIADIC_HEAD arg20                             \
                  (static_cast<decltype(args)&&>(args)...);                   \
            }                                                                 \
                                                                     \
      )}                                                                      \
    { }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg1>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg1>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg1>\
      DYNO_PP_VARIADIC_HEAD arg1(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg1)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg1>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg1>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg1>\
      DYNO_PP_VARIADIC_HEAD arg1(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg1)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg2>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg2>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg2>\
      DYNO_PP_VARIADIC_HEAD arg2(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg2)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg2>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg2>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg2>\
      DYNO_PP_VARIADIC_HEAD arg2(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg2)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg3>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg3>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg3>\
      DYNO_PP_VARIADIC_HEAD arg3(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg3)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg3>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg3>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg3>\
      DYNO_PP_VARIADIC_HEAD arg3(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg3)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg4>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg4>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg4>\
      DYNO_PP_VARIADIC_HEAD arg4(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg4)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg4>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg4>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg4>\
      DYNO_PP_VARIADIC_HEAD arg4(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg4)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg5>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg5>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg5>\
      DYNO_PP_VARIADIC_HEAD arg5(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg5)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg5>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg5>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg5>\
      DYNO_PP_VARIADIC_HEAD arg5(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg5)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg6>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg6>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg6>\
      DYNO_PP_VARIADIC_HEAD arg6(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg6)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg6>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg6>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg6>\
      DYNO_PP_VARIADIC_HEAD arg6(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg6)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg7>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg7>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg7>\
      DYNO_PP_VARIADIC_HEAD arg7(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg7)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg7>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg7>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg7>\
      DYNO_PP_VARIADIC_HEAD arg7(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg7)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg8>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg8>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg8>\
      DYNO_PP_VARIADIC_HEAD arg8(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg8)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg8>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg8>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg8>\
      DYNO_PP_VARIADIC_HEAD arg8(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg8)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg9>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg9>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg9>\
      DYNO_PP_VARIADIC_HEAD arg9(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg9)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg9>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg9>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg9>\
      DYNO_PP_VARIADIC_HEAD arg9(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg9)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg10>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg10>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg10>\
      DYNO_PP_VARIADIC_HEAD arg10(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg10)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg10>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg10>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg10>\
      DYNO_PP_VARIADIC_HEAD arg10(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg10)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg11>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg11>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg11>\
      DYNO_PP_VARIADIC_HEAD arg11(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg11)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg11>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg11>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg11>\
      DYNO_PP_VARIADIC_HEAD arg11(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg11)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg12>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg12>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg12>\
      DYNO_PP_VARIADIC_HEAD arg12(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg12)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg12>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg12>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg12>\
      DYNO_PP_VARIADIC_HEAD arg12(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg12)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg13>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg13>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg13>\
      DYNO_PP_VARIADIC_HEAD arg13(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg13)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg13>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg13>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg13>\
      DYNO_PP_VARIADIC_HEAD arg13(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg13)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg14>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg14>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg14>\
      DYNO_PP_VARIADIC_HEAD arg14(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg14)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg14>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg14>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg14>\
      DYNO_PP_VARIADIC_HEAD arg14(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg14)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg15>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg15>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg15>\
      DYNO_PP_VARIADIC_HEAD arg15(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg15)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg15>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg15>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg15>\
      DYNO_PP_VARIADIC_HEAD arg15(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg15)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg16>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg16>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg16>\
      DYNO_PP_VARIADIC_HEAD arg16(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg16)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg16>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg16>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg16>\
      DYNO_PP_VARIADIC_HEAD arg16(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg16)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg17>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg17>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg17>\
      DYNO_PP_VARIADIC_HEAD arg17(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg17)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg17>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg17>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg17>\
      DYNO_PP_VARIADIC_HEAD arg17(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg17)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg18>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg18>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg18>\
      DYNO_PP_VARIADIC_HEAD arg18(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg18)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg18>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg18>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg18>\
      DYNO_PP_VARIADIC_HEAD arg18(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg18)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg19>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg19>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg19>\
      DYNO_PP_VARIADIC_HEAD arg19(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg19)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg19>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg19>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg19>\
      DYNO_PP_VARIADIC_HEAD arg19(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg19)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                        \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg20>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        !::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg20>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg20>\
      DYNO_PP_VARIADIC_HEAD arg20(Args&& ...args) {                      \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg20)))(static_cast<Args&&>(args)...);\
      }                                                                       \
      template <typename ...Args, typename = decltype(                        \
        ::std::declval<::boost::callable_traits::function_type_t<DYNO_PP_VARIADIC_TAIL arg20>>()\
          (::std::declval<Args&&>()...)                                       \
      ), typename = ::std::enable_if_t<                                       \
        ::boost::callable_traits::is_const_member<DYNO_PP_VARIADIC_TAIL arg20>::value,\
        char[sizeof...(Args)+1] /* make the enable_if dependent */            \
      >>                                                                      \
      ::boost::callable_traits::return_type_t<DYNO_PP_VARIADIC_TAIL arg20>\
      DYNO_PP_VARIADIC_HEAD arg20(Args&& ...args) const {                \
        return poly_.virtual_(DYNO_STRING(DYNO_PP_STRINGIZE(DYNO_PP_VARIADIC_HEAD arg20)))(static_cast<Args&&>(args)...);\
      }                                                                       \
                                                                     \
  private:                                                                    \
    ::dyno::poly<concept_t> poly_;                                            \
  }



#endif // DYNO_MACRO_HPP
