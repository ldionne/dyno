# Dyno: Runtime polymorphism done right
<a target="_blank" href="https://travis-ci.org/ldionne/dyno">![Travis status][badge.Travis]</a>

## DISCLAIMER
At this point, this library is experimental and it is a pure curiosity.
No stability of interface or quality of implementation is guaranteed.
Use at your own risks.

## Overview
__Dyno__ solves the problem of runtime polymorphism better than vanilla C++
does. It provides a way to define interfaces that can be fulfilled
non-intrusively, and it provides a fully customizable way of storing
polymorphic objects and dispatching to virtual methods. It does not
require inheritance, heap allocation or leaving the comfortable world
of value semantics, and it can do so while outperforming vanilla C++.

__Dyno__ is pure-library implementation of what's also known as [Rust trait
objects][], [Go interfaces][], [Haskell type classes][], and [virtual concepts][].
Under the hood, it uses a C++ technique known as [type erasure][], which is
the idea behind [`std::any`][], [`std::function`][] and many other useful types.

<!-- Important: keep this in sync with example/overview.cpp -->
```c++
#include <dyno.hpp>
#include <iostream>
using namespace dyno::literals;

// Define the interface of something that can be drawn
struct Drawable : decltype(dyno::requires_(
  "draw"_s = dyno::method<void (std::ostream&) const>
)) { };

// Define how concrete types can fulfill that interface
template <typename T>
auto const dyno::default_concept_map<Drawable, T> = dyno::make_concept_map(
  "draw"_s = [](T const& self, std::ostream& out) { self.draw(out); }
);

// Define an object that can hold anything that can be drawn.
struct drawable {
  template <typename T>
  drawable(T x) : poly_{x} { }

  void draw(std::ostream& out) const
  { poly_.virtual_("draw"_s)(out); }

private:
  dyno::poly<Drawable> poly_;
};

struct Square {
  void draw(std::ostream& out) const { out << "Square"; }
};

struct Circle {
  void draw(std::ostream& out) const { out << "Circle"; }
};

void f(drawable const& d) {
  d.draw(std::cout);
}

int main() {
  f(Square{}); // prints Square
  f(Circle{}); // prints Circle
}
```

Alternatively, if you find this to be too much boilerplate and you can stand
using a macro, the following is equivalent:

<!-- Important: keep this in sync with example/overview.macro.cpp -->
```c++
#include <dyno.hpp>
#include <iostream>

// Define the interface of something that can be drawn
DYNO_INTERFACE(Drawable,
  (draw, void (std::ostream&) const)
);

struct Square {
  void draw(std::ostream& out) const { out << "Square"; }
};

struct Circle {
  void draw(std::ostream& out) const { out << "Circle"; }
};

void f(Drawable const& d) {
  d.draw(std::cout);
}

int main() {
  f(Square{}); // prints Square
  f(Circle{}); // prints Circle
}
```


## Compiler requirements
This is a C++17 library. No efforts will be made to support older compilers
(sorry). The library is known to work with the following compilers:

| Compiler    | Version  |
| ----------- |:--------:|
| GCC         | >= 7     |
| Clang       | >= 4.0   |
| Apple Clang | >= 9.1   |


## Dependencies
The library depends on [Boost.Hana][] and [Boost.CallableTraits][]. The unit
tests depend on [libawful][] and the benchmarks depend on [Google Benchmark][],
[Boost.TypeErasure][] and [Mpark.Variant][], but you don't need them to use
the library. For local development, the `dependencies/install.sh` script can
be used to install all the dependencies automatically.


## Building the library
__Dyno__ is a header-only library, so there's nothing to build per-se. Just
add the `include/` directory to your compiler's header search path (and make
sure the dependencies are satisfied), and you're good to go. However, there
are unit tests, examples and benchmarks that can be built:

