// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#ifndef BENCHMARK_ANY_ITERATOR_DYNO_GENERIC_HPP
#define BENCHMARK_ANY_ITERATOR_DYNO_GENERIC_HPP

#include <dyno.hpp>


namespace dyno_generic {
  using namespace dyno::literals;

  template <typename Reference>
  struct Iterator : decltype(dyno::requires_(
    dyno::MoveConstructible{},
    "increment"_s = dyno::function<void (dyno::T&)>,
    "dereference"_s = dyno::function<Reference (dyno::T&)>,
    "equal"_s = dyno::function<bool (dyno::T const&, dyno::T const&)>
  )) { };

  template <typename Value, typename StoragePolicy, typename VTablePolicy, typename Reference = Value&>
  struct any_iterator {
    using value_type = Value;
    using reference = Reference;

    template <typename It>
    explicit any_iterator(It it)
      : poly_{std::move(it), dyno::make_concept_map(
        "increment"_s = [](It& self) { ++self; },
        "dereference"_s = [](It& self) -> decltype(auto) { return *self; },
        "equal"_s = [](It const& a, It const& b) -> bool { return a == b; }
      )}
    { }

    any_iterator(any_iterator&& other)
      : poly_{std::move(other.poly_)}
    { }

    any_iterator& operator++() {
      poly_.virtual_("increment"_s)(poly_);
      return *this;
    }

    reference operator*() {
      return poly_.virtual_("dereference"_s)(poly_);
    }

    friend bool operator==(any_iterator const& a, any_iterator const& b) {
      return a.poly_.virtual_("equal"_s)(a.poly_, b.poly_);
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
      dyno::local<dyno::only<decltype("increment"_s),
                             decltype("dereference"_s),
                             decltype("equal"_s)>>,
      dyno::remote<dyno::everything_else>
    >
  >;
} // end namespace dyno_generic

#endif // BENCHMARK_ANY_ITERATOR_DYNO_GENERIC_HPP
