// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <te.hpp>

#include <cassert>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>
using namespace te::literals;


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



struct Drawable : decltype(te::requires(
  "draw"_s = te::function<void (te::T const&, std::ostream&)>
)) { };

class object_t {
public:
  template <typename T>
  object_t(T x)
    : vtable_{
      te::complete_concept_map<Drawable, T>(te::make_concept_map(
        "draw"_s = [](T const& self, std::ostream& out) { draw(self, out); }
      ))
    }
    , self_{std::make_shared<T>(std::move(x))}
  { }

  friend void draw(object_t const& x, std::ostream& out) {
    x.vtable_["draw"_s](x.self_.get(), out);
  }

private:
  te::remote_vtable<te::local_vtable<Drawable>> vtable_;
  std::shared_ptr<void const> self_;
};


int main() {
  history_t<document_t<object_t>> h{1};
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
