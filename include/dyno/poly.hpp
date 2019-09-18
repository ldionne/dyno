// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#ifndef DYNO_POLY_HPP
#define DYNO_POLY_HPP

#include <dyno/builtin.hpp>
#include <dyno/concept.hpp>
#include <dyno/concept_map.hpp>
#include <dyno/detail/is_placeholder.hpp>
#include <dyno/storage.hpp>
#include <dyno/vtable.hpp>

#include <boost/hana/contains.hpp>
#include <boost/hana/core/to.hpp>
#include <boost/hana/map.hpp>
#include <boost/hana/unpack.hpp>

#include <type_traits>
#include <utility>


namespace dyno {

// A `dyno::poly` encapsulates an object of a polymorphic type that supports the
// interface of the given `Concept`.
//
// `dyno::poly` is meant to be used as a holder for a polymorphic object. It can
// manage the lifetime of that object and provide access to its dynamically-
// dispatched methods. However, it does not directly implement any specific
// interface beyond what's strictly necessary for managing the lifetime
// (constructor, destructor, assignment, swap, etc..). Instead, it provides
// a `virtual_` method that gives access to dynamically-dispatched methods of
// the object it manages.
//
// The intended use case is for users to create their very own type-erased
// wrappers on top of `dyno::poly`, defining their interface as they wish and
// using the dynamic dispatch provided by the library to implement runtime
// polymorphism.
//
// Different aspects of a `dyno::poly` can also be customized:
//  `Concept`
//    The concept satisfied by `dyno::poly`. This determines which methods will
//    be available for dynamic dispatching.
//
//  `Storage`
//    The type used to provide the storage for the managed object. This must
//    be a model of the `PolymorphicStorage` concept.
//
//  `VTable`
//    The policy specifying how to implement the dynamic dispatching mechanism
//    for methods. This must be a specialization of `dyno::vtable`.
//    See `dyno::vtable` for details.
//
// TODO:
// - How to combine the storage of the object with that of the vtable?
//   For example, how would we allow storing the vtable inside the rest
//   of the storage?
// - Is it actually OK to require Destructible and Storable all the time?
// - Test that we can't call e.g. a non-const method on a const poly.
template <
  typename Concept,
  typename Storage = dyno::remote_storage,
  typename VTablePolicy = dyno::vtable<dyno::remote<dyno::everything>>
>
struct poly {
private:
  using ActualConcept = decltype(dyno::requires_(
    Concept{},
    dyno::Destructible{},
    dyno::Storable{}
  ));
  using VTable = typename VTablePolicy::template apply<ActualConcept>;

public:
  template <typename T, typename RawT = std::decay_t<T>, typename ConceptMap>
  poly(T&& t, ConceptMap map)
    : vtable_{dyno::complete_concept_map<ActualConcept, RawT>(map)}
    , storage_{std::forward<T>(t)}
  { }

  template <typename T, typename RawT = std::decay_t<T>,
    typename = std::enable_if_t<!std::is_same<RawT, poly>::value>,
    typename = std::enable_if_t<dyno::models<ActualConcept, RawT>>
  >
  poly(T&& t)
    : poly{std::forward<T>(t), dyno::concept_map<ActualConcept, RawT>}
  { }

  poly(poly const& other)
    : vtable_{other.vtable_}
    , storage_{other.storage_, vtable_}
  { }

  poly(poly&& other)
    : vtable_{std::move(other.vtable_)}
    , storage_{std::move(other.storage_), vtable_}
  { }

  poly& operator=(poly const& other) {
    poly(other).swap(*this);
    return *this;
  }

  poly& operator=(poly&& other) {
    poly(std::move(other)).swap(*this);
    return *this;
  }

  void swap(poly& other) {
    storage_.swap(vtable_, other.storage_, other.vtable_);
    using std::swap;
    swap(vtable_, other.vtable_);
  }

  friend void swap(poly& a, poly& b) { a.swap(b); }

  ~poly() { storage_.destruct(vtable_); }

  template <typename ...T, typename Name, typename ...Args>
  decltype(auto) operator->*(dyno::detail::delayed_call<Name, Args...>&& delayed) {
    auto f = virtual_(Name{});
    auto injected = [f, this](auto&& ...args) -> decltype(auto) {
      return f(*this, static_cast<decltype(args)&&>(args)...);
    };
    return boost::hana::unpack(std::move(delayed.args), injected);
  }

  template <typename ...T, typename Name, typename ...Args>
  decltype(auto) operator->*(dyno::detail::delayed_call<Name, Args...>&& delayed) const {
    auto f = virtual_(Name{});
    auto injected = [f, this](auto&& ...args) -> decltype(auto) {
      return f(*this, static_cast<decltype(args)&&>(args)...);
    };
    return boost::hana::unpack(std::move(delayed.args), injected);
  }

  template <typename Function,
    bool HasClause = decltype(boost::hana::contains(dyno::clause_names(Concept{}), Function{})){},
    std::enable_if_t<HasClause>* = nullptr
  >
  constexpr decltype(auto) virtual_(Function name) const& {
    auto clauses = boost::hana::to_map(dyno::clauses(Concept{}));
    return virtual_impl(clauses[name], name);
  }
  template <typename Function,
    bool HasClause = decltype(boost::hana::contains(dyno::clause_names(Concept{}), Function{})){},
    std::enable_if_t<HasClause>* = nullptr
  >
  constexpr decltype(auto) virtual_(Function name) & {
    auto clauses = boost::hana::to_map(dyno::clauses(Concept{}));
    return virtual_impl(clauses[name], name);
  }
  template <typename Function,
    bool HasClause = decltype(boost::hana::contains(dyno::clause_names(Concept{}), Function{})){},
    std::enable_if_t<HasClause>* = nullptr
  >
  constexpr decltype(auto) virtual_(Function name) && {
    auto clauses = boost::hana::to_map(dyno::clauses(Concept{}));
    return std::move(*this).virtual_impl(clauses[name], name);
  }

