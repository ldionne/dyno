// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#ifndef TE_EXPERIMENTAL_UNROLLED_VTABLE_HPP
#define TE_EXPERIMENTAL_UNROLLED_VTABLE_HPP

#include <te/concept.hpp>

#include <utility>


namespace te { namespace experimental {

namespace detail {
  template <typename ...Mappings>
  struct unrolled_vtable_impl;
}

template <typename Concept>
using unrolled_vtable = te::unpack_vtable_layout<Concept, detail::unrolled_vtable_impl>;

/*
What follows is a script to generate the specializations of `unrolled_vtable_impl`.
Run the script as

  awk '/SCRIPTBEGIN/{flag=1;next}/SCRIPTEND/{flag=0}flag' ${thisfile} | erb

SCRIPTBEGIN
<% (0..10).each do |n| %>
template <
  <%= (0...n).map {|i| "typename Name#{i}, typename Fptr#{i}" }.join(",\n  ") %>
> struct unrolled_vtable_impl<
  <%= (0...n).map {|i| "std::pair<Name#{i}, Fptr#{i}>" }.join(",\n  ") %>
> {
  template <typename ConceptMap>
  constexpr explicit unrolled_vtable_impl(ConceptMap map)
    <%= ": " unless n == 0 %><%= (0...n).map {|i| "fptr#{i}_(map.erased(Name#{i}{}))" }.join("\n    , ") %>
  { }
  <%= (0...n).map {|i| "constexpr auto operator[](Name#{i}) const { return fptr#{i}_; };" }.join("\n  ") %>

private:
  <%= (0...n).map {|i| "Fptr#{i} fptr#{i}_;" }.join("\n  ") %>
};
<% end %>
SCRIPTEND */

namespace detail {
  ////////////////////////////////////////////////////////////////////////////
  // BEGIN GENERATED CODE
  ////////////////////////////////////////////////////////////////////////////
  template <

  > struct unrolled_vtable_impl<

  > {
    template <typename ConceptMap>
    constexpr explicit unrolled_vtable_impl(ConceptMap map)

    { }


  private:

  };

  template <
    typename Name0, typename Fptr0
  > struct unrolled_vtable_impl<
    std::pair<Name0, Fptr0>
  > {
    template <typename ConceptMap>
    constexpr explicit unrolled_vtable_impl(ConceptMap map)
      : fptr0_(map.erased(Name0{}))
    { }
    constexpr auto operator[](Name0) const { return fptr0_; };

  private:
    Fptr0 fptr0_;
  };

  template <
    typename Name0, typename Fptr0,
    typename Name1, typename Fptr1
  > struct unrolled_vtable_impl<
    std::pair<Name0, Fptr0>,
    std::pair<Name1, Fptr1>
  > {
    template <typename ConceptMap>
    constexpr explicit unrolled_vtable_impl(ConceptMap map)
      : fptr0_(map.erased(Name0{}))
      , fptr1_(map.erased(Name1{}))
    { }
    constexpr auto operator[](Name0) const { return fptr0_; };
    constexpr auto operator[](Name1) const { return fptr1_; };

  private:
    Fptr0 fptr0_;
    Fptr1 fptr1_;
  };

  template <
    typename Name0, typename Fptr0,
    typename Name1, typename Fptr1,
    typename Name2, typename Fptr2
  > struct unrolled_vtable_impl<
    std::pair<Name0, Fptr0>,
    std::pair<Name1, Fptr1>,
    std::pair<Name2, Fptr2>
  > {
    template <typename ConceptMap>
    constexpr explicit unrolled_vtable_impl(ConceptMap map)
      : fptr0_(map.erased(Name0{}))
      , fptr1_(map.erased(Name1{}))
      , fptr2_(map.erased(Name2{}))
    { }
    constexpr auto operator[](Name0) const { return fptr0_; };
    constexpr auto operator[](Name1) const { return fptr1_; };
    constexpr auto operator[](Name2) const { return fptr2_; };

  private:
    Fptr0 fptr0_;
    Fptr1 fptr1_;
    Fptr2 fptr2_;
  };

