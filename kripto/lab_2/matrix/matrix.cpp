#include <cmath>
#include <iostream>

#include "matrix_oop.h"

// заполняет матрицу нулями
void Matrix::allocate_mem(int rows, int columns) {
  _matrix = new double*[rows];
  for (int i = 0; i < rows; i++) {
    _matrix[i] = new double[columns];
  }
}

void Matrix::SetZeros() {
  if (this->IsNormalMatrix()) {
    for (int i = 0; i < _rows; i++) {
      for (int j = 0; j < _columns; j++) {
        _matrix[i][j] = 0;
      }
    }
  }
}

// конструктор матрицы по рядам и столбцам
Matrix::Matrix(int rows, int columns) : _rows(rows), _columns(columns) {
  if (rows <= 0 || columns <= 0) {
    throw std::invalid_argument(
        "Matrix construct: cannot initiaize a _matrix with negative number "
        "of rows or columns");
  } else {
    this->allocate_mem(rows, columns);
    this->SetZeros();
  }
}

// конструктор копирования
Matrix::Matrix(const Matrix& other) {
  if (this != &other) {
    _rows = other._rows;
    _columns = other._columns;
    this->allocate_mem(other._rows, other._columns);
    for (int i = 0; i < _rows; i++) {
      for (int j = 0; j < _columns; j++) {
        _matrix[i][j] = other._matrix[i][j];
      }
    }
  }
}

// конструктор перемещения
Matrix::Matrix(Matrix&& other) {
  if (this != &other) {
    std::swap(_rows, other._rows);
    std::swap(_columns, other._columns);
    std::swap(_matrix, other._matrix);
  }
}

// деструктор
Matrix::~Matrix() {
  if (_matrix != nullptr) {
    for (int i = 0; i < _rows; i++) {
      delete _matrix[i];
    }
    delete _matrix;
  }
  _matrix = nullptr;
  _rows = 0;
  _columns = 0;
}

Matrix& Matrix::operator=(const Matrix& other) {
  if (this != &other) {
    this->~Matrix();
    _rows = other._rows;
    _columns = other._columns;
    allocate_mem(_rows, _columns);
    for (int i = 0; i < _rows; i++) {
      for (int j = 0; j < _columns; j++) {
        _matrix[i][j] = other._matrix[i][j];
      }
    }
  }
  return *this;
}

// getters && setters

double& Matrix::operator()(int i, int j) {
  if (i >= _rows || j >= _columns) {
    throw std::out_of_range("(): index is out of range");
  } else {
    return _matrix[i][j];
  }
}

// accessors
int Matrix::row() { return _rows; }

int Matrix::col() { return _columns; }

// mutators
void Matrix::EditRow(int value) {
  if (value > 0) {
    this->~Matrix();
    _rows = value;
    this->allocate_mem(_rows, _columns);
    this->SetZeros();
  } else {
    throw std::invalid_argument("EditRow: row value less or equal to zero");
  }
}

void Matrix::EditColumn(int value) {
  if (value > 0) {
    this->~Matrix();
    _columns = value;
    this->allocate_mem(_rows, _columns);
    this->SetZeros();
  } else {
    throw std::invalid_argument(
        "EditColumn: column value less or equal to zero");
  }
}

// operators

Matrix Matrix::operator+(const Matrix& other) {
  Matrix res = *this;
  res.sum_matrix(other);
  return res;
}

Matrix Matrix::operator-(const Matrix& other) {
  Matrix res = *this;
  res.sub_matrix(other);
  return res;
}

Matrix& Matrix::operator-=(const Matrix& other) {
  this->sub_matrix(other);
  return *this;
}

Matrix& Matrix::operator+=(const Matrix& other) {
  this->sum_matrix(other);
  return *this;
}

Matrix Matrix::operator*(const Matrix& other) {
  Matrix res = *this;
  res.mul_matrix(other);
  return res;
}

