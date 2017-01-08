// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <iterator>
#include <memory>
#include <vector>


template <typename Value, typename Reference>
struct any_iterator_base {
  virtual void increment() = 0;
  virtual Reference dereference() = 0;
  virtual bool equal(any_iterator_base const&) const = 0;
  // etc...
};

template <typename Iterator, typename Value, typename Reference>
struct any_iterator_model : any_iterator_base<Value, Reference> {
  explicit any_iterator_model(Iterator it)
    : it_(it)
  { }

  virtual void increment() override final {
    ++it_;
  }

  virtual Reference dereference() override final {
    return *it_;
  }

  virtual bool equal(any_iterator_base<Value, Reference> const& other_) const override final {
    any_iterator_model const& other = static_cast<any_iterator_model const&>(other_);
    return it_ == other.it_;
  }

private:
  Iterator it_;
};

template <typename Value, typename Reference = Value&>
struct any_iterator {
  template <typename Iterator>
  explicit any_iterator(Iterator it)
    : it_(std::make_unique<any_iterator_model<Iterator, Value, Reference>>(it))
  { }

  friend bool operator==(any_iterator const& a, any_iterator const& b) {
    return a.it_->equal(*b.it_);
  }

  friend bool operator!=(any_iterator const& a, any_iterator const& b) {
    return !(a == b);
  }

  any_iterator& operator++() {
    it_->increment();
    return *this;
  }

  Reference operator*() {
    return it_->dereference();
  }

private:
  std::unique_ptr<any_iterator_base<Value, Reference>> it_;
};

volatile long long COUNTER = 100000000;

int main() {
  using Iterator = any_iterator<int>;
  std::vector<int> input; input.resize(COUNTER);
  std::vector<int> result; result.reserve(COUNTER);

  Iterator first{input.begin()}, last{input.end()};
  for (; first != last; ++first) {
    result.push_back(*first);
  }
}
