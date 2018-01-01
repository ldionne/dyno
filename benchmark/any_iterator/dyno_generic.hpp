// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#ifndef BENCHMARK_ANY_ITERATOR_DYNO_GENERIC_HPP
#define BENCHMARK_ANY_ITERATOR_DYNO_GENERIC_HPP

#include <dyno.hpp>


namespace dyno_generic {
  using namespace dyno::literals;

  template <typename Reference>
  struct Iterator : decltype(dyno::requires(
    dyno::MoveConstructible{},
    "increment"_dyno = dyno::function<void (dyno::T&)>,
    "dereference"_dyno = dyno::function<Reference (dyno::T&)>,
    "equal"_dyno = dyno::function<bool (dyno::T const&, dyno::T const&)>
  )) { };

  template <typename Value, typename StoragePolicy, typename VTablePolicy, typename Reference = Value&>
  struct any_iterator {
    using value_type = Value;
    using reference = Reference;

    template <typename It>
    explicit any_iterator(It it)
      : poly_{std::move(it), dyno::make_concept_map(
        "increment"_dyno = [](It& self) { ++self; },
        "dereference"_dyno = [](It& self) -> decltype(auto) { return *self; },
        "equal"_dyno = [](It const& a, It const& b) -> bool { return a == b; }
      )}
    { }

    any_iterator(any_iterator&& other)
      : poly_{std::move(other.poly_)}
    { }

    any_iterator& operator++() {
      poly_.virtual_("increment"_dyno)(poly_);
      return *this;
    }

    reference operator*() {
      return poly_.virtual_("dereference"_dyno)(poly_);
    }

    friend bool operator==(any_iterator const& a, any_iterator const& b) {
      return a.poly_.virtual_("equal"_dyno)(a.poly_, b.poly_);
    }

  private:
    dyno::poly<Iterator<reference>, StoragePolicy, VTablePolicy> poly_;
  };

  using remote_storage = dyno_generic::any_iterator<
    int, dyno::remote_storage, dyno::vtable<dyno::remote<dyno::everything>>
  >;

  using local_storage = dyno_generic::any_iterator<
    int, dyno::local_storage<16>, dyno::vtable<dyno::remote<dyno::everything>>
  >;

  using local_storage_inlined_vtable = dyno_generic::any_iterator<
    int,
    dyno::local_storage<16>,
    dyno::vtable<
      dyno::local<dyno::only<decltype("increment"_dyno),
                             decltype("dereference"_dyno),
                             decltype("equal"_dyno)>>,
      dyno::remote<dyno::everything_else>
    >
  >;
} // end namespace dyno_generic

#endif // BENCHMARK_ANY_ITERATOR_DYNO_GENERIC_HPP
