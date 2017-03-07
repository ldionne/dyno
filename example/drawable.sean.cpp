// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <cassert>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>


//
// Example taken from Sean Parent's talk "Inheritance Is The Base Class of Evil"
// at GoingNative 2013. See https://goo.gl/svMkvk for video.
//

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
void draw(my_class_t /*self*/, std::ostream& out)
{ out << "my_class_t" << std::endl; }

template <typename Object>
void draw(document_t<Object> const& self, std::ostream& out) {
  out << "<document>" << std::endl;
  for (auto const& x : self)
    draw(x, out);
  out << "</document>" << std::endl;
}

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
    virtual void draw_(std::ostream& out) const override final
    { draw(data_, out); }
    T data_;
  };

  std::shared_ptr<concept_t const> self_;
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
