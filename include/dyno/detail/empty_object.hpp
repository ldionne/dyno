// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#ifndef DYNO_DETAIL_EMPTY_OBJECT_HPP
#define DYNO_DETAIL_EMPTY_OBJECT_HPP

#include <type_traits>


namespace dyno { namespace detail {

// Hack to get an instance of an empty type that is not default constructible,
// while still satisfying the C++ standard. None of this would be necessary if
// stateless lambdas were default constructible.
//
// The idea behind this trick is that we make two layout-compatible types `T1`
// and `T2`, while having `T2` inherit from the empty class `T` we're trying
// to bypass the construction of.
//
// We then create a union of these two types, and initialize `T1` inside that
// union. Since `T1` and `T2` are layout-compatible, we can legally access the
// `T2` member of the union, which we can then legally cast to its base class
// `T`. Et voilà, we've got a valid `T` object, yet we've never initialized it.
//
// For details on standard layout types, see:
// http://en.cppreference.com/w/cpp/language/data_members#Standard_layout
template <typename T>
struct empty_object {
  static_assert(std::is_standard_layout<T>{},
    "This trick won't work if `T` is not standard layout, because that's "
    "required for `T2` below to be standard layout.");

  static_assert(std::is_empty<T>{},
    "This trick won't work if `T` is not empty, because that's required for "
    "`T1` and `T2` below to be layout-compatible (and also to make sure `T` "
    "is trivially destructible.");

  // `T1` and `T2` have `c` as a common initial sequence of non-static
  // data members:
  //   Two standard-layout non-union class types may have a common initial
  //   sequence of non-static data members and bit-fields, for a sequence of
  //   one or more initial members (in order of declaration), if the members
  //   have layout-compatible types [...].

  // `T1` and `T2` are layout-compatible:
  //   Two standard-layout non-union class types are called layout-compatible
  //   if [...] their common initial sequence consists of every non-static
  //   data member and bit field.
  struct T1     { char c; };
  struct T2 : T { char c; };

  union Storage {
    constexpr Storage() : t1{} { }
    T1 t1;
    T2 t2;
  };

  static T get() {
    // Initialize the union with `T1` active.
    Storage storage{};

    // Access the member `c` of `T2` in the union:
    //   In a standard-layout union with an active member of non-union class
    //   type `T1`, it is permitted to read a non-static data member `m` of
    //   another union member of non-union class type `T2` provided `m` is
    //   part of the common initial sequence of `T1` and `T2` [...].
    char const* c = &storage.t2.c;

    // From this pointer, get a pointer back to `T2`:
    //   A pointer to an object of standard-layout struct type can be
    //   `reinterpret_cast` to pointer to its first non-static data member
    //   (if it has non-static data members) [...], and vice versa.
    //   (padding is not allowed before the first data member). [...]
    T2 const* t2 = reinterpret_cast<T2 const*>(c);

    // Finally, get a pointer to the base class `T` from the `T2` pointer.
    T const* t = static_cast<T const*>(t2);

    return *t;
  }
};

}} // end namespace dyno::detail

#endif // DYNO_DETAIL_EMPTY_OBJECT_HPP
