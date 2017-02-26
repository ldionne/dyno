// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#ifndef TE_POLY_HPP
#define TE_POLY_HPP

#include <te/builtin.hpp>
#include <te/concept_map.hpp>
#include <te/storage.hpp>
#include <te/vtable.hpp>

#include <type_traits>
#include <utility>


namespace te {

// A `te::poly` encapsulates an object of a polymorphic type that supports the
// interface of the given `Concept`.
//
// `te::poly` is meant to be used as a holder for a polymorphic object. It can
// manage the lifetime of that object and provide access to its dynamically-
// dispatched methods. However, it does not directly implement any specific
// interface beyond what's strictly necessary for managing the lifetime
// (constructor, destructor, assignment, swap, etc..). Instead, it provides
// a `virtual_` method that gives access to dynamically-dispatched methods of
// the object it manages.
//
// The intended use case is for users to create their very own type-erased
// wrappers on top of `te::poly`, defining their interface as they wish and
// using the dynamic dispatch provided by the library to implement runtime
// polymorphism.
//
// Different aspects of a `te::poly` can also be customized:
//  `Concept`
//    The concept satisfied by `te::poly`. This determines which methods will
//    be available for dynamic dispatching.
//
//  `Storage`
//    The type used to provide the storage for the managed object. This must
//    be a model of the `PolymorphicStorage` concept.
//
//  `VTable`
//    The type used to provide the dynamic dispatching mechanism for methods.
//    This must be a model of the `VTable` concept.
//
// TODO:
// - How to combine the storage of the object with that of the vtable?
//   For example, how would we allow storing the vtable inside the rest
//   of the storage?
// - Is it actually OK to require Destructible all the time?
template <
  typename Concept,
  typename Storage = te::remote_storage,
  typename VTable = te::remote_vtable<te::local_vtable<
    decltype(te::requires(Concept{}, te::Destructible{}))
  >>
>
struct poly {
private:
  using ActualConcept = decltype(te::requires(
    Concept{},
    te::Destructible{}
  ));

public:
  template <typename T, typename RawT = std::decay_t<T>, typename ConceptMap>
  explicit poly(T&& t, ConceptMap map)
    : vtable_{te::complete_concept_map<ActualConcept, RawT>(map)}
    , storage_{std::forward<T>(t)}
  { }

  template <typename T, typename RawT = std::decay_t<T>>
  explicit poly(T&& t)
    : poly{std::forward<T>(t), te::concept_map<ActualConcept, RawT>}
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

  template <typename Function>
  constexpr decltype(auto) virtual_(Function name) const {
    return vtable_[name];
  }

  constexpr auto get() { return storage_.get(); }
  constexpr auto get() const { return storage_.get(); }

private:
  VTable vtable_;
  Storage storage_;
};

} // end namespace te

#endif // TE_POLY_HPP
