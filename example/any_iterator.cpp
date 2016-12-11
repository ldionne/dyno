// Copyright Louis Dionne 2016
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <te.hpp>

#include <boost/hana/core/when.hpp>
#include <boost/hana/map.hpp>
#include <boost/hana/pair.hpp>
#include <boost/hana/string.hpp>
#include <boost/hana/type.hpp>

#include <array>
#include <cassert>
#include <cstddef>
#include <iterator>
#include <type_traits>
#include <utility>
#include <vector>
namespace hana = boost::hana;
using namespace hana::literals;


// This is the definition of an Iterator concept using a "generic" language.
// Instead of defining specific methods that must be defined, it defines its
// interface in terms of compile-time strings, assuming these may be fulfilled
// in possibly many different ways.
template <
  typename Value,
  typename Category,
  typename Reference
>
using iterator_vtable = te::vtable<
  decltype(hana::make_pair("increment"_s, hana::type_c<void (void*)>)),
  decltype(hana::make_pair("dereference"_s, hana::type_c<Reference (void*)>)),
  decltype(hana::make_pair("operator=="_s, hana::type_c<bool (void const*, void const*)>)),

  decltype(hana::make_pair("type_info"_s, hana::type_c<te::type_info ()>)),
  decltype(hana::make_pair("copy-construct"_s, hana::type_c<void (void*, void const*)>)),
  decltype(hana::make_pair("move-construct"_s, hana::type_c<void (void*, void*)>)),
  decltype(hana::make_pair("destruct"_s, hana::type_c<void (void*)>))
>;


template <typename T> struct not_defined;
template <typename T, typename = hana::when<true>> not_defined<T> iterator_vtable_for;

// This is some kind of concept map; it maps the "generic" iterator interface
// (method names as compile-time strings) to actual implementations for a
// specific iterator type.
template <typename T>
auto iterator_vtable_for<T, hana::when<
  std::is_base_of<std::random_access_iterator_tag,
                  typename std::iterator_traits<T>::iterator_category>{}
