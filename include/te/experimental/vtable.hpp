// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#ifndef TE_EXPERIMENTAL_VTABLE_HPP
#define TE_EXPERIMENTAL_VTABLE_HPP

#include <te/concept.hpp>
#include <te/detail/erase_function.hpp>

#include <type_traits>
#include <utility>


namespace te {
namespace experimental {

namespace detail {
  template <typename ...Functions>
  struct vtable_base;

  template <typename Concept, typename ConceptMap, typename ...Functions>
  struct vtable_impl;

  template <typename Concept, typename ConceptMap>
  struct make_vtable_impl {
    template <typename ...Functions>
    using apply = vtable_impl<Concept, ConceptMap, Functions...>;
  };
} // end namespace detail

template <typename Concept>
struct vtable {
  template <typename ConceptMap>
  constexpr explicit vtable(ConceptMap) {
    using Derived = te::unpack_vtable_layout<
      Concept, detail::make_vtable_impl<Concept, ConceptMap>::template apply
    >;
    new (&base_) Derived{};
  }

  template <typename Name>
  constexpr auto operator[](Name) const {
    Base const* base = static_cast<Base const*>(static_cast<void const*>(&base_));
    return [base](auto&& ...args) -> decltype(auto) {
      return base->apply(Name{}, std::forward<decltype(args)>(args)...);
    };
  }

private:
  using Base = te::unpack_vtable_layout<Concept, detail::vtable_base>;
  std::aligned_storage<sizeof(Base)> base_;
};

/*
What follows is a script to generate the specialization of `vtable_base`
and `vtable_impl`. Run the script as

  awk '/SCRIPTBEGIN/{flag=1;next}/SCRIPTEND/{flag=0}flag' ${thisfile} | erb

SCRIPTBEGIN
<% (0..10).each do |n| %>
template <
  <%= (0...n).map {|i| "typename Name#{i}, typename R#{i}, typename ...Args#{i}" }.join(",\n  ") %>
> struct vtable_base<
  <%= (0...n).map {|i| "std::pair<Name#{i}, R#{i} (*)(Args#{i}...)>" }.join(",\n  ") %>
> {
  <%= (0...n).map {|i| "virtual R#{i} apply(Name#{i}, Args#{i}...) const = 0;" }.join("\n  ") %>
};

template <typename Concept, typename ConceptMap
  <%= (0...n).map {|i| ", typename Name#{i}, typename R#{i}, typename ...Args#{i}" }.join("\n  ") %>
>
struct vtable_impl<Concept, ConceptMap
  <%= (0...n).map {|i| ", std::pair<Name#{i}, R#{i} (*)(Args#{i}...)>" }.join("\n  ") %>
> final : vtable_base<
  <%= (0...n).map {|i| "std::pair<Name#{i}, R#{i} (*)(Args#{i}...)>" }.join(",\n  ") %>
> {
  <%= (0...n).map {|i|
    "R#{i} apply(Name#{i} name, Args#{i} ...args) const override final" +
    "{ return te::detail::erase_function<typename decltype(Concept{}.get_signature(name))::type>(ConceptMap{}[name])(std::forward<Args#{i}>(args)...); }"
  }.join("\n  ") %>
};
<% end %>
SCRIPTEND */

namespace detail {
  ////////////////////////////////////////////////////////////////////////////
  // BEGIN GENERATED CODE
  ////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////
  // END GENERATED CODE
  ////////////////////////////////////////////////////////////////////////////
} // end namespace detail

} // end namespace experimental
} // end namespace te

#endif // TE_EXPERIMENTAL_VTABLE_HPP