  template <
    typename Name0, typename Fptr0,
    typename Name1, typename Fptr1,
    typename Name2, typename Fptr2,
    typename Name3, typename Fptr3
  > struct unrolled_vtable_impl<
    std::pair<Name0, Fptr0>,
    std::pair<Name1, Fptr1>,
    std::pair<Name2, Fptr2>,
    std::pair<Name3, Fptr3>
  > {
    template <typename ConceptMap>
    constexpr explicit unrolled_vtable_impl(ConceptMap map)
      : fptr0_(map.erased(Name0{}))
      , fptr1_(map.erased(Name1{}))
      , fptr2_(map.erased(Name2{}))
      , fptr3_(map.erased(Name3{}))
    { }
    constexpr auto operator[](Name0) const { return fptr0_; };
    constexpr auto operator[](Name1) const { return fptr1_; };
    constexpr auto operator[](Name2) const { return fptr2_; };
    constexpr auto operator[](Name3) const { return fptr3_; };

  private:
    Fptr0 fptr0_;
    Fptr1 fptr1_;
    Fptr2 fptr2_;
    Fptr3 fptr3_;
  };

  template <
    typename Name0, typename Fptr0,
    typename Name1, typename Fptr1,
    typename Name2, typename Fptr2,
    typename Name3, typename Fptr3,
    typename Name4, typename Fptr4
  > struct unrolled_vtable_impl<
    std::pair<Name0, Fptr0>,
    std::pair<Name1, Fptr1>,
    std::pair<Name2, Fptr2>,
    std::pair<Name3, Fptr3>,
    std::pair<Name4, Fptr4>
  > {
    template <typename ConceptMap>
    constexpr explicit unrolled_vtable_impl(ConceptMap map)
      : fptr0_(map.erased(Name0{}))
      , fptr1_(map.erased(Name1{}))
      , fptr2_(map.erased(Name2{}))
      , fptr3_(map.erased(Name3{}))
      , fptr4_(map.erased(Name4{}))
    { }
    constexpr auto operator[](Name0) const { return fptr0_; };
    constexpr auto operator[](Name1) const { return fptr1_; };
    constexpr auto operator[](Name2) const { return fptr2_; };
    constexpr auto operator[](Name3) const { return fptr3_; };
    constexpr auto operator[](Name4) const { return fptr4_; };

  private:
    Fptr0 fptr0_;
    Fptr1 fptr1_;
    Fptr2 fptr2_;
    Fptr3 fptr3_;
    Fptr4 fptr4_;
  };

  template <
    typename Name0, typename Fptr0,
    typename Name1, typename Fptr1,
    typename Name2, typename Fptr2,
    typename Name3, typename Fptr3,
    typename Name4, typename Fptr4,
    typename Name5, typename Fptr5
  > struct unrolled_vtable_impl<
    std::pair<Name0, Fptr0>,
    std::pair<Name1, Fptr1>,
    std::pair<Name2, Fptr2>,
    std::pair<Name3, Fptr3>,
    std::pair<Name4, Fptr4>,
    std::pair<Name5, Fptr5>
  > {
    template <typename ConceptMap>
    constexpr explicit unrolled_vtable_impl(ConceptMap map)
      : fptr0_(map.erased(Name0{}))
      , fptr1_(map.erased(Name1{}))
      , fptr2_(map.erased(Name2{}))
      , fptr3_(map.erased(Name3{}))
      , fptr4_(map.erased(Name4{}))
      , fptr5_(map.erased(Name5{}))
    { }
    constexpr auto operator[](Name0) const { return fptr0_; };
    constexpr auto operator[](Name1) const { return fptr1_; };
    constexpr auto operator[](Name2) const { return fptr2_; };
    constexpr auto operator[](Name3) const { return fptr3_; };
    constexpr auto operator[](Name4) const { return fptr4_; };
    constexpr auto operator[](Name5) const { return fptr5_; };

  private:
    Fptr0 fptr0_;
    Fptr1 fptr1_;
    Fptr2 fptr2_;
    Fptr3 fptr3_;
    Fptr4 fptr4_;
    Fptr5 fptr5_;
  };

