#include <cppx/meta>
#include <cppx/compiler>


using namespace cppx::meta;

#if 0
$class object {
  constexpr {
    if (!$object.has_destructor())
      -> { ~object() { } }
  }
}

$class movable : object {
  constexpr {
    bool move = false;
    for... (auto ctor : $movable.constructors()) {
      if (ctor.is_move())
        move = true;
    }
    if (!move) {
      -> { movable(movable&&) = default; }
      -> { movable& operator=(movable&&) = default; }
    }
  }
}


$class copyable : movable {
  constexpr {
    bool copy = false;
    for... (auto ctor : $movable.constructors()) {
      if (ctor.is_copy())
        copy = true;
    }
    if (!copy) {
      -> { copyable(const copyable&) = default; }
      -> { copyable& operator=(const copyable&) = default; }
    }
  }
}


$class basic_value : copyable {
  constexpr {
    for... (auto var : $basic_value.member_variables()) {
      compiler.require(!var.is_protected(),
                        "protected member of a value type");
      var.make_private();
    }
    bool has_default = false;
    for... (auto fn : $basic_value.member_functions()) {
      // compiler.debug(fn);

      if (fn.is_default_constructor())
        has_default = true;

      compiler.require(!fn.is_protected(), "protected member function of a value type");
      compiler.require(!fn.is_virtual(), "virtual member function of a value type");
      if (fn.is_destructor())
        compiler.require(fn.is_public(), "inaccessible destructor");

      // Make the constructor public.
      fn.make_public();
    }

    if (!has_default)
      -> { basic_value() = default; }
  }
}


basic_value date {
  int y;
  int m;
  int d;

  // virtual void f() { }
};

#endif

struct RangeInterface {
  void begin();
  void end();
  void cbegin() const;
  void cend() const;
};


// auto methods = std::make_tuple(
//   "begin"_s = dyno::function<void (dyno::T&)>,
//   "end"_s = dyno::function<void (dyno::T&)>,
//   "cbegin"_s = dyno::function<void (dyno::T const&)>,
//   "cend"_s = dyno::function<void (dyno::T const&)>
// );

$class Range {
  constexpr {
    for... (auto method : $RangeInterface.member_functions()) {
      compiler.require(method.is_public(), "non-public method in an interface");
      // -> {  }
    }
  }
}

Range numeric {
  int x;
};

int main() {
  numeric foo{3};
  foo.begin();
  compiler.debug($numeric);
}
