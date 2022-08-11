namespace s21 {

// constructors
template <class T>
stack<T>::stack() : _size(0), _capacity(0), _stackptr(nullptr) {}

template <class T>
stack<T>::stack(size_type n) : _size(0), _capacity(n), _stackptr(n ? new value_type[n] : nullptr) {}

template <class T>
stack<T>::stack(std::initializer_list<value_type> const &items) : _size(0), _capacity(0) {
  _stackptr = new value_type[items.size()];
  int i = 0;
  for (auto it = items.begin(); it != items.end(); it++) _stackptr[i++] = *it;
  _size = items.size();
  _capacity = items.size();
}

template <class T>
stack<T>::stack(const stack &s) : _size(s._size), _capacity(s._capacity) {
  _stackptr = new value_type[s._capacity];
  for (size_type i = 0; i < _size; ++i) _stackptr[i] = s._stackptr[i];
}

template <class T>
stack<T>::stack(stack &&s) : _size(0), _capacity(0), _stackptr(nullptr) {
  std::swap(_size, s._size);
  std::swap(_capacity, s._capacity);
  std::swap(_stackptr, s._stackptr);
}

template <class T>
void stack<T>::Reserve_more_capacity(size_type size) {
  value_type *buff = new value_type[size];
  for (size_type i = 0; i < _size; ++i) buff[i] = std::move(_stackptr[i]);
  delete[] _stackptr;
  _stackptr = buff;
  _capacity = size;
}

template <class T>
stack<T>::~stack() {
  delete[] _stackptr;
}

template <class T>
void stack<T>::Destroy_stack() {
  _size = 0;
  _capacity = 0;
  _stackptr = nullptr;
}

// overload operators
template <class T>
stack<T> &stack<T>::operator=(stack<T> &&s) {
  if (this == &s) {
    return *this;
  } else {
    Destroy_stack();
    std::swap(_size, s._size);
    std::swap(_capacity, s._capacity);
    std::swap(_stackptr, s._stackptr);
    return *this;
  }
}

template <class T>
stack<T> &stack<T>::operator=(const stack<T> &s) {
  if (this == &s) {
    return *this;
  } else {
    for (size_type i = 0; i < s._size; ++i) push(s._stackptr[i]);
    _size = s._size;
    return *this;
  }
}

// main methods
template <class T>
void stack<T>::swap(stack &other) {
  if (!empty() && !other.empty()) {
    std::swap(_size, other._size);
    std::swap(_capacity, other._capacity);
    std::swap(_stackptr, other._stackptr);
  }
}

template <class T>
size_t stack<T>::size() {
  return _size;
}

template <class T>
void stack<T>::push(const_reference value) {
  if (_size >= _capacity) {
    Reserve_more_capacity(_size + 2);
  }
  _stackptr[_size++] = value;
}

template <class T>
const T &stack<T>::top() {
  if (_size == 0) {
    throw std::invalid_argument("Nothihg to top");
  } else {
    return _stackptr[_size - 1];
  }
}

template <class T>
bool stack<T>::empty() {
  if (_size) {
    return false;
  } else {
    return true;
  }
}

template <class T>
void stack<T>::pop() {
  if (_size == 0) {
    throw std::invalid_argument("Nothihg to pop");
  } else {
    _size--;
  }
}

template <class T>
template <class TYPE, class... Args>
void stack<T>::emplace_front(TYPE data, Args... args) {
  push(data);
  emplace_front(args...);
}

}  // namespace s21