  template <
    typename Name0, typename Fptr0,
    typename Name1, typename Fptr1,
    typename Name2, typename Fptr2,
    typename Name3, typename Fptr3,
    typename Name4, typename Fptr4,
    typename Name5, typename Fptr5,
    typename Name6, typename Fptr6
  > struct unrolled_vtable_impl<
    std::pair<Name0, Fptr0>,
    std::pair<Name1, Fptr1>,
    std::pair<Name2, Fptr2>,
    std::pair<Name3, Fptr3>,
    std::pair<Name4, Fptr4>,
    std::pair<Name5, Fptr5>,
    std::pair<Name6, Fptr6>
  > {
    template <typename ConceptMap>
    constexpr explicit unrolled_vtable_impl(ConceptMap map)
      : fptr0_(map.erased(Name0{}))
      , fptr1_(map.erased(Name1{}))
      , fptr2_(map.erased(Name2{}))
      , fptr3_(map.erased(Name3{}))
      , fptr4_(map.erased(Name4{}))
      , fptr5_(map.erased(Name5{}))
      , fptr6_(map.erased(Name6{}))
    { }
    constexpr auto operator[](Name0) const { return fptr0_; };
    constexpr auto operator[](Name1) const { return fptr1_; };
    constexpr auto operator[](Name2) const { return fptr2_; };
    constexpr auto operator[](Name3) const { return fptr3_; };
    constexpr auto operator[](Name4) const { return fptr4_; };
    constexpr auto operator[](Name5) const { return fptr5_; };
    constexpr auto operator[](Name6) const { return fptr6_; };

  private:
    Fptr0 fptr0_;
    Fptr1 fptr1_;
    Fptr2 fptr2_;
    Fptr3 fptr3_;
    Fptr4 fptr4_;
    Fptr5 fptr5_;
    Fptr6 fptr6_;
  };

  template <
    typename Name0, typename Fptr0,
    typename Name1, typename Fptr1,
    typename Name2, typename Fptr2,
    typename Name3, typename Fptr3,
    typename Name4, typename Fptr4,
    typename Name5, typename Fptr5,
    typename Name6, typename Fptr6,
    typename Name7, typename Fptr7
  > struct unrolled_vtable_impl<
    std::pair<Name0, Fptr0>,
    std::pair<Name1, Fptr1>,
    std::pair<Name2, Fptr2>,
    std::pair<Name3, Fptr3>,
    std::pair<Name4, Fptr4>,
    std::pair<Name5, Fptr5>,
    std::pair<Name6, Fptr6>,
    std::pair<Name7, Fptr7>
  > {
    template <typename ConceptMap>
    constexpr explicit unrolled_vtable_impl(ConceptMap map)
      : fptr0_(map.erased(Name0{}))
      , fptr1_(map.erased(Name1{}))
      , fptr2_(map.erased(Name2{}))
      , fptr3_(map.erased(Name3{}))
      , fptr4_(map.erased(Name4{}))
      , fptr5_(map.erased(Name5{}))
      , fptr6_(map.erased(Name6{}))
      , fptr7_(map.erased(Name7{}))
    { }
    constexpr auto operator[](Name0) const { return fptr0_; };
    constexpr auto operator[](Name1) const { return fptr1_; };
    constexpr auto operator[](Name2) const { return fptr2_; };
    constexpr auto operator[](Name3) const { return fptr3_; };
    constexpr auto operator[](Name4) const { return fptr4_; };
    constexpr auto operator[](Name5) const { return fptr5_; };
    constexpr auto operator[](Name6) const { return fptr6_; };
    constexpr auto operator[](Name7) const { return fptr7_; };

  private:
    Fptr0 fptr0_;
    Fptr1 fptr1_;
    Fptr2 fptr2_;
    Fptr3 fptr3_;
    Fptr4 fptr4_;
    Fptr5 fptr5_;
    Fptr6 fptr6_;
    Fptr7 fptr7_;
  };

