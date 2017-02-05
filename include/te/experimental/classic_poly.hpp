// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#ifndef TE_EXPERIMENTAL_CLASSIC_POLY_HPP
#define TE_EXPERIMENTAL_CLASSIC_POLY_HPP

#include <te/concept_map.hpp>
#include <te/storage.hpp>
#include <te/vtable.hpp>

#include <type_traits>
#include <utility>


namespace te { namespace experimental {

template <typename Concept>
struct concept_t {

};

template <typename Concept, typename T>
struct model_t : concept_t<Concept> {
  T self_;


};


template <typename Concept>
struct classic_poly {
  template <typename T, typename RawT = std::decay_t<T>>
  explicit classic_poly(T&& t)
    : self_{new model_t<RawT>{std::forward<T>(t)}}
  { }

  classic_poly(classic_poly const& other)
    : vtable_{other.vtable_}
    , storage_{other.storage_, vtable_}
  { }

  classic_poly(classic_poly&& other)
    : vtable_{std::move(other.vtable_)}
    , storage_{std::move(other.storage_), vtable_}
  { }

  classic_poly& operator=(classic_poly const& other) {
    classic_poly(other).swap(*this);
    return *this;
  }

  classic_poly& operator=(classic_poly&& other) {
    classic_poly(std::move(other)).swap(*this);
    return *this;
  }

  void swap(classic_poly& other) {
    storage_.swap(vtable_, other.storage_, other.vtable_);
    using std::swap;
    swap(vtable_, other.vtable_);
  }

  friend void swap(classic_poly& a, classic_poly& b) { a.swap(b); }

  ~classic_poly() { storage_.destruct(vtable_); }

  template <typename Function>
  constexpr decltype(auto) virtual_(Function name) const {
    return vtable_[name];
  }

  constexpr auto get() { return storage_.get(); }
  constexpr auto get() const { return storage_.get(); }

private:
  using concept_t = te::unpack_vtable_layout<Concept, detail::vtable_base>;

  template <typename T>
  struct model_t final : concept_t {

    T t_;
  };

  concept_t* self_;
};

}} // end namespace te::experimental

#endif // TE_EXPERIMENTAL_CLASSIC_POLY_HPP
