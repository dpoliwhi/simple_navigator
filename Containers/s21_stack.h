#pragma once

#include <iostream>

namespace s21 {

template <class T>
class stack {
 private:
  size_t _size;
  size_t _capacity;
  T *_stackptr;

 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

 private:
  void Reserve_more_capacity(size_type size);
  void Destroy_stack();

 public:
  // constructors
  stack();
  explicit stack(size_type n);
  explicit stack(std::initializer_list<value_type> const &items);
  stack(const stack &s);
  stack(stack &&s);
  ~stack();

  // overload operators
  stack<value_type> &operator=(stack<value_type> &&s);
  stack<value_type> &operator=(const stack<T> &s);

  // main methods
  const_reference top();
  bool empty();
  size_type size();
  void push(const_reference value);
  void pop();
  void swap(stack &other);

  // bonus
  void emplace_front() {}
  template <class TYPE, class... Args>
  void emplace_front(TYPE data, Args... args);
};
}  // namespace s21

#include "s21_stack.inl"
