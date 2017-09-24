// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#ifndef BENCHMARK_ANY_ITERATOR_HANDROLLED_VTABLE_HPP
#define BENCHMARK_ANY_ITERATOR_HANDROLLED_VTABLE_HPP

template <typename Reference>
struct HandrolledVTable {
  void (*increment)(void*);
  Reference (*dereference)(void*);
  bool (*equal)(void const*, void const*);
  void (*dtor)(void*);
  void (*delete_)(void*);
};

template <typename T>
void increment(void* self) {
  ++*static_cast<T*>(self);
}

template <typename T>
bool equal(void const* a, void const* b) {
  return *static_cast<T const*>(a) == *static_cast<T const*>(b);
}

template <typename T>
typename T::reference dereference(void* self) {
  return **static_cast<T*>(self);
}

template <typename T>
void dtor(void* self) {
  static_cast<T*>(self)->~T();
}

template <typename T>
void delete_(void* self) {
  delete static_cast<T*>(self);
}

template <typename T>
static constexpr HandrolledVTable<typename T::reference> const vtable_for = {
  &increment<T>, &dereference<T>, &equal<T>, &dtor<T>, &delete_<T>
};

#endif // BENCHMARK_ANY_ITERATOR_HANDROLLED_VTABLE_HPP