  template <
    typename Name0, typename Fptr0,
    typename Name1, typename Fptr1,
    typename Name2, typename Fptr2,
    typename Name3, typename Fptr3,
    typename Name4, typename Fptr4,
    typename Name5, typename Fptr5,
    typename Name6, typename Fptr6,
    typename Name7, typename Fptr7,
    typename Name8, typename Fptr8
  > struct unrolled_vtable_impl<
    std::pair<Name0, Fptr0>,
    std::pair<Name1, Fptr1>,
    std::pair<Name2, Fptr2>,
    std::pair<Name3, Fptr3>,
    std::pair<Name4, Fptr4>,
    std::pair<Name5, Fptr5>,
    std::pair<Name6, Fptr6>,
    std::pair<Name7, Fptr7>,
    std::pair<Name8, Fptr8>
  > {
    template <typename ConceptMap>
    constexpr explicit unrolled_vtable_impl(ConceptMap map)
      : fptr0_(map.erased(Name0{}))
      , fptr1_(map.erased(Name1{}))
      , fptr2_(map.erased(Name2{}))
      , fptr3_(map.erased(Name3{}))
      , fptr4_(map.erased(Name4{}))
      , fptr5_(map.erased(Name5{}))
      , fptr6_(map.erased(Name6{}))
      , fptr7_(map.erased(Name7{}))
      , fptr8_(map.erased(Name8{}))
    { }
    constexpr auto operator[](Name0) const { return fptr0_; };
    constexpr auto operator[](Name1) const { return fptr1_; };
    constexpr auto operator[](Name2) const { return fptr2_; };
    constexpr auto operator[](Name3) const { return fptr3_; };
    constexpr auto operator[](Name4) const { return fptr4_; };
    constexpr auto operator[](Name5) const { return fptr5_; };
    constexpr auto operator[](Name6) const { return fptr6_; };
    constexpr auto operator[](Name7) const { return fptr7_; };
    constexpr auto operator[](Name8) const { return fptr8_; };

  private:
    Fptr0 fptr0_;
    Fptr1 fptr1_;
    Fptr2 fptr2_;
    Fptr3 fptr3_;
    Fptr4 fptr4_;
    Fptr5 fptr5_;
    Fptr6 fptr6_;
    Fptr7 fptr7_;
    Fptr8 fptr8_;
  };

  template <
    typename Name0, typename Fptr0,
    typename Name1, typename Fptr1,
    typename Name2, typename Fptr2,
    typename Name3, typename Fptr3,
    typename Name4, typename Fptr4,
    typename Name5, typename Fptr5,
    typename Name6, typename Fptr6,
    typename Name7, typename Fptr7,
    typename Name8, typename Fptr8,
    typename Name9, typename Fptr9
  > struct unrolled_vtable_impl<
    std::pair<Name0, Fptr0>,
    std::pair<Name1, Fptr1>,
    std::pair<Name2, Fptr2>,
    std::pair<Name3, Fptr3>,
    std::pair<Name4, Fptr4>,
    std::pair<Name5, Fptr5>,
    std::pair<Name6, Fptr6>,
    std::pair<Name7, Fptr7>,
    std::pair<Name8, Fptr8>,
    std::pair<Name9, Fptr9>
  > {
    template <typename ConceptMap>
    constexpr explicit unrolled_vtable_impl(ConceptMap map)
      : fptr0_(map.erased(Name0{}))
      , fptr1_(map.erased(Name1{}))
      , fptr2_(map.erased(Name2{}))
      , fptr3_(map.erased(Name3{}))
      , fptr4_(map.erased(Name4{}))
      , fptr5_(map.erased(Name5{}))
      , fptr6_(map.erased(Name6{}))
      , fptr7_(map.erased(Name7{}))
      , fptr8_(map.erased(Name8{}))
      , fptr9_(map.erased(Name9{}))
    { }
    constexpr auto operator[](Name0) const { return fptr0_; };
    constexpr auto operator[](Name1) const { return fptr1_; };
    constexpr auto operator[](Name2) const { return fptr2_; };
    constexpr auto operator[](Name3) const { return fptr3_; };
    constexpr auto operator[](Name4) const { return fptr4_; };
    constexpr auto operator[](Name5) const { return fptr5_; };
    constexpr auto operator[](Name6) const { return fptr6_; };
    constexpr auto operator[](Name7) const { return fptr7_; };
    constexpr auto operator[](Name8) const { return fptr8_; };
    constexpr auto operator[](Name9) const { return fptr9_; };

  private:
    Fptr0 fptr0_;
    Fptr1 fptr1_;
    Fptr2 fptr2_;
    Fptr3 fptr3_;
    Fptr4 fptr4_;
    Fptr5 fptr5_;
    Fptr6 fptr6_;
    Fptr7 fptr7_;
    Fptr8 fptr8_;
    Fptr9 fptr9_;
  };
  ////////////////////////////////////////////////////////////////////////////
  // END GENERATED CODE
  ////////////////////////////////////////////////////////////////////////////
} // end namespace detail

}} // end namespace te::experimental

#endif // TE_EXPERIMENTAL_UNROLLED_VTABLE_HPP