Matrix Matrix::operator*(const double number) {
  Matrix res = *this;
  res.mul_number(number);
  return res;
}

Matrix& Matrix::operator*=(const Matrix& other) {
  this->mul_matrix(other);
  return *this;
}

Matrix& Matrix::operator*=(const double number) {
  this->mul_number(number);
  return *this;
}

bool Matrix::operator==(const Matrix& other) {
  bool res = this->eq_matrix(other);
  return res;
}

/**
 * @brief Записывает в this минор матрицы , через "вырезание" i-ой строки и j-го
 * столбца
 *
 * @param src исходник матрицы минора
 * @param rows номер индекс строки
 * @param column номер индекса столбца
 */
void Matrix::GetMinor(const Matrix src, int row, int column) {
  if (_rows + 1 == src._rows && _columns + 1 == src._columns) {
    for (int i = 0, flag_i = 0; i < src._rows; i++) {
      if (i == row) {
        flag_i = 1;
      } else {
        for (int j = 0, flag_d = 0; j < src._columns; j++) {
          if (j == column) {
            flag_d = 1;
          } else {
            _matrix[i - flag_i][j - flag_d] = src._matrix[i][j];
          }
        }
      }
    }
  } else {
    throw std::invalid_argument("GetMinor: Incorrect size of _matrix");
  }
}

double Matrix::determinant() {
  double D = 0;
  if (_columns == _rows) {
    if (_rows == 1) return _matrix[0][0];
    Matrix temp(_rows - 1, _columns - 1);
    for (int i = 0; i < _rows; i++) {
      temp.GetMinor(*this, 0, i);
      int one = 1;
      if (i % 2 == 1) one = -1;
      D += _matrix[0][i] * temp.determinant() * one;
    }
  } else {
    throw std::invalid_argument("determinant: matrix isn't sqare");
  }

  return D;
}

Matrix Matrix::transpose() {
  Matrix res(_columns, _rows);
  for (int i = 0; i < _columns; i++) {
    for (int j = 0; j < _rows; j++) {
      res._matrix[i][j] = _matrix[j][i];
    }
  }
  return res;
}

// вычисляет матрицу алгебраических дополнений
Matrix Matrix::calc_complements() {
  Matrix res(_rows, _columns);
  if (res._rows == res._columns) {
    Matrix calc(_rows - 1, _columns - 1);
    for (int i = 0; i < _rows; i++) {
      for (int j = 0; j < _columns; j++) {
        calc.GetMinor(*this, i, j);
        res._matrix[i][j] = calc.determinant();
        if ((i + j) % 2 == 1) res._matrix[i][j] *= -1;
      }
    }
  } else {
    throw std::invalid_argument("calc_complements: _matrix isn't sqare");
  }
  return res;
}

void Matrix::sub_matrix(const Matrix& other) {
  if (_matrix == nullptr || other._matrix == nullptr)
    throw std::invalid_argument("sub: _matrix is not exist");
  if (_rows == other._rows && _columns == other._columns) {
    for (int i = 0; i < _rows; i++) {
      for (int j = 0; j < _columns; j++) {
        _matrix[i][j] -= other._matrix[i][j];
      }
    }
  } else {
    throw std::invalid_argument("sub: m1 and m2 have different sizes");
  }
}

void Matrix::sum_matrix(const Matrix& other) {
  if (_matrix == nullptr || other._matrix == nullptr)
    throw std::invalid_argument("sum: _matrix is not exist");
  if (_rows == other._rows && _columns == other._columns) {
    for (int i = 0; i < _rows; i++) {
      for (int j = 0; j < _columns; j++) {
        _matrix[i][j] += other._matrix[i][j];
      }
    }
  } else {
    throw std::invalid_argument("sum: m1 and m2 have different sizes");
  }
}