```sh
(cd dependencies && ./install.sh) # Install dependencies; will print a path to add to CMAKE_PREFIX_PATH
mkdir build
(cd build && cmake .. -DCMAKE_PREFIX_PATH="${PWD}/../dependencies/install") # Setup the build directory

cmake --build build --target examples   # Build and run the examples
cmake --build build --target tests      # Build and run the unit tests
cmake --build build --target check      # Does both examples and tests
cmake --build build --target benchmarks # Build and run the benchmarks
```


## Introduction
In programming, the need for manipulating objects with a common interface but
with a different dynamic type arises very frequently. C++ solves this with
inheritance:

```c++
struct Drawable {
  virtual void draw(std::ostream& out) const = 0;
};

struct Square : Drawable {
  virtual void draw(std::ostream& out) const override final { ... }
};

struct Circle : Drawable {
  virtual void draw(std::ostream& out) const override final { ... }
};

void f(Drawable const* drawable) {
  drawable->draw(std::cout);
}
```

However, this approach has several drawbacks. It is

1. __Intrusive__<br>
   In order for `Square` and `Circle` to fulfill the `Drawable` interface, they
   both need to inherit from the `Drawable` base class. This requires having
   the license to modify those classes, which makes inheritance very inextensible.
   For example, how would you make a `std::vector<int>` fulfill the `Drawable`
   interface? You simply can't.

2. __Incompatible with value semantics__<br>
   Inheritance requires you to pass polymorphic pointers or references to objects
   instead of the objects themselves, which plays very badly with the rest of
   the language and the standard library. For example, how would you copy a
   vector of `Drawable`s? You'd need to provide a virtual `clone()` method, but
   now you've just messed up your interface.

3. __Tightly coupled with dynamic storage__<br>
   Because of the lack of value semantics, we usually end up allocating these
   polymorphic objects on the heap. This is both horribly inefficient and
   semantically wrong, since chances are we did not need the dynamic storage
   duration at all, and an object with automatic storage duration (e.g. on
   the stack) would have been enough.

4. __Prevents inlining__<br>
   95% of the time, we end up calling a virtual method through a polymorphic
   pointer or reference. That requires three indirections: one for loading the
   pointer to the vtable inside the object, one for loading the right entry in
   the vtable, and one for the indirect call to the function pointer. All this
   jumping around makes it difficult for the compiler to make good inlining
   decisions. However, it turns out that all of these indirections except the
   indirect call can be avoided.

Unfortunately, this is the choice that C++ has made for us, and these are the
rules that we are bound to when we need dynamic polymorphism. Or is it really?

### So, what is this library?
__Dyno__ solves the problem of runtime polymorphism in C++ without any of the
drawbacks listed above, and many more goodies. It is:

1. __Non-intrusive__<br>
   An interface can be fulfilled by a type without requiring any modification
   to that type. Heck, a type can even fulfill the same interface in different
   ways! With __Dyno__, you can kiss ridiculous class hierarchies goodbye.

2. __100% based on value semantics__<br>
   Polymorphic objects can be passed as-is, with their natural value semantics.
   You need to copy your polymorphic objects? Sure, just make sure they have
   a copy constructor. You want to make sure they don't get copied? Sure, mark
   it as deleted. With __Dyno__, silly `clone()` methods and the proliferation
   of pointers in APIs are things of the past.

3. __Not coupled with any specific storage strategy__<br>
   The way a polymorphic object is stored is really an implementation detail,
   and it should not interfere with the way you use that object. __Dyno__ gives
   you complete control over the way your objects are stored. You have a lot of
   small polymorphic objects? Sure, let's store them in a local buffer and
   avoid any allocation. Or maybe it makes sense for you to store things on
   the heap? Sure, go ahead.

