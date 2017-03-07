// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#ifndef DYNO_DETAIL_TRANSFORM_SIGNATURE_HPP
#define DYNO_DETAIL_TRANSFORM_SIGNATURE_HPP

namespace dyno { namespace detail {

// Transforms a signature by applying a metafunction to the return type and
// all the arguments of a function signature. This returns a function type,
// not a pointer to a function.
template <typename Signature, template <typename ...> class F>
struct transform_signature;

template <typename R, typename ...Args, template <typename ...> class F>
struct transform_signature<R (Args...), F> {
  using Result = typename F<R>::type;
  using type = Result (typename F<Args>::type...);
};

template <typename R, typename ...Args, template <typename ...> class F>
struct transform_signature<R (Args..., ...), F> {
  using Result = typename F<R>::type;
  using type = Result (typename F<Args>::type..., ...);
};

}} // end namespace dyno::detail

#endif // DYNO_DETAIL_TRANSFORM_SIGNATURE_HPP
