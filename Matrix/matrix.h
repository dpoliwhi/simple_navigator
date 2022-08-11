#pragma once

#include <cmath>
#include <iostream>

namespace s21 {

class Matrix {
  friend Matrix operator*(const Matrix& other, const double num);
  friend Matrix operator*(const double num, const Matrix& other);

 private:
  int _rows, _cols;
  double** _matrix;
  void create_matrix(int rows, int cols);
  void free_matrix();
  Matrix new_matrix(int j, int i);

 public:
  // constructors & destructor
  Matrix();
  Matrix(int rows, int cols);
  Matrix(const Matrix& other);
  Matrix(Matrix&& other);
  ~Matrix();

  // operators overloads
  Matrix operator+(const Matrix& other);
  Matrix operator-(const Matrix& other);
  Matrix operator*(const Matrix& other);
  bool operator==(const Matrix& other);
  Matrix& operator+=(const Matrix& other);
  Matrix& operator-=(const Matrix& other);
  Matrix& operator*=(const Matrix& other);
  Matrix& operator*=(const double num);
  Matrix& operator=(const Matrix& other);
  double& operator()(int row, int col) const;

  // public methods
  bool eq_matrix(const Matrix& other);
  void sum_matrix(const Matrix& other);
  void sub_matrix(const Matrix& other);
  void mul_number(const double num);
  void mul_matrix(const Matrix& other);
  Matrix transpose();
  Matrix calc_complements();
  double determinant();
  Matrix inverse_matrix();

  // accessors and mutators
  int getRows() const;
  int getCols() const;
  void setRows(int rows);
  void setCols(int cols);

  // void printMatrix();
  void fill_matrix(const double a1[]);
};
}  // namespace s21