4. __Flexible dispatch mechanism to achieve best possible performance__<br>
   Storing a pointer to a vtable is just one of many different implementation
   strategies for performing dynamic dispatch. __Dyno__ gives you complete
   control over how dynamic dispatch happens, and can in fact beat vtables
   in some cases. If you have a function that's called in a hot loop, you can
   for example store it directly in the object and skip the vtable indirection.
   You can also use application-specific knowledge the compiler could never
   have to optimize some dynamic calls &mdash; library-level devirtualization.


## Using the library
First, you start by defining a generic interface and giving it a name.
__Dyno__ provides a simple domain specific language to do that. For example,
let's define an interface `Drawable` that describes types that can be drawn:

```c++
#include <dyno.hpp>
using namespace dyno::literals;

struct Drawable : decltype(dyno::requires_(
  "draw"_s = dyno::method<void (std::ostream&) const>
)) { };
```

This defines `Drawable` as representing an interface for anything that has a
method called `draw` taking a reference to a `std::ostream`. __Dyno__ calls
these interfaces _dynamic concepts_, since they describe sets of requirements
to be fulfilled by a type (like C++ concepts). However, unlike C++ concepts,
these _dynamic concepts_ are used to generate runtime interfaces, hence the
name _dynamic_. The above definition is basically equivalent to the following:

```c++
struct Drawable {
  virtual void draw(std::ostream&) const = 0;
};
```

Once the interface is defined, the next step is to actually create a type that
satisfies this interface. With inheritance, you would write something like this:

```c++
struct Square : Drawable {
  virtual void draw(std::ostream& out) const override final {
    out << "square" << std::endl;
  }
};
```

With __Dyno__, the polymorphism is non-intrusive and it is instead provided
via what is called a _concept map_ (after [C++0x Concept Maps][]):

```c++
struct Square { /* ... */ };

template <>
auto const dyno::concept_map<Drawable, Square> = dyno::make_concept_map(
  "draw"_s = [](Square const& square, std::ostream& out) {
    out << "square" << std::endl;
  }
);
```

> This construct is the specialization of a C++14 variable template named
> `concept_map` defined in the `dyno::` namespace. We then initialize that
> specialization with `dyno::make_concept_map(...)`.

The first parameter of the lambda is the implicit `*this` parameter that is
implied when we declared `draw` as a method above. It's also possible to
erase non-member functions (see [the relevant section](#erasing-non-member-functions)).

This _concept map_ defines how the type `Square` satisfies the `Drawable`
concept. In a sense, it _maps_ the type `Square` to its implementation of
the concept, which motivates the appellation. When a type satisfies the
requirements of a concept, we say that the type _models_ (or is a model of)
that concept. Now that `Square` is a model of the `Drawable` concept, we'd
like to use a `Square` polymorphically as a `Drawable`. With traditional
inheritance, we would use a pointer to a base class like this:

```c++
void f(Drawable const* d) {
  d->draw(std::cout);
}

f(new Square{});
```

With __Dyno__, polymorphism and value semantics are compatible, and the way
polymorphic types are passed around can be highly customized. To do this,
we'll need to define a type that can hold anything that's `Drawable`. It is
that type, instead of a `Drawable*`, that we'll be passing around to and from
polymorphic functions. To help define this wrapper, __Dyno__ provides the
`dyno::poly` container, which can hold an arbitrary object satisfying a given
concept. As you will see, `dyno::poly` has a dual role: it stores the polymorphic
object and takes care of the dynamic dispatching of methods. All you need to do
is write a thin wrapper over `dyno::poly` to give it exactly the desired interface:

```c++
struct drawable {
  template <typename T>
  drawable(T x) : poly_{x} { }

  void draw(std::ostream& out) const
  { poly_.virtual_("draw"_s)(out); }

private:
  dyno::poly<Drawable> poly_;
};
```

> Note: You could technically use `dyno::poly` directly in your interfaces.
> However, it is much more convenient to use a wrapper with real methods
> than `dyno::poly`, and so writing a wrapper is recommended.

Let's break this down. First, we define a member `poly_` that is a polymorphic
container for anything that models the `Drawable` concept:

```c++
dyno::poly<Drawable> poly_;
```

Then, we define a constructor that allows constructing this container from an
arbitrary type `T`:

```c++
template <typename T>
drawable(T x) : poly_{x} { }
```

The unsaid assumption here is that `T` actually models the `Drawable` concept.
Indeed, when you create a `dyno::poly` from an object of type `T`, __Dyno__
will go and look at the concept map defined for `Drawable` and `T`, if any. If
there's no such concept map, the library will report that we're trying to create
a `dyno::poly` from a type that does not support it, and your program won't compile.

Finally, the strangest and most important part of the definition above is that
of the `draw` method:

```c++
void draw(std::ostream& out) const
{ poly_.virtual_("draw"_s)(out); }
```

What happens here is that when `.draw` is called on our `drawable` object,
we'll actually perform a dynamic dispatch to the implementation of the `"draw"`
function for the object currently stored in the `dyno::poly`, and call that.
Now, to create a function that accepts anything that's `Drawable`, no need
to worry about pointers and ownership in your interface anymore:

```c++
void f(drawable d) {
  d.draw(std::cout);
}

f(Square{});
```

By the way, if you're thinking that this is all stupid and you should have been
using a template, you're right. However, consider the following, where you really
do need _runtime_ polymorphism:

```c++
drawable get_drawable() {
  if (some_user_input())
    return Square{};
  else
    return Circle{};
}

f(get_drawable());
```

Strictly speaking, you don't need to wrap `dyno::poly`, but doing so puts a nice
barrier between __Dyno__ and the rest of your code, which never has to worry
about how your polymorphic layer is implemented. Also, we largely ignored how
`dyno::poly` was implemented in the above definition. However, `dyno::poly` is
a very powerful policy-based container for polymorphic objects that can be
customized to one's needs for performance. Creating a `drawable` wrapper makes
it easy to tweak the implementation strategy used by `dyno::poly` for performance
without impacting the rest of your code.


### Customizing the polymorphic storage
The first aspect that can be customized in a `dyno::poly` is the way the object
is stored inside the container. By default, we simply store a pointer to the
actual object, like one would do with inheritance-based polymorphism. However,
this is often not the most efficient implementation, and that's why `dyno::poly`
allows customizing it. To do so, simply pass a storage policy to `dyno::poly`.
For example, let's define our `drawable` wrapper so that it tries to store
objects up to `16` bytes in a local buffer, but then falls back to the heap
if the object is larger:

```c++
struct drawable {
  template <typename T>
  drawable(T x) : poly_{x} { }

  void draw(std::ostream& out) const
  { poly_.virtual_("draw"_s)(out); }

private:
  dyno::poly<Drawable, dyno::sbo_storage<16>> poly_;
  //                   ^^^^^^^^^^^^^^^^^^^^^ storage policy
};
```

Notice that nothing except the policy changed in our definition. That is one
very important tenet of __Dyno__; these policies are implementation
details, and they should not change the way you write your code. With the
above definition, you can now create `drawable`s just like you did before,
and no allocation will happen when the object you're creating the `drawable`
from fits in `16` bytes. When it does not fit, however, `dyno::poly` will allocate
a large enough buffer on the heap.

Let's say you actually never want to do an allocation. No problem, just change
the policy to `dyno::local_storage<16>`. If you try to construct a `drawable`
from an object that's too large to fit in the local storage, your program
won't compile. Not only are we saving an allocation, but we're also saving a
pointer indirection every time we access the polymorphic object if we compare
to the traditional inheritance-based approach. By tweaking these (important)
implementation details for you specific use case, you can make your program
much more efficient than with classic inheritance.

Other storage policies are also provided, like `dyno::remote_storage` and
`dyno::non_owning_storage`. `dyno::remote_storage` is the default one, which
always stores a pointer to a heap-allocated object. `dyno::non_owning_storage`
stores a pointer to an object that already exists, without worrying about
the lifetime of that object. It allows implementing non-owning polymorphic
views over objects, which is very useful.

Custom storage policies can also be created quite easily. See `<dyno/storage.hpp>`
for details.


### Customizing the dynamic dispatch
When we introduced `dyno::poly`, we mentioned that it had two roles; the first
is to store the polymorphic object, and the second one is to perform dynamic
dispatch. Just like the storage can be customized, the way dynamic dispatching
is performed can also be customized using policies. For example, let's define
our `drawable` wrapper so that instead of storing a pointer to the vtable, it
instead stores the vtable in the `drawable` object itself. This way, we'll
avoid one indirection each time we access a virtual function:

```c++
struct drawable {
  template <typename T>
  drawable(T x) : poly_{x} { }

  void draw(std::ostream& out) const
  { poly_.virtual_("draw"_s)(out); }

private:
  using Storage = dyno::sbo_storage<16>;                      // storage policy
  using VTable = dyno::vtable<dyno::local<dyno::everything>>; // vtable policy
  dyno::poly<Drawable, Storage, VTable> poly_;
};
```

Notice that nothing besides the vtable policy needs to change in the definition
of our `drawable` type. Furthermore, if we wanted, we could change the storage
policy independently from the vtable policy. With the above, even though we are
saving all indirections, we are paying for it by making our `drawable` object
larger (since it needs to hold the vtable locally). This could be prohibitive
if we had many functions in the vtable. Instead, it would make more sense to
store most of the vtable remotely, but only inline those few functions that we
call heavily. __Dyno__ makes it very easy to do so by using __Selectors__, which
can be used to customize what functions a policy applies to:

```c++
struct drawable {
  template <typename T>
  drawable(T x) : poly_{x} { }

  void draw(std::ostream& out) const
  { poly_.virtual_("draw"_s)(out); }

private:
  using Storage = dyno::sbo_storage<16>;
  using VTable = dyno::vtable<
    dyno::local<dyno::only<decltype("draw"_s)>>,
    dyno::remote<dyno::everything_else>
  >;
  dyno::poly<Drawable, Storage, VTable> poly_;
};
```

Given this definition, the vtable is actually split in two. The first part is
local to the `drawable` object and contains only the `draw` method. The second
part is a pointer to a vtable in static storage that holds the remaining methods
(the destructor, for example).

__Dyno__ provides two vtable policies, `dyno::local<>` and `dyno::remote<>`.
Both of these policies must be customized using a __Selector__. The selectors
supported by the library are `dyno::only<functions...>`, `dyno::except<...>`,
and `dyno::everything_else` (which can also be spelled `dyno::everything`).


### Defaulted concept maps
When defining a concept, it is often the case that one can provide a default
definition for at least some functions associated to the concept. For example,
by default, it would probably make sense to use a member function named `draw`
(if any) to implement the abstract `"draw"` method of the `Drawable` concept.
For this, one can use `dyno::default_concept_map`:

```c++
template <typename T>
auto const dyno::default_concept_map<Drawable, T> = dyno::make_concept_map(
  "draw"_s = [](auto const& self, std::ostream& out) { self.draw(out); }
);
```

Now, whenever we try to look at how some type `T` fulfills the `Drawable`
concept, we'll fall back to the default concept map if no concept map was
defined. For example, we can create a new type `Circle`:

```c++
struct Circle {
  void draw(std::ostream& out) const {
    out << "circle" << std::endl;
  }
};

f(Circle{}); // prints "circle"
```

`Circle` is automatically a model of `Drawable`, even though we did not
explicitly define a concept map for `Circle`. On the other hand, if we
were to define such a concept map, it would have precedence over the
default one:

```c++
template <>
auto dyno::concept_map<Drawable, Circle> = dyno::make_concept_map(
  "draw"_s = [](Circle const& circle, std::ostream& out) {
    out << "triangle" << std::endl;
  }
);

f(Circle{}); // prints "triangle"
```


### Parametric concept maps
It is sometimes useful to define a concept map for a complete family of types
all at once. For example, we might want to make `std::vector<T>` a model of
`Drawable`, but only when `T` can be printed to a stream. This is easily
achieved by using this (not so) secret trick:

```c++
template <typename T>
auto const dyno::concept_map<Drawable, std::vector<T>, std::void_t<decltype(
  std::cout << std::declval<T>()
)>> = dyno::make_concept_map(
  "draw"_s = [](std::vector<T> const& v, std::ostream& out) {
    for (auto const& x : v)
      out << x << ' ';
  }
);

f(std::vector<int>{1, 2, 3}) // prints "1 2 3 "
```

> Notice how we do not have to modify `std::vector` at all. How could we do
> this with classic polymorphism? Answer: no can do.


### Erasing non-member functions
__Dyno__ allows erasing non-member functions and functions that are dispatched
on an arbitrary argument (but only one argument) too. To do this, simply define
the concept using `dyno::function` instead of `dyno::method`, and use the
`dyno::T` placeholder to denote the argument being erased:

```c++
// Define the interface of something that can be drawn
struct Drawable : decltype(dyno::requires_(
  "draw"_s = dyno::function<void (dyno::T const&, std::ostream&)>
)) { };
```

The `dyno::T const&` parameter used above represents the type of the object
on which the function is being called. However, it does not have to be the
first parameter:

```c++
struct Drawable : decltype(dyno::requires_(
  "draw"_s = dyno::function<void (std::ostream&, dyno::T const&)>
)) { };
```

The fulfillment of the concept does not change whether the concept uses a
method or a function, but make sure that the parameters of your function
implementation match that of the function declared in the concept:

```c++
// Define how concrete types can fulfill that interface
template <typename T>
auto const dyno::default_concept_map<Drawable, T> = dyno::make_concept_map(
  "draw"_s = [](std::ostream& out, T const& self) { self.draw(out); }
  //            ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ matches the concept definition
);
```

Finally, when calling a `function` on a `dyno::poly`, you'll have to pass in
all the parameters explicitly, since __Dyno__ can't guess which one you want
to dispatch on. The parameter that was declared with a `dyno::T` placeholder
in the concept should be passed the `dyno::poly` itself:

```c++
// Define an object that can hold anything that can be drawn.
struct drawable {
  template <typename T>
  drawable(T x) : poly_{x} { }

  void draw(std::ostream& out) const
  { poly_.virtual_("draw"_s)(out, poly_); }
  //                              ^^^^^ passing the poly explicitly

private:
  dyno::poly<Drawable> poly_;
};
```


<!-- Links -->
[`std::any`]: http://en.cppreference.com/w/cpp/utility/any
[`std::function`]: http://en.cppreference.com/w/cpp/utility/functional/function
[badge.Travis]: https://travis-ci.org/ldionne/dyno.svg?branch=master
[Boost.CallableTraits]: https://github.com/badair/callable_traits
[Boost.Hana]: https://github.com/boostorg/hana
[Boost.TypeErasure]: http://www.boost.org/doc/libs/release/doc/html/boost_typeerasure.html
[C++0x Concept Maps]: https://isocpp.org/wiki/faq/cpp0x-concepts-history#cpp0x-concept-maps
[Go interfaces]: https://gobyexample.com/interfaces
[Google Benchmark]: https://github.com/google/benchmark
[Haskell type classes]: http://learnyouahaskell.com/types-and-typeclasses
[libawful]: https://github.com/ldionne/libawful
[Mpark.Variant]: https://github.com/mpark/variant
[Rust trait objects]: https://doc.rust-lang.org/book/ch17-02-trait-objects.html
[type erasure]: https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Type_Erasure
[virtual concepts]: https://github.com/andyprowl/virtual-concepts
