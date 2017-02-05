// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#ifndef TE_EXPERIMENTAL_COLLOCATED_POLY_HPP
#define TE_EXPERIMENTAL_COLLOCATED_POLY_HPP

#include <te/concept_map.hpp>
#include <te/storage.hpp>
#include <te/vtable.hpp>

#include <cstddef>
#include <type_traits>
#include <utility>


namespace te { namespace experimental {

template <
  typename Concept,
  typename Storage = te::remote_storage,
  typename VTable = te::remote_vtable<te::local_vtable<Concept>>
>
class collocated_poly {
  template <typename T>
  struct collocated_storage {
    template <typename ConceptMap, typename U>
    constexpr collocated_storage(ConceptMap map, U&& u)
      : vtable{map}, object{std::forward<U>(u)}
    { }

    VTable vtable;
    // TODO: This is potentially very wasteful. For example, when type-erasing
    //       a `char`, a ton of space will be wasted. This is the only way I
    //       could find of implementing this. Or we could also extract the
    //       exact alignment of the type from the vtable and save on size,
    //       but that would be more costly each time we extract the object.
    alignas(std::max_align_t) T object;
  };

  VTable const& get_vtable() const {
    return *static_cast<VTable const*>(storage_.get());
  }

  Storage storage_;

public:
  template <typename Function>
  constexpr decltype(auto) virtual_(Function name) const {
    return get_vtable()[name];
  }

  template <typename T = void>
  T const* get() const {
    void const* base = storage_.get();
    constexpr auto offset = offsetof(collocated_storage<std::max_align_t>, object);
    void const* object = static_cast<char const*>(base) + offset;
    return static_cast<T const*>(object);
  }

  template <typename T = void>
  T* get() {
    void* base = storage_.get();
    constexpr auto offset = offsetof(collocated_storage<std::max_align_t>, object);
    void* object = static_cast<char*>(base) + offset;
    return static_cast<T*>(object);
  }

  template <typename T, typename RawT = std::decay_t<T>>
  explicit collocated_poly(T&& t)
    : storage_{collocated_storage<RawT>{te::concept_map<Concept, RawT>,
                                        std::forward<T>(t)}}
  { }

  collocated_poly(collocated_poly const& other)
    : storage_{other.storage_, other.get_vtable()}
  { }

  // TODO: Here, we're potentially moving the vtable while we're referring to it.
  //       I think we're breaking strict aliasing rules because the vtable is
  //       referred to by two different things from the underlying storage ctor.
  collocated_poly(collocated_poly&& other)
    : storage_{std::move(other.storage_), other.get_vtable()}
  { }

  collocated_poly& operator=(collocated_poly const& other) {
    collocated_poly(other).swap(*this);
    return *this;
  }

  collocated_poly& operator=(collocated_poly&& other) {
    collocated_poly(std::move(other)).swap(*this);
    return *this;
  }

  void swap(collocated_poly& other) {
    // TODO: Strict aliasing issue here too.
    storage_.swap(get_vtable(), other.storage_, other.get_vtable());
  }

  friend void swap(collocated_poly& a, collocated_poly& b) { a.swap(b); }

  ~collocated_poly() {
    // TODO: A-B problem because we want to destroy the storage which contains
    //       the vtable, but for this we require the vtable.
    storage_.destruct(get_vtable());
  }
};

}} // end namespace te::experimental

#endif // TE_EXPERIMENTAL_COLLOCATED_POLY_HPP