>> = hana::make_map(
  hana::make_pair("increment"_s, [](void* this_) {
    ++*static_cast<T*>(this_);
  }),

  hana::make_pair("dereference"_s, [](void* this_) -> decltype(auto) {
    return (**static_cast<T*>(this_));
  }),

  hana::make_pair("operator=="_s, [](void const* a, void const* b) {
    return *static_cast<T const*>(a) == *static_cast<T const*>(b);
  }),

  hana::make_pair("type_info"_s, [] {
    return te::type_info_for<T>;
  }),

  hana::make_pair("copy-construct"_s, [](void* this_, void const* other) {
    new (this_) T(*static_cast<T const*>(other));
  }),

  hana::make_pair("move-construct"_s, [](void* this_, void* other) {
    new (this_) T(std::move(*static_cast<T*>(other)));
  }),

  hana::make_pair("destruct"_s, [](void* this_) {
    static_cast<T*>(this_)->~T();
  })
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
struct any_iterator {
  using iterator_category = Category;
  using value_type = Value;
  using reference = Reference;
  using pointer = value_type*;

  template <typename Iterator>
  explicit any_iterator(Iterator it)
    : vtable_{iterator_vtable_for<Iterator>}
    , storage_{te::type_info_for<Iterator>}
  {
    new (storage_.get()) Iterator(std::move(it));

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
    , storage_{vtable_["type_info"_s]()}
  {
    vtable_["copy-construct"_s](storage_.get(), other.storage_.get());
  }

  // TODO: Here, we could avoid allocating and just move the pointer inside
  // the storage.
  any_iterator(any_iterator&& other)
    : vtable_{std::move(other.vtable_)}
    , storage_{vtable_["type_info"_s]()}
  {
    vtable_["move-construct"_s](storage_.get(), other.storage_.get());
  }

  any_iterator& operator=(any_iterator const& other) {
    any_iterator(other).swap(*this);
    return *this;
  }

  any_iterator& operator=(any_iterator&& other) {
    any_iterator(std::move(other)).swap(*this);
    return *this;
  }

  // TODO: That is NOT a proper implementation of swap!
  void swap(any_iterator& other) {
    any_iterator tmp(std::move(other));

    other.~any_iterator();
    new (&other) any_iterator(std::move(*this));

    this->~any_iterator();
    new (this) any_iterator(std::move(tmp));
  }

  any_iterator& operator++() {
    vtable_["increment"_s](storage_.get());
    return *this;
  }

  reference operator*() {
    return vtable_["dereference"_s](storage_.get());
  }

  ~any_iterator() {
    vtable_["destruct"_s](storage_.get());
  }

  friend bool operator==(any_iterator const& a, any_iterator const& b) {
    assert(a.vtable_["operator=="_s] == b.vtable_["operator=="_s]);
    return a.vtable_["operator=="_s](a.storage_.get(), b.storage_.get());
  }

  friend bool operator!=(any_iterator const& a, any_iterator const& b) {
    return !(a == b);
  }

private:
  iterator_vtable<value_type, iterator_category, reference> vtable_;
  te::small_buffer<8> storage_;
};


int main() {
  ////////////////////////////////////////////////////////////////////////////
  // Iteration
  ////////////////////////////////////////////////////////////////////////////
  {
    using Iterator = any_iterator<int, std::random_access_iterator_tag>;
    std::vector<int> input{1, 2, 3, 4};
    std::vector<int> result;

    Iterator first{input.begin()}, last{input.end()};
    for (; first != last; ++first) {
      result.push_back(*first);
    }
    assert(result == input);
  }

  {
    using Iterator = any_iterator<int, std::random_access_iterator_tag>;
    std::array<int, 4> input{{1, 2, 3, 4}};
    std::array<int, 4> result;
    Iterator first{input.begin()}, last{input.end()}, out{result.begin()};

    for (; first != last; ++first, ++out) {
      *out = *first;
    }
    assert(result == input);
  }

  ////////////////////////////////////////////////////////////////////////////
  // Copy-construction
  ////////////////////////////////////////////////////////////////////////////
  {
    using Iterator = any_iterator<int, std::random_access_iterator_tag>;
    std::vector<int> input{1, 2, 3, 4};
    Iterator first{input.begin()}, last{input.end()};
    Iterator cfirst(first), clast(last);
    assert(first == cfirst);
    assert(last == clast);
  }

  ////////////////////////////////////////////////////////////////////////////
  // Move-construction
  ////////////////////////////////////////////////////////////////////////////
  {
    using Iterator = any_iterator<int, std::random_access_iterator_tag>;
    std::vector<int> input{1, 2, 3, 4};
    std::vector<int> result;

    Iterator first{input.begin()}, last{input.end()};
    Iterator cfirst(std::move(first)), clast(std::move(last));
    for (; cfirst != clast; ++cfirst) {
      result.push_back(*cfirst);
    }
    assert(result == input);
  }

  ////////////////////////////////////////////////////////////////////////////
  // Copy-assignment
  ////////////////////////////////////////////////////////////////////////////
  {
    using Iterator = any_iterator<int, std::random_access_iterator_tag>;
    std::vector<int> input{1, 2, 3, 4};
    Iterator first{input.begin()}, mid{input.begin() + 2};
    assert(*first == 1);
    first = mid;
    assert(*first == 3);
  }

  ////////////////////////////////////////////////////////////////////////////
  // Move-assignment
  ////////////////////////////////////////////////////////////////////////////
  {
    using Iterator = any_iterator<int, std::random_access_iterator_tag>;
    std::vector<int> input{1, 2, 3, 4};
    Iterator first{input.begin()}, mid{input.begin() + 2};
    assert(*first == 1);
    first = std::move(mid);
    assert(*first == 3);
  }
}
