// Copyright Louis Dionne 2016
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#ifndef ANY_ITERATOR_HPP
#define ANY_ITERATOR_HPP

#include <te.hpp>

#include <boost/hana/core/when.hpp>
#include <boost/hana/map.hpp>
#include <boost/hana/pair.hpp>
#include <boost/hana/string.hpp>
#include <boost/hana/type.hpp>

#include <cassert>
#include <iterator>
#include <type_traits>
#include <utility>
namespace hana = boost::hana;
using namespace te::literals;


// This is the definition of an Iterator concept using a "generic" language.
// Instead of defining specific methods that must be defined, it defines its
// interface in terms of compile-time strings, assuming these may be fulfilled
// in possibly many different ways.
template <
  typename Value,
  typename Category,
  typename Reference
>
using iterator_vtable = decltype(te::make_vtable(
  "increment"_s       = te::function<void (te::T&)>,
  "dereference"_s     = te::function<Reference (te::T&)>,
  "equal"_s           = te::function<bool (te::T const&, te::T const&)>,

  "type_info"_s       = te::function<te::type_info ()>,
  "copy-construct"_s  = te::function<void (void*, te::T const&)>,
  "move-construct"_s  = te::function<void (void*, te::T&&)>,
  "destruct"_s        = te::function<void (te::T&)>
));

template <typename T> struct not_defined;
template <typename T, typename = hana::when<true>> not_defined<T> iterator_vtable_for;

template <typename T, typename Value, typename Category, typename Reference>
iterator_vtable<Value, Category, Reference> const erased_iterator_vtable_for{iterator_vtable_for<T>};


// This is some kind of concept map; it maps the "generic" iterator interface
// (method names as compile-time strings) to actual implementations for a
// specific iterator type.
template <typename T>
auto const iterator_vtable_for<T, hana::when<
  std::is_base_of<std::random_access_iterator_tag,
                  typename std::iterator_traits<T>::iterator_category>{}
>> = te::make_vtable(
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
struct any_iterator
  : te::swappable<any_iterator<Value, Category, Reference>>
  , te::destructible<any_iterator<Value, Category, Reference>>
{
  using iterator_category = Category;
  using value_type = Value;
  using reference = Reference;
  using pointer = value_type*;

  template <typename Iterator>
  explicit any_iterator(Iterator it)
    : vtable_{&erased_iterator_vtable_for<Iterator, Value, Category, Reference>}
    , storage_{te::type_info_for<Iterator>}
  {
    new (storage()) Iterator(std::move(it));

    using IteratorTraits = std::iterator_traits<Iterator>;
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

  friend bool operator==(any_iterator const& a, any_iterator const& b) {
    assert(a.virtual_("equal"_s) == b.virtual_("equal"_s));
    return a.virtual_("equal"_s)(a.storage(), b.storage());
  }

  friend bool operator!=(any_iterator const& a, any_iterator const& b) {
    return !(a == b);
  }

private:
  iterator_vtable<value_type, iterator_category, reference> const* vtable_;
  te::local_storage<8> storage_;

public: // TODO: Find a way not to make this public
  template <typename Method>
  constexpr decltype(auto) virtual_(Method m) const {
    return (*vtable_)[m];
  }

  auto storage() { return storage_.get(); }
  auto storage() const { return storage_.get(); }
};

#endif // ANY_ITERATOR_HPP
