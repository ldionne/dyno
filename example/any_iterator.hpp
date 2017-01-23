// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#ifndef ANY_ITERATOR_HPP
#define ANY_ITERATOR_HPP

#include <te.hpp>

#include <cassert>
#include <iterator>
#include <type_traits>
#include <utility>
using namespace te::literals;


struct Storable : decltype(te::requires(
  "type_info"_s = te::function<te::type_info()>
)) { };

struct CopyConstructible : decltype(te::requires(
  Storable{},
  te::MoveConstructible{},
  "copy-construct"_s = te::function<void (void*, te::T const&)>
)) { };

struct MoveAssignable : decltype(te::requires(
  // No virtual function required to support this
)) { };

struct CopyAssignable : decltype(te::requires(
  MoveAssignable{}
  // No virtual function required to support this
)) { };

struct Swappable : decltype(te::requires(
  // No virtual function required to support this so far
)) { };

// This is the definition of an Iterator concept using a "generic" language.
// Instead of defining specific methods that must be defined, it defines its
// interface in terms of compile-time strings, assuming these may be fulfilled
// in possibly many different ways.
template <typename Reference>
struct Iterator : decltype(te::requires(
  CopyConstructible{},
  CopyAssignable{},
  te::Destructible{},
  te::EqualityComparable{},
  Swappable{},
  "increment"_s = te::function<void (te::T&)>,
  "dereference"_s = te::function<Reference (te::T&)>
)) { };

// This is some kind of concept map; it maps the "generic" iterator interface
// (method names as compile-time strings) to actual implementations for a
// specific iterator type.
template <typename T>
auto const te::concept_map<
  Iterator<typename std::iterator_traits<T>::reference>,
  T,
  std::enable_if_t<
    std::is_base_of<std::random_access_iterator_tag,
                    typename std::iterator_traits<T>::iterator_category>{}
  >
> = te::make_concept_map<
  Iterator<typename std::iterator_traits<T>::reference>
>(
  "increment"_s = [](T& self) {
    ++self;
  },

  "dereference"_s = [](T& self) -> decltype(auto) {
    return *self;
  },

  "equal"_s = [](T const& a, T const& b) {
    return a == b;
  },

  "type_info"_s = []() {
    return te::type_info_for<T>;
  },

  "copy-construct"_s = [](void* p, T const& other) {
    new (p) T(other);
  },

  "move-construct"_s = [](void* p, T&& other) {
    new (p) T(std::move(other));
  },

  "destruct"_s = [](T& self) {
    self.~T();
  }
);

template <typename Concept, typename T>
te::vtable<Concept> const vtable{te::concept_map<Concept, T>};

// This defines a type-erased wrapper satisfying a specific concept (Iterator)
// and providing the given interface (methods, etc..). The choice of how to
// store the type-erased object and how to implement the VTable should be done
// here, and should be disjoint from the actual concept definition and concept
// map above.
template <
  typename Value,
  typename Category,
  typename Reference = Value&
>
struct any_iterator {
  using iterator_category = Category;
  using value_type = Value;
  using reference = Reference;
  using pointer = value_type*;

  template <typename It>
  explicit any_iterator(It it)
    : vtable_{&vtable<Iterator<reference>, It>}
    , storage_{te::type_info_for<It>}
  {
    new (storage()) It(std::move(it));

    using IteratorTraits = std::iterator_traits<It>;
    using Source_value_type = typename IteratorTraits::value_type;
    using Source_reference = typename IteratorTraits::reference;
    using Source_category = typename IteratorTraits::iterator_category;

    static_assert(std::is_convertible<Source_value_type, value_type>{},
      "The 'value_type' of the erased iterator must be convertible to that of "
      "the 'any_iterator'");

    static_assert(std::is_convertible<Source_reference, reference>{},
      "The 'reference' of the erased iterator must be convertible to that of "
      "the 'any_iterator'");

    static_assert(std::is_base_of<iterator_category, Source_category>{},
      "The 'iterator_category' of the erased iterator must be at least as "
      "powerful as that of the 'any_iterator'");
  }

  any_iterator(any_iterator const& other)
    : vtable_{other.vtable_}
    , storage_{virtual_("type_info"_s)()}
  {
    virtual_("copy-construct"_s)(storage(), other.storage());
  }

  // TODO: Here, we could avoid allocating and just move the pointer inside
  // the storage.
  any_iterator(any_iterator&& other)
    : vtable_{std::move(other.vtable_)}
    , storage_{virtual_("type_info"_s)()}
  {
    virtual_("move-construct"_s)(storage(), other.storage());
  }

  any_iterator& operator=(any_iterator const& other) {
    any_iterator(other).swap(*this);
    return *this;
  }

  any_iterator& operator=(any_iterator&& other) {
    any_iterator(std::move(other)).swap(*this);
    return *this;
  }

  any_iterator& operator++() {
    virtual_("increment"_s)(storage());
    return *this;
  }

  reference operator*() {
    return virtual_("dereference"_s)(storage());
  }


  ////////////////////////////////////////////////////////////////////////////
  // BOILERPLATE THAT WE COULD PROBABLY SHARE SOMEWHERE
  ////////////////////////////////////////////////////////////////////////////

  // TODO: That is NOT a proper implementation of swap!
  void swap(any_iterator& other) {
    any_iterator tmp(std::move(other));

    other.~any_iterator();
    new (&other) any_iterator(std::move(*this));

    this->~any_iterator();
    new (this) any_iterator(std::move(tmp));
  }

  friend bool operator==(any_iterator const& a, any_iterator const& b) {
    assert(a.virtual_("equal"_s) == b.virtual_("equal"_s));
    return a.virtual_("equal"_s)(a.storage(), b.storage());
  }

  friend bool operator!=(any_iterator const& a, any_iterator const& b) {
    return !(a == b);
  }

  ~any_iterator() {
    virtual_("destruct"_s)(storage());
  }

private:
  te::vtable<Iterator<reference>> const* vtable_;
  te::local_storage<8> storage_;

  template <typename Method>
  constexpr decltype(auto) virtual_(Method m) const {
    return (*vtable_)[m];
  }

  auto storage() { return storage_.get(); }
  auto storage() const { return storage_.get(); }
};

#endif // ANY_ITERATOR_HPP
