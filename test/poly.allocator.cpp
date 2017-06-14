// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include "testing.hpp"

#include <dyno/concept.hpp>
#include <dyno/concept_map.hpp>
#include <dyno/poly.hpp>

#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/managed_mapped_file.hpp>
namespace ipc = boost::interprocess;
using namespace dyno::literals;


// This test makes sure that `dyno::poly` can be used with a custom allocator.
// We use Boost.Interprocess allocators because they use fancy pointers and
// they hence make sure that we're really generic in the implementation.

struct Concept : decltype(dyno::requires(
  // ...
)) { };

struct Foo { };

template <>
auto const dyno::concept_map<Concept, Foo> = dyno::make_concept_map(
  // ...
);

static constexpr std::size_t FILE_SIZE = 1000;

void writer(std::string const& filename) {
  ipc::file_mapping::remove(filename.c_str());
  ipc::managed_mapped_file shmem(ipc::create_only, filename.c_str(), FILE_SIZE);

  using ByteAllocator = ipc::allocator<char, ipc::managed_mapped_file::segment_manager>;
  using Poly = dyno::poly<Concept, ByteAllocator>;

  ByteAllocator alloc = shmem.get_allocator<char>();
  Poly poly{12345, alloc};
}

void reader(std::string const& filename) {

}

int main() {
}
