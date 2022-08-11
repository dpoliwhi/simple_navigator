namespace s21 {

// constructors
template <typename T>
queue<T>::queue() : _size(0), _capacity(0), _stackptr(nullptr) {}

template <typename T>
queue<T>::queue(size_type n) : _size(0), _capacity(n), _stackptr(n ? new value_type[n] : nullptr) {}

template <typename T>
queue<T>::queue(std::initializer_list<value_type> const &items) : _size(0), _capacity(0) {
  _stackptr = new value_type[items.size()];
  int i = 0;
  for (auto it = items.begin(); it != items.end(); it++) _stackptr[i++] = *it;
  _size = items.size();
  _capacity = items.size();
}

template <typename T>
queue<T>::queue(const queue &q) : _size(q._size), _capacity(q._capacity) {
  _stackptr = new value_type[q._capacity];
  for (size_type i = 0; i < _size; ++i) _stackptr[i] = q._stackptr[i];
}

template <typename T>
queue<T>::queue(queue &&q) : _size(0), _capacity(0), _stackptr(nullptr) {
  std::swap(_size, q._size);
  std::swap(_capacity, q._capacity);
  std::swap(_stackptr, q._stackptr);
}

template <typename T>
queue<T>::~queue() {
  delete[] _stackptr;
}

template <typename T>
void queue<T>::Destroy_stack() {
  _size = 0;
  _capacity = 0;
  _stackptr = nullptr;
}

template <typename T>
void queue<T>::Reserve_more_capacity(size_type size) {
  value_type *buff = new value_type[size];
  for (size_type i = 0; i < _size; ++i) buff[i] = std::move(_stackptr[i]);
  delete[] _stackptr;
  _stackptr = buff;
  _capacity = size;
}

// overload operators
template <typename T>
queue<T> &queue<T>::operator=(queue<T> &&q) {
  if (this == &q) {
    return *this;
  } else {
    Destroy_stack();
    std::swap(_size, q._size);
    std::swap(_capacity, q._capacity);
    std::swap(_stackptr, q._stackptr);
    return *this;
  }
}

template <typename T>
queue<T> &queue<T>::operator=(const queue<T> &q) {
  if (this == &q) {
    return *this;
  } else {
    for (size_type i = 0; i < q._size; ++i) push(q._stackptr[i]);
    _size = q._size;
    return *this;
  }
}

template <typename T>
const T &queue<T>::back() {
  if (_size == 0) {
    throw std::invalid_argument("No items available");
  } else {
    return _stackptr[_size - 1];
  }
}

template <typename T>
const T &queue<T>::front() {
  if (_size == 0) {
    throw std::invalid_argument("No items available");
  } else {
    return _stackptr[0];
  }
}

template <typename T>
bool queue<T>::empty() {
  if (_size) {
    return false;
  } else {
    return true;
  }
}

template <typename T>
size_t queue<T>::size() {
  return _size;
}

template <typename T>
void queue<T>::push(const_reference value) {
  if (_size >= _capacity) {
    Reserve_more_capacity(_size + 2);
  }
  _stackptr[_size++] = value;
}

template <typename T>
void queue<T>::pop() {
  if (_size == 0) {
    throw std::invalid_argument("Nothihg to pop");
  } else {
    T *q2 = new T[_size - 1];
    _size--;
    for (size_t i = 0; i < _size; i++) q2[i] = _stackptr[i + 1];
    delete[] _stackptr;
    _capacity = _size;
    _stackptr = q2;
    q2 = nullptr;
  }
}

template <typename T>
void queue<T>::swap(queue &other) {
  if (!empty() && !other.empty()) {
    std::swap(_size, other._size);
    std::swap(_capacity, other._capacity);
    std::swap(_stackptr, other._stackptr);
  }
}

template <class T>
template <class TYPE, class... Args>
void queue<T>::emplace_back(TYPE data, Args... args) {
  push(data);
  emplace_back(args...);
}

}  // namespace s21
