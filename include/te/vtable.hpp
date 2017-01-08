// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#ifndef TE_VTABLE_HPP
#define TE_VTABLE_HPP

#include <boost/hana/map.hpp>
#include <boost/hana/pair.hpp>
#include <boost/hana/type.hpp>

#include <boost/callable_traits/function_type.hpp>

#include <type_traits>
#include <utility>


namespace te {

namespace detail {
  // Transform a signature from the way it is specified in a concept definition
  // to a type suitable for storage in a vtable.
  template <typename T>
  struct sig_replace {
    static_assert(!std::is_same<T, te::T>{},
      "te::T may not be passed by value in concept definitions; it is only a placeholder");
    using type = T;
  };
  template <typename R, typename ...Args>
  struct sig_replace<R (Args...)> {
    using type = typename sig_replace<R>::type (*)(typename sig_replace<Args>::type...);
  };
  template <>
  struct sig_replace<te::T const&> {
    using type = void const*;
  };
  template <>
  struct sig_replace<te::T &> {
    using type = void*;
  };
  template <>
  struct sig_replace<te::T &&> {
    using type = void*;
  };
  template <>
  struct sig_replace<te::T *> {
    using type = void*;
  };
  template <>
  struct sig_replace<te::T const *> {
    using type = void const*;
  };

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
  template <typename R_pl, typename ...Args_pl,
            typename R_ac, typename ...Args_ac,
            typename Function>
  constexpr auto fun_replace(boost::hana::basic_type<R_pl(Args_pl...)> /*placeholder_sig*/,
                             boost::hana::basic_type<R_ac(Args_ac...)> /*actual_sig*/,
                             Function)
  {
    using Storage = typename sig_replace<R_pl(Args_pl...)>::type;
    auto adapter = [](typename sig_replace<Args_pl>::type ...args)
      -> typename sig_replace<R_pl>::type
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
    using Storage = typename sig_replace<void(Args_pl...)>::type;
    auto adapter = [](typename sig_replace<Args_pl>::type ...args) -> void {
      static_assert(std::is_empty<Function>{},
        "This trick won't work if `Function` is not empty.");
      (*static_cast<Function*>(nullptr))( // <-------------- UB ALERT
        detail::special_cast<Args_pl, Args_ac>(args)...
      );
    };
    return static_cast<Storage>(adapter);
  }
} // end namespace detail

// A `vtable` is a mapping from statically-known function names to
// dynamically-known function pointers. In some sense, a vtable is
// a type-erased `concept_map`.
//
// There are many different ways of implementing a virtual table. The most
// common one, used by the compiler, is to map every function to an index
// and use an array. A polymorphic object then holds a pointer to this array,
// and looks up the actual implementation of a method in that array when it
// gets called.
//
// Another possibility is to use a compile-time map from the names of functions
// to function pointers. This is the only implementation strategy currently
// provided by the library.
template <typename ...Mappings>
struct vtable;

template <typename ...Name, typename ...Signature>
struct vtable<boost::hana::pair<Name, boost::hana::basic_type<Signature>>...> {
  template <typename ConceptMap>
  constexpr explicit vtable(ConceptMap map)
    : vtbl_{boost::hana::make_map(
      boost::hana::make_pair(
        Name{},
        detail::fun_replace(
          boost::hana::basic_type<Signature>{},
          boost::hana::basic_type<
            boost::callable_traits::function_type_t<
              std::decay_t<decltype(map[Name{}])>
            >
          >{},
          map[Name{}]
        )
      )...
    )}
  { }

  template <typename Name_>
  constexpr auto operator[](Name_ name) const {
    return vtbl_[name];
  }

private:
  boost::hana::map<
    boost::hana::pair<Name, typename detail::sig_replace<Signature>::type>...
  > vtbl_;
};

} // end namespace te

#endif // TE_VTABLE_HPP
