#pragma once

#include <exception>
#include <iostream>
#include <string>

class Matrix {
 private:
  int _rows = 0;
  int _columns = 0;
  double** _matrix = nullptr;
  void SetZeros();

 public:
  // constructors
  Matrix() = default;
  Matrix(int rows, int columns);
  Matrix(const Matrix& other);
  // move constructor
  Matrix(Matrix&& other);

  // destructors
  ~Matrix();

  // accessors
  int row();
  int col();
  // mutators
  void EditRow(int value);
  void EditColumn(int value);

  // get matrix element
  double* operator[](int i);
  double& operator()(int i, int j);
  bool IsNull();

  // ariphmetic
  Matrix operator+(const Matrix& other);
  Matrix operator-(const Matrix& other);
  Matrix operator*(const Matrix& other);
  Matrix operator*(const double number);
  double determinant();
  Matrix transpose();
  Matrix calc_complements();
  void sub_matrix(const Matrix& other);
  void sum_matrix(const Matrix& other);
  void mul_number(const double num);
  void mul_matrix(const Matrix& other);
  Matrix inverse_matrix();

  // equating
  Matrix& operator=(const Matrix& other);

  // equating && ariphmetic
  Matrix& operator+=(const Matrix& other);
  Matrix& operator-=(const Matrix& other);
  Matrix& operator*=(const Matrix& other);
  Matrix& operator*=(const double number);

  // comparing
  bool operator==(const Matrix& other);
  bool eq_matrix(const Matrix& other);

  // auxiliary

  void GetMinor(Matrix src, int rows, int column);
  void FillRandom(double fMin, double fMax);
  void show();
  Matrix Concatenation(Matrix& other);
  Matrix& SetIdentityMatrix();

 private:
  void allocate_mem(int rows, int columns);
  bool IsNormalMatrix();
};
