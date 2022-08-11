#include "matrix.h"

#include <exception>
#include <iostream>

namespace s21 {

Matrix::Matrix() { create_matrix(3, 3); }

Matrix::Matrix(int rows, int cols) {
  if (rows <= 0 || cols <= 0) {
    throw std::invalid_argument("Matrix size must be greater than 0");
  } else {
    create_matrix(rows, cols);
  }
}

Matrix::Matrix(const Matrix& other) {
  _rows = other._rows;
  _cols = other._cols;
  create_matrix(_rows, _cols);
  for (int i = 0; i < _rows; i++)
    for (int j = 0; j < _cols; j++) _matrix[i][j] = other._matrix[i][j];
}

Matrix::Matrix(Matrix&& other) : _rows(0), _cols(0), _matrix(nullptr) {
  std::swap(_rows, other._rows);
  std::swap(_cols, other._cols);
  std::swap(_matrix, other._matrix);
}

void Matrix::create_matrix(int rows, int cols) {
  _rows = rows;
  _cols = cols;
  _matrix = new double*[rows];
  for (int i = 0; i < rows; i++) _matrix[i] = new double[cols]{};
}

// void Matrix::printMatrix()
// {
//    for (int i = 0; i < _rows; i++) {
//     for (int j = 0; j < _cols; j++)
//         std::cout << _matrix[i][j] << " ";
//         std::cout << std::endl;
//    }
//    std::cout << _cols << _rows << std::endl;
// }

void Matrix::fill_matrix(const double a1[]) {
  int k = 0;
  for (int i = 0; i < _rows; i++) {
    for (int j = 0; j < _cols; j++) {
      _matrix[i][j] = a1[k++];
    }
  }
}

Matrix::~Matrix() {
  if (_matrix) free_matrix();
}

void Matrix::free_matrix() {
  for (int i = 0; i < _rows; i++) {
    delete[] _matrix[i];
  }
  delete[] _matrix;
}

bool Matrix::eq_matrix(const Matrix& other) {
  bool res = true;
  if (_rows != other._rows || _cols != other._cols) {
    res = false;
  } else {
    for (int i = 0; i < _rows && res != false; i++)
      for (int j = 0; j < _cols && res != false; j++) {
        if (_matrix[i][j] != other._matrix[i][j]) res = false;
      }
  }
  return res;
}

void Matrix::sum_matrix(const Matrix& other) {
  if (_rows != other._rows || _cols != other._cols) {
    throw std::out_of_range("Incorrect input, matrices should have the same size");
  }
  for (int i = 0; i < _rows; i++)
    for (int j = 0; j < _cols; j++) _matrix[i][j] += other._matrix[i][j];
}

void Matrix::sub_matrix(const Matrix& other) {
  if (_rows != other._rows || _cols != other._cols) {
    throw std::out_of_range("Incorrect input, matrices should have the same size");
  }
  for (int i = 0; i < _rows; i++)
    for (int j = 0; j < _cols; j++) _matrix[i][j] -= other._matrix[i][j];
}

void Matrix::mul_number(const double num) {
  for (int i = 0; i < _rows; i++)
    for (int j = 0; j < _cols; j++) _matrix[i][j] *= num;
}

void Matrix::mul_matrix(const Matrix& other) {
  if (_cols != other._rows) {
    throw std::out_of_range("Invalid input, incorrect matrix size");
  }
  Matrix temp(_rows, other._cols);
  for (int i = 0; i < _rows; i++)
    for (int j = 0; j < other._cols; j++)
      for (int k = 0; k < _cols; k++) temp._matrix[i][j] += _matrix[i][k] * other._matrix[k][j];
  *this = temp;
}

Matrix Matrix::transpose() {
  Matrix temp1(_cols, _rows);
  for (int i = 0; i < temp1._rows; i++)
    for (int j = 0; j < temp1._cols; j++) temp1._matrix[i][j] = _matrix[j][i];
  return temp1;
}

Matrix Matrix::new_matrix(int j, int i) {
  Matrix temp2(_rows - 1, _cols - 1);
  int k, krows, l, lcol;
  for (k = 0, krows = 0; k < temp2._rows; k++, krows++) {
    if (krows == j) krows++;
    for (l = 0, lcol = 0; l < temp2._cols; l++, lcol++) {
      if (lcol == i) lcol++;
      temp2._matrix[k][l] = _matrix[krows][lcol];
    }
  }
  return temp2;
}

double Matrix::determinant() {
  double det = 0;
  if (_rows != _cols) {
    throw std::out_of_range("Invalid input, incorrect matrix size");
  }
  if (_rows == 1) {
    det = _matrix[0][0];
  } else if (_rows == 2) {
    det = _matrix[0][0] * _matrix[1][1] - _matrix[0][1] * _matrix[1][0];
  } else {
    for (int i = 0; i < _cols; i++) {
      Matrix temp = new_matrix(0, i);
      det += (pow(-1, i)) * _matrix[0][i] * temp.determinant();
    }
  }
  return det;
}

Matrix Matrix::calc_complements() {
  if (_rows != _cols) throw std::out_of_range("Invalid input, incorrect matrix size");
  Matrix res(_rows, _cols);
  for (int i = 0; i < _rows; i++)
    for (int j = 0; j < _cols; j++) {
      Matrix temp3 = new_matrix(i, j);
      res._matrix[i][j] = (pow(-1, i + j)) * temp3.determinant();
    }
  return res;
}

Matrix Matrix::inverse_matrix() {
  double det = determinant();
  if (_rows != _cols || det == 0) throw std::out_of_range("Invalid input, incorrect matrix size");
  Matrix temp4 = calc_complements();
  Matrix res = temp4.transpose();
  res.mul_number(1.0 / det);
  return res;
}

Matrix Matrix::operator+(const Matrix& other) {
  Matrix temp = *this;
  temp.sum_matrix(other);
  return temp;
}

Matrix Matrix::operator-(const Matrix& other) {
  Matrix temp = *this;
  temp.sub_matrix(other);
  return temp;
}

Matrix Matrix::operator*(const Matrix& other) {
  Matrix temp = *this;
  temp.mul_matrix(other);
  return temp;
}

Matrix operator*(const Matrix& other, const double num) {
  Matrix temp = other;
  temp.mul_number(num);
  return temp;
}

Matrix operator*(const double num, const Matrix& other) {
  Matrix temp = other;
  temp.mul_number(num);
  return temp;
}

bool Matrix::operator==(const Matrix& other) { return eq_matrix(other); }

Matrix& Matrix::operator+=(const Matrix& other) {
  sum_matrix(other);
  return *this;
}

Matrix& Matrix::operator-=(const Matrix& other) {
  sub_matrix(other);
  return *this;
}

Matrix& Matrix::operator*=(const Matrix& other) {
  mul_matrix(other);
  return *this;
}

Matrix& Matrix::operator*=(const double num) {
  mul_number(num);
  return *this;
}

Matrix& Matrix::operator=(const Matrix& other) {
  if (this != &other) {
    free_matrix();
    _rows = other._rows;
    _cols = other._cols;
    create_matrix(_rows, _cols);
    for (int i = 0; i < _rows; i++)
      for (int j = 0; j < _cols; j++) _matrix[i][j] = other._matrix[i][j];
  }
  return *this;
}

double& Matrix::operator()(int row, int col) const {
  if (row < 0 || row >= _rows || col < 0 || col >= _cols) {
    throw std::out_of_range("Incorrect index");
  }
  return _matrix[row][col];
}

int Matrix::getRows() const { return _rows; }

int Matrix::getCols() const { return _cols; }

void Matrix::setRows(int rows) { _rows = rows; }

void Matrix::setCols(int cols) { _cols = cols; }

}  // namespace s21
