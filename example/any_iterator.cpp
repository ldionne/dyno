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
#include <iterator>
#include <type_traits>
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
    : vtable_{iterator_vtable_for<Iterator>}, storage_{it}
  {
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
  {
    std::vector<int> v{1, 2, 3, 4};
    any_iterator<int, std::random_access_iterator_tag> first{v.begin()}, last{v.end()};

    std::vector<int> result;
    for (; first != last; ++first) {
      result.push_back(*first);
    }
    assert(result == v);
  }

  {
    std::array<int, 4> a{{1, 2, 3, 4}};
    std::array<int, 4> result;
    using Iterator = any_iterator<int, std::random_access_iterator_tag>;
    Iterator first{a.begin()}, last{a.end()}, out{result.begin()};

    for (; first != last; ++first, ++out) {
      *out = *first;
    }
    assert(result == a);
  }
}
