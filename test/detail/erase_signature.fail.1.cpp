// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <te/concept.hpp>
#include <te/detail/erase_signature.hpp>


using T = te::detail::erase_signature<void (te::T)>::type;

int main() { }
