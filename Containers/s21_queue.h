#pragma once

#include <iostream>
#include <string>

namespace s21 {
template <class T>
class queue {
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
  void Destroy_stack();
  void Reserve_more_capacity(size_type size);

 public:
  // constructors
  queue();
  explicit queue(size_type n);
  explicit queue(std::initializer_list<value_type> const &items);
  queue(const queue &q);
  queue(queue &&q);
  ~queue();

  //  operators
  queue<value_type> &operator=(queue<value_type> &&q);
  queue<value_type> &operator=(const queue<T> &q);

  // element acces
  const_reference front();
  const_reference back();

  // capacity
  bool empty();
  size_type size();

  // modifiers
  void push(const_reference value);
  void pop();
  void swap(queue &other);

  // bonus
  void emplace_back() {}
  template <class TYPE, class... Args>
  void emplace_back(TYPE data, Args... args);
};

}  // namespace s21

#include "s21_queue.inl"