  template <typename Function,
    bool HasClause = decltype(boost::hana::contains(dyno::clause_names(Concept{}), Function{})){},
    std::enable_if_t<!HasClause>* = nullptr
  >
  constexpr decltype(auto) virtual_(Function) const {
    static_assert(HasClause, "dyno::poly::virtual_: Trying to access a function "
                             "that is not part of the Concept");
  }

  // Returns a pointer to the underlying storage.
  //
  // The pointer is potentially invalidated whenever the poly is modified;
  // the specific storage policy should be consulted to know when pointers
  // to the underlying storage are invalidated.
  //
  // The behavior is undefined if the requested type is not cv-qualified `void`
  // and the underlying storage is not of the requested type.
  template <typename T>
  T* unsafe_get() { return storage_.template get<T>(); }

  template <typename T>
  T const* unsafe_get() const { return storage_.template get<T>(); }

private:
  VTable vtable_;
  Storage storage_;

  // Handle dyno::function
  template <typename R, typename ...T, typename Function>
  constexpr decltype(auto) virtual_impl(dyno::function_t<R(T...)>, Function name) const {
    auto fptr = vtable_[name];
    return [fptr](auto&& ...args) -> decltype(auto) {
      return fptr(poly::unerase_poly<T>(static_cast<decltype(args)&&>(args))...);
    };
  }

  // Handle dyno::method
  template <typename R, typename ...T, typename Function>
  constexpr decltype(auto) virtual_impl(dyno::method_t<R(T...)>, Function name) & {
    auto fptr = vtable_[name];
    return [fptr, this](auto&& ...args) -> decltype(auto) {
      return fptr(poly::unerase_poly<dyno::T&>(*this),
                  poly::unerase_poly<T>(static_cast<decltype(args)&&>(args))...);
    };
  }
  template <typename R, typename ...T, typename Function>
  constexpr decltype(auto) virtual_impl(dyno::method_t<R(T...)&>, Function name) & {
    auto fptr = vtable_[name];
    return [fptr, this](auto&& ...args) -> decltype(auto) {
      return fptr(poly::unerase_poly<dyno::T&>(*this),
                  poly::unerase_poly<T>(static_cast<decltype(args)&&>(args))...);
    };
  }
  template <typename R, typename ...T, typename Function>
  constexpr decltype(auto) virtual_impl(dyno::method_t<R(T...)&&>, Function name) && {
    auto fptr = vtable_[name];
    return [fptr, this](auto&& ...args) -> decltype(auto) {
      return fptr(poly::unerase_poly<dyno::T&&>(*this),
                  poly::unerase_poly<T>(static_cast<decltype(args)&&>(args))...);
    };
  }
  template <typename R, typename ...T, typename Function>
  constexpr decltype(auto) virtual_impl(dyno::method_t<R(T...) const>, Function name) const {
    auto fptr = vtable_[name];
    return [fptr, this](auto&& ...args) -> decltype(auto) {
      return fptr(poly::unerase_poly<dyno::T const&>(*this),
                  poly::unerase_poly<T>(static_cast<decltype(args)&&>(args))...);
    };
  }
  template <typename R, typename ...T, typename Function>
  constexpr decltype(auto) virtual_impl(dyno::method_t<R(T...) const&>, Function name) const {
    auto fptr = vtable_[name];
    return [fptr, this](auto&& ...args) -> decltype(auto) {
      return fptr(poly::unerase_poly<dyno::T const&>(*this),
                  poly::unerase_poly<T>(static_cast<decltype(args)&&>(args))...);
    };
  }

  // unerase_poly helper
  template <typename T, typename Arg, std::enable_if_t<!detail::is_placeholder<T>::value, int> = 0>
  static constexpr decltype(auto) unerase_poly(Arg&& arg)
  { return static_cast<Arg&&>(arg); }

  template <typename T, typename Arg, std::enable_if_t<detail::is_placeholder<T>::value, int> = 0>
  static constexpr decltype(auto) unerase_poly(Arg&& arg) {
    using RawArg = std::remove_cv_t<std::remove_reference_t<Arg>>;
    constexpr bool is_poly = std::is_same<poly, RawArg>::value;
    static_assert(is_poly,
      "dyno::poly::virtual_: Passing a non-poly object as an argument to a virtual "
      "function that specified a placeholder for that parameter.");
    return static_cast<Arg&&>(arg).storage_.get();
  }
  template <typename T, typename Arg, std::enable_if_t<detail::is_placeholder<T>::value, int> = 0>
  static constexpr decltype(auto) unerase_poly(Arg* arg) {
    using RawArg = std::remove_cv_t<Arg>;
    constexpr bool is_poly = std::is_same<poly, RawArg>::value;
    static_assert(is_poly,
      "dyno::poly::virtual_: Passing a non-poly object as an argument to a virtual "
      "function that specified a placeholder for that parameter.");
    return arg->storage_.get();
  }
};

} // end namespace dyno

#endif // DYNO_POLY_HPP