bool Matrix::eq_matrix(const Matrix& other) {
  bool res = true;
  if (_rows == other._rows && _columns == other._columns) {
    for (int i = 0; i < _rows && res; i++) {
      for (int j = 0; j < _columns && res; j++) {
        if (fabs(_matrix[i][j] - other._matrix[i][j]) > 0.000001) res = false;
      }
    }
  } else {
    res = false;
  }
  return res;
}

void Matrix::mul_number(const double number) {
  for (int i = 0; i < _rows; i++) {
    for (int j = 0; j < _columns; j++) {
      _matrix[i][j] = _matrix[i][j] * number;
    }
  }
}

void Matrix::mul_matrix(const Matrix& other) {
  if (_columns != other._rows) {
    throw std::invalid_argument("Cols from 1st M != rows from 2nd M");
  }
  Matrix A(_rows, other._columns);
  for (int i = 0; i < _rows; i++) {
    for (int j = 0; j < other._columns; j++) {
      for (int k = 0; k < _columns; k++) {
        A._matrix[i][j] += _matrix[i][k] * other._matrix[k][j];
      }
    }
  }
  this->~Matrix();
  _matrix = new double*[A._rows];
  for (int i = 0; i < A._rows; i++) {
    _matrix[i] = new double[_columns];
  }
  *this = A;
}

Matrix Matrix::inverse_matrix() {
  Matrix res(_rows, _columns);
  if (_rows == _columns && this->IsNormalMatrix()) {
    double D = this->determinant();
    if (D != 0) {
      if (_rows == 1) {
        res[0][0] = 1.0 / D;
      } else {
        res = this->calc_complements();
        res = res.transpose();
        res *= (1 / D);
      }
    } else {
      throw std::invalid_argument("inverse: matrix determinant is equal to 0");
    }
  } else {
    throw std::invalid_argument("inverse: matrix isn't sqare");
  }
  return res;
}



Matrix Matrix::Concatenation(Matrix& other) {
  if (other._rows != _rows) {
    throw std::invalid_argument("Concatenation: matrices sizes doesn't match");
  }
  Matrix tmp(this->_rows, this->_columns + other._columns);
  for (int i = 0; i <_rows; i++) {
    for (int j = 0; j < _columns; j++) {
      tmp[i][j] = _matrix[i][j];
    }
  }

  for (int i = 0; i < tmp.row(); i++) {
    for (int j = this->_columns; j < tmp.col(); j++) {
      tmp[i][j] = other[i][j - this->_columns];
    }
  }
  return tmp;
}

void Matrix::FillRandom(double fMin, double fMax) {
  for (int i = 0; i < _rows; i++) {
    for (int j = 0; j < _columns; j++) {
      this->_matrix[i][j] = fMin + (double)rand() / RAND_MAX * (fMax - fMin);
    }
  }
}

void Matrix::show() {
  for (int i = 0; i < _rows; i++) {
    for (int j = 0; j < _columns; j++) {
      std::cout << this->_matrix[i][j] << " ";
    }
    std::cout << "\n";
  }
  std::cout << "rows " << _rows << " col " << _columns << "\n";
}

bool Matrix::IsNormalMatrix() {
  bool res = false;
  if (_rows > 0 && _columns > 0 && this->_matrix != nullptr) res = true;
  return res;
}

bool Matrix::IsNull() {
  bool res = false;
  void* ptr = static_cast<void*>(this->_matrix);
  if (ptr == nullptr) {
    res = true;
  }
  return res;
}

double* Matrix::operator[](int i) {
  double* out;
  if (i >= _rows) {
    out = nullptr;
    throw std::out_of_range("[]: index is out of range");
  }
  out = _matrix[i];
  return out;
}


Matrix& Matrix::SetIdentityMatrix() {
  for (int i = 0; i < _rows; i++) {
    for (int j = 0; j < _columns; j++) {
      if (i == j) {
        _matrix[i][j] = 1;
      } else {
        _matrix[i][j] = 0;
      }
    }
  }
  return *this;
}