# Type Erased: Runtime polymorphism done right
<a target="_blank" href="https://travis-ci.org/ldionne/te">![Travis status][badge.Travis]</a>

## DISCLAIMER
At this point, this library is experimental and it is a pure curiosity.
No stability of interface or quality of implementation is guaranteed at.
Use at your own risks.

## Overview
__Type Erased__ solves the problem of runtime polymorphism in C++ better than
the language does. It provides a way to define interfaces that can be fulfilled
non-intrusively, and it provides a fully customizable way of storing polymorphic
objects and dispaching to virtual methods. It does not require inheritance,
heap allocation or leaving the comfortable world of value semantics, and it
can do so while outperforming vanilla C++.

<!-- Important: keep this in sync with example/overview.cpp -->
```c++
#include <te.hpp>
#include <iostream>
using namespace te::literals;

// Define the interface of something that can be drawn
struct Drawable : decltype(te::requires(
  "draw"_s = te::function<void (te::T const&, std::ostream&)>
)) { };

// Provide a default implementation of that interface
template <typename T>
auto te::default_concept_map<Drawable, T> = te::make_default_concept_map<Drawable, T>(
  "draw"_s = [](T const& self, std::ostream& out) { self.draw(out); }
);

// Define an object that can hold anything that can be drawn.
struct drawable {
  template <typename T>
  drawable(T x) : poly_{x} { }

  void draw(std::ostream& out) const
  { poly_.virtual_("draw"_s)(poly_.get(), out); }

private:
  te::poly<Drawable> poly_;
};

struct Square {
  void draw(std::ostream& out) const { /* ... */ }
};

struct Circle {
  void draw(std::ostream& out) const { /* ... */ }
};

void f(drawable const& d) {
  d.draw(std::cout);
}
```


## Dependencies
The library depends on [Boost.Hana][] and [CallableTraits][]. The unit tests
depend on [libawful][] and the benchmarks on [Google Benchmark][], but you don't
need them to use the library. For local development, all the dependencies are
pulled automatically.


## Building the library
`te` is a header-only library, so there's nothing to build per-se. Just add the
`include/` directory to your compiler's header search path (and make sure the
dependencies are satisfied), and you're good to go. However, there are unit
tests, examples and benchmarks that can be built:

```sh
(mkdir build && cd build && cmake ..)     # Setup the build directory
cmake --build build --target dependencies # Fetch and build all the dependencies

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
  void draw(std::ostream& out) const override final { ... }
};

struct Circle : Drawable {
  void draw(std::ostream& out) const override final { ... }
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
   duration at all, and a simple stack-allocated object with the usual lifetime
   would have been enough.

4. __Slow__<br>
   95% of the time, we end up calling a virtual method through a polymorphic
   pointer or reference. That requires three indirections: one for loading the
   pointer to the vtable inside the object, one for loading the right entry in
   the vtable, and one for the call to the function pointer. All of this but
   the indirect call can be avoided.

Unfortunately, this is the choice that C++ has made for us, and these are the
rules that we are bound to when we need dynamic polymorphism. Or is it really?

### So, what is this library?
__Type Erased__ solves the problem of runtime polymorphism in C++ without any
of the drawbacks listed above, and many more goodies. It is:

1. __Non-intrusive__<br>
   An interface can be fulfilled by a type without requiring any modification
   to that type. Heck, a type can even fulfill the same interface in different
   ways! With __Type Erased__, you can kiss ridiculous class hierarchies
   goodbye.

2. __100% based on value semantics__<br>
   Polymorphic objects can be passed as-is, with their natural value semantics.
   You need to copy your polymorphic objects? Sure, just make sure they have
   a copy constructor. You want to make sure they don't get copied? Sure, mark
   it as deleted. With __Type Erased__, silly `clone()` methods and the
   proliferation of pointers in APIs are things of the past.

3. __Not coupled with any specific storage strategy__<br>
   The way a polymorphic object is stored is really an implementation detail,
   and it should not interfere with the way you use that object. __Type Erased__
   gives you complete control over the way your objects are stored. You have a
   lot of small polymorphic objects? Sure, let's store them on the stack directly
   and avoid any allocation. Or maybe it makes sense for you to store things on
   the heap? Sure, go ahead.

4. __Fast__<br>
   Storing a pointer to a vtable is just one of many different implementation
   strategies for performing dynamic dispatch. __Type Erased__ gives you
   complete control over how dynamic dispatch happens, and can in fact beat
   vtables. You've got a function that gets called in a hot loop? Sure, let's
   store it in the object directly and skip the indirection through the vtable.
   The classic vtable scheme works for you? Sure, let's use this and get
   exactly the same performance as usual vtables.


## Using the library
First, you start by defining a generic interface and giving it a name.
__Type Erased__ provides a simple domain specific language to do that.
For example, let's define an interface `Drawable` that describes types
that can be drawn:

```c++
#include <te.hpp>
using namespace te::literals;

struct Drawable : decltype(te::requires(
  "draw"_s = te::function<void (te::T const&, std::ostream&)>
)) { };
```

This defines `Drawable` as representing an interface for anything that has a
function called `draw` taking a reference to a const object of any type, and
a `std::ostream&`. __Type Erased__ calls these interfaces _dynamic concepts_,
since they describe sets of requirements to be fulfilled by a type (like C++
concepts). However, unlike C++ concepts, these _dynamic concepts_ are used to
generate runtime interfaces, hence the name _dynamic_. The above definition is
basically equivalent to the following, except we make no statement about whether
`draw` is a member function or not:

```c++
struct Drawable {
  virtual void draw(std::ostream&) const = 0;
};
```

In some sense, the `te::T const&` parameter used above represents the type of
the (polymorphic) `this` pointer that would be passed in case of a traditional
virtual method. When the interface is defined, the next step is to actually
create a type that satisfies this interface. With inheritance, you would write
something like this:

```c++
struct Square : Drawable {
  void draw(std::ostream& out) const override final {
    out << "square" << std::endl;
  }
};
```

With __Type Erased__, the polymorphism is non-intrusive and it is instead
provided via what is called a _concept map_ (after [C++0x Concept Maps][]):

```c++
struct Square { /* ... */ };

template <>
auto te::concept_map<Drawable, Square> = te::make_concept_map<Drawable, Square>(
  "draw"_s = [](Square const& square, std::ostream& out) {
    out << "square" << std::endl;
  }
);
```

> This construct is the specialization of a C++14 variable template named
> `concept_map` defined in the `te::` namespace. We then initialize that
> specialization with `te::make_concept_map<Drawable, Square>(...)`.

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

With __Type Erased__, polymorphism and value semantics are compatible, and the
way polymorphic types are passed around can be highly customized. To do this,
we'll need to define a type that can hold anything that's `Drawable`. It is
that type, instead of a `Drawable*`, that we'll be passing around to and from
polymorphic functions. To help define this wrapper, __Type Erased__ provides
the `te::poly` container, which can hold an arbitrary object satisfying a given
concept. As you will see, `te::poly` has a dual role: it stores the polymorphic
object and takes care of the dynamic dispatching of methods. All you need to do
is write a thin wrapper over `te::poly` to give it exactly the desired interface:

```c++
struct drawable {
  template <typename T>
  drawable(T x) : poly_{x} { }

  void draw(std::ostream& out) const
  { poly_.virtual_("draw"_s)(poly_.get(), out); }

private:
  te::poly<Drawable> poly_;
};
```

Let's break this down. First, we define a member `poly_` that is a polymorphic
container for anything that models the `Drawable` concept:

```c++
te::poly<Drawable> poly_;
```

Then, we define a constructor that allows constructing this container from an
arbitrary type `T`:

```c++
template <typename T>
drawable(T x) : poly_{x} { }
```

The unsaid assumption here is that `T` actually models the `Drawable` concept.
Indeed, when you create a `te::poly` from an object of type `T`, __Type Erased__
will go and look at the concept map defined for `Drawable` and `T`, if any. If
there's no such concept map, the library will report that we're trying to create
a `te::poly` from a type that does not support it, and your program won't compile.

Finally, the strangest and most important part of the definition above is that
of the `draw` method:

```c++
void draw(std::ostream& out) const
{ poly_.virtual_("draw"_s)(poly_.get(), out); }
```

What happens here is that when `.draw` is called on our `drawable` object,
we'll actually perform a dynamic dispatch to the implementation of the `"draw"`
function for the object currently stored in the `te::poly`, and call that.
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

Strictly speaking, you don't need to wrap `te::poly`, but doing so puts a nice
barrier between __Type Erased__ and the rest of your code, which never has to
worry about how your polymorphic layer is implemented. Also, we largely ignored
how `te::poly` was implemented in the above definition. However, `te::poly` is
a very powerful policy-based container for polymorphic objects that can be
customized to one's needs for performance. Creating a `drawable` wrapper makes
it easy to tweak the implementation strategy used by `te::poly` for performance
without impacting the rest of your code.


### Customizing the polymorphic storage
The first aspect that can be customized in a `te::poly` is the way the object
is stored inside the container. By default, we simply store a pointer to the
actual object, like one would do with inheritance-based polymorphism. However,
this is often not the most efficient implementation, and that's why `te::poly`
allows customizing it. To do so, simply pass a storage policy to `te::poly`.
For example, let's define our `drawable` wrapper so that it tries to store
objects up to `16` bytes on the stack, but then falls back to the heap if the
object is larger:

```c++
struct drawable {
  template <typename T>
  drawable(T x) : poly_{x} { }

  void draw(std::ostream& out) const
  { poly_.virtual_("draw"_s)(poly_.get(), out); }

private:
  te::poly<Drawable, te::sbo_storage<16>> poly_;
  //                 ^^^^^^^^^^^^^^^^^^^ storage policy
};
```

Notice that nothing except the policy changed in our definition. That is one
very important tenet of __Type Erased__; these policies are implementation
details, and they should not change the way you write your code. With the
above definition, you can now create `drawable`s just like you did before,
and no allocation will happen when the object you're creating the `drawable`
from fits in `16` bytes. When it does not fit, however, `te::poly` will allocate
a large enough buffer on the heap.

Let's say you actually never want to do an allocation. No problem, just change
the policy to `te::local_storage<16>`. If you try to construct a `drawable`
from an object that's too large to fit in the stack-allocated storage, your
program won't compile. Not only are we saving an allocation, but we're also
saving a pointer indirection every time we access the polymorphic object if
we compare to the traditional inheritance-based approach. By tweaking these
(important) implementation details for you specific use case, you can make
your program much more efficient than with classic inheritance.

Other storage policies are also provided, like `te::remote_storage` and
`te::non_owning_storage`. `te::remote_storage` is the default one, which
always stores a pointer to a heap-allocated object. `te::non_owning_storage`
stores a pointer to an object that already exists, without worrying about
the lifetime of that object. It allows implementing non-owning polymorphic
views over objects, which is very useful.

Custom storage policies can also be created quite easily. See `<te/storage.hpp>`
for details.


### Customizing the dynamic dispatch
When we introduced `te::poly`, we mentioned that it had two roles; the first
is to store the polymorphic object, and the second one is to perform dynamic
dispatch. Just like the storage can be customized, the way dynamic dispatching
is performed can also be customized using policies. For example, let's define
our `drawable` wrapper so that instead of storing a pointer to the vtable, it
instead stores the vtable in the `drawable` object itself. This way, we'll
avoid one indirection each time we access a virtual function:

TODO: This section needs to be finished up. Dynamic dispatching policies work,
      but they still need to be polished a lot more before they're sufficiently
      easy to use and flexible.


### Defaulted concept maps
When defining a concept, it is often the case that one can provide a default
definition for at least some functions associated to the concept. For example,
by default, it would probably make sense to use a member function named `draw`
(if any) to implement the abstract `"draw"` method of the `Drawable` concept.
For this, one can use `te::default_concept_map`:

```c++
template <typename T>
auto te::default_concept_map<Drawable, T> = te::make_default_concept_map<Drawable, T>(
  "draw"_s = [](auto const& t, std::ostream& out) { t.draw(out); }
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
auto te::concept_map<Drawable, Circle> = te::make_concept_map<Drawable, Circle>(
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
auto te::concept_map<Drawable, std::vector<T>, std::void_t<decltype(
  std::cout << std::declval<T>()
)>> = te::make_concept_map<Drawable, std::vector<T>>(
  "draw"_s = [](std::vector<T> const& v, std::ostream& out) {
    for (auto const& x : v)
      out << x << ' ';
  }
);

f(std::vector<int>{1, 2, 3}) // prints "1 2 3 "
```

> Notice how we do not have to modify `std::vector` at all. How could we do
> this with classic polymorphism? Answer: no can do.


<!-- Links -->
[badge.Travis]: https://travis-ci.org/ldionne/te.svg?branch=master
[Boost.Hana]: https://github.com/boostorg/hana
[C++0x Concept Maps]: https://isocpp.org/wiki/faq/cpp0x-concepts-history#cpp0x-concept-maps
[CallableTraits]: https://github.com/badair/callable_traits
[Google Benchmark]: https://github.com/google/benchmark
[libawful]: https://github.com/ldionne/libawful
