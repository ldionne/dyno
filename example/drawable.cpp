// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <te.hpp>
#include <te/experimental/vtable.hpp>

#include <cassert>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>


template <typename Object>
using document_t = std::vector<Object>;

template <typename Document>
using history_t = std::vector<Document>;

template <typename T>
void draw(T const& t, std::ostream& out)
{ out << t << std::endl; }

template <typename Document>
void commit(history_t<Document>& x) {
  assert(!x.empty());
  x.push_back(x.back());
}

template <typename Document>
void undo(history_t<Document>& x) {
  assert(!x.empty());
  x.pop_back();
}

template <typename Document>
Document& current(history_t<Document>& x) {
  assert(!x.empty());
  return x.back();
}

struct my_class_t { };
void draw(my_class_t self, std::ostream& out)
{ out << "my_class_t" << std::endl; }

template <typename Object>
void draw(document_t<Object> const& self, std::ostream& out) {
  out << "<document>" << std::endl;
  for (auto const& x : self)
    draw(x, out);
  out << "</document>" << std::endl;
}

template <typename Object>
void run_main() {
  history_t<document_t<Object>> h{1};
  current(h).emplace_back(0);
  current(h).emplace_back(std::string{"Hello!"});

  draw(current(h), std::cout);
  std::cout << "-------------------" << std::endl;

  commit(h);

  current(h).emplace_back(current(h));
  current(h).emplace_back(my_class_t{});
  current(h)[1] = std::string{"World"};

  draw(current(h), std::cout);
  std::cout << "-------------------" << std::endl;

  undo(h);

  draw(current(h), std::cout);
}

namespace with_te {
  using namespace te::literals;

  struct Drawable : decltype(te::requires(
    "draw"_s = te::function<void (te::T const&, std::ostream&)>
  )) { };

  template <typename T>
  te::vtable<Drawable> const vtable{te::make_concept_map<Drawable, T>(
    "draw"_s = [](T const& self, std::ostream& out) { draw(self, out); }
  )};

  class object_t {
  public:
    template <typename T>
    object_t(T x)
      : self_{std::make_shared<T>(std::move(x))}
      , vtable_{&vtable<T>}
    { }

    friend void draw(object_t const& x, std::ostream& out) {
      (*x.vtable_)["draw"_s](x.self_.get(), out);
    }

  private:
    std::shared_ptr<void const> self_;
    te::vtable<Drawable> const* vtable_;
  };
} // end namespace with_te

namespace with_te_experimental {
  using namespace te::literals;

  struct Drawable : decltype(te::requires(
    "draw"_s = te::function<void (te::T const&, std::ostream&)>
  )) { };

  template <typename T>
  auto const Drawable_concept_map = te::make_concept_map<Drawable, T>(
    "draw"_s = [](T const& self, std::ostream& out) { draw(self, out); }
  );

  template <typename T>
  struct make_Drawable_concept_map {
    auto operator()() const { return Drawable_concept_map<T>; }
  };

  class object_t {
  public:
    template <typename T>
    object_t(T x)
      : self_{std::make_shared<T>(std::move(x))}
      , vptr_{make_Drawable_concept_map<T>{}}
    { }

    friend void draw(object_t const& x, std::ostream& out) {
      x.vptr_["draw"_s](x.self_.get(), out);
    }

  private:
    std::shared_ptr<void const> self_;
    te::experimental::vtable<Drawable> vptr_;
  };
} // end namespace with_te_experimental

namespace with_sean {
  //
  // Example taken from Sean Parent's talk "Inheritance Is The Base Class of Evil"
  // at GoingNative 2013. See https://goo.gl/svMkvk for video.
  //
  class object_t {
  public:
    template <typename T>
    object_t(T x)
      : self_{std::make_shared<model<T>>(std::move(x))}
    { }

    friend void draw(object_t const& x, std::ostream& out)
    { x.self_->draw_(out); }

  private:
    struct concept_t {
      virtual ~concept_t() = default;
      virtual void draw_(std::ostream&) const = 0;
    };

    template <typename T>
    struct model : concept_t {
      explicit model(T x) : data_(std::move(x)) { }
      void draw_(std::ostream& out) const override final
      { draw(data_, out); }
      T data_;
    };

    std::shared_ptr<concept_t const> self_;
  };
} // end namespace with_sean


int main() {
  run_main<with_sean::object_t>();
  run_main<with_te::object_t>();
  run_main<with_te_experimental::object_t>();
}
