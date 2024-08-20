#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() {
  _rows = 0;
  _cols = 0;
  _matrix = nullptr;
}

S21Matrix::S21Matrix(int rows, int cols) : _rows(rows), _cols(cols) {
  if (rows <= 0 || cols <= 0) {
    throw std::invalid_argument("Wrong size of matrix");
  }
  createMatrix();
}

S21Matrix::S21Matrix(const S21Matrix& o) : _rows(o._rows), _cols(o._cols) {
  createMatrix();
  for (int i = 0; i < _rows; ++i) {
    for (int j = 0; j < _cols; ++j) {
      _matrix[i][j] = o._matrix[i][j];
    }
  }
}

S21Matrix::S21Matrix(S21Matrix&& o) : _rows(o._rows), _cols(o._cols) {
  _matrix = o._matrix;
  o._rows = 0;
  o._cols = 0;
  o._matrix = nullptr;
}

S21Matrix::~S21Matrix() { deleteMatrix(); }

void S21Matrix::createMatrix() {
  _matrix = new double*[_rows];
  for (int i = 0; i < _rows; ++i) {
    _matrix[i] = new double[_cols]();
  }
}

void S21Matrix::deleteMatrix() {
  for (int i = 0; i < _rows; ++i) {
    delete[] _matrix[i];
  }
  delete[] _matrix;
}

bool S21Matrix::EqMatrix(const S21Matrix& o) {
  bool res = true;
  if (_rows != o._rows || _cols != o._cols) {
    res = false;
  }
  for (int i = 0; i < _rows && res; ++i) {
    for (int j = 0; j < _cols && res; ++j) {
      if (fabs(_matrix[i][j] - o._matrix[i][j]) > EPS) {
        res = false;
      }
    }
  }
  return res;
}

void S21Matrix::SumMatrix(const S21Matrix& o) {
  if (_rows != o._rows || _cols != o._cols) {
    throw std::invalid_argument("Different size of matrix");
  }
  for (int i = 0; i < _rows; ++i) {
    for (int j = 0; j < _cols; ++j) {
      _matrix[i][j] += o._matrix[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& o) {
  if (_rows != o._rows || _cols != o._cols) {
    throw std::invalid_argument("Different size of matrix");
  }
  for (int i = 0; i < _rows; ++i) {
    for (int j = 0; j < _cols; ++j) {
      _matrix[i][j] -= o._matrix[i][j];
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& o) {
  if (_cols != o._rows) {
    throw std::invalid_argument("Wrong size of matrixes");
  }
  S21Matrix res(_rows, o._cols);
  for (int i = 0; i < _rows; ++i) {
    for (int j = 0; j < o._cols; ++j) {
      for (int k = 0; k < _cols; ++k) {
        res._matrix[i][j] += this->_matrix[i][k] * o._matrix[k][j];
      }
    }
  }
  *this = res;
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < this->_rows; ++i) {
    for (int j = 0; j < this->_cols; ++j) {
      this->_matrix[i][j] *= num;
    }
  }
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix res(_cols, _rows);
  for (int i = 0; i < this->_rows; ++i) {
    for (int j = 0; j < this->_cols; ++j) {
      res._matrix[j][i] = _matrix[i][j];
    }
  }
  return res;
}

double S21Matrix::Determinant() {
  if (_rows != _cols) {
    throw std::invalid_argument("Matrix is not sqared");
  }
  double res = 0;
  if (_rows == 1) {
    res += this->_matrix[0][0];
  } else {
    for (int i = 0; i < _cols; ++i) {
      S21Matrix minor;
      minor = this->createMinor(0, i);
      res += this->_matrix[0][i] * (((i) % 2) ? -1 : 1) * minor.Determinant();
    }
  }
  return res;
}

S21Matrix S21Matrix::createMinor(int row, int col) {
  S21Matrix res(this->_rows - 1, this->_cols - 1);
  int offset_row = 0, offset_col = 0;
  for (int i = 0; i < res._rows; ++i) {
    if (row == i) {
      offset_row = 1;
    }
    offset_col = 0;
    for (int j = 0; j < res._cols; ++j) {
      if (col == j) {
        offset_col = 1;
      }
      res._matrix[i][j] = this->_matrix[i + offset_row][j + offset_col];
    }
  }
  return res;
}

S21Matrix S21Matrix::CalcComplements() {
  if (this->_rows != this->_cols) {
    throw std::invalid_argument("Matrix is not sqared");
  }
  S21Matrix res(this->_rows, this->_cols);
  S21Matrix minor;
  for (int i = 0; i < this->_rows; ++i) {
    for (int j = 0; j < this->_cols; ++j) {
      minor = this->createMinor(i, j);
      res._matrix[i][j] = (((i + j) % 2) ? -1 : 1) * minor.Determinant();
    }
  }
  return res;
}

// extra
// void S21Matrix::printMatrix() {
//   for (int i = 0; i < this->_rows; ++i) {
//     for (int j = 0; j < this->_cols; ++j) {
//       std::cout << this->_matrix[i][j] << ' ';
//     }
//     std::cout << std::endl;
//   }
// }
// extra

S21Matrix S21Matrix::InverseMatrix() {
  if (this->_rows != this->_cols) {
    throw std::invalid_argument("Matrix is not sqared");
  }
  double det = this->Determinant();
  if (det == 0) {
    throw std::logic_error("Determinant = 0");
  }
  S21Matrix result(*this);
  if (this->_rows == 1) {
    result *= (1 / (det));
  } else {
    result = (result.CalcComplements()).Transpose();
  }
  result *= (1 / (det));
  return result;
}

double& S21Matrix::operator()(int row, int col) {
  if (row >= this->_rows || col >= this->_cols) {
    throw std::out_of_range("Incorrect input, index is out of range");
  }
  return this->_matrix[row][col];
}

S21Matrix& S21Matrix::operator=(const S21Matrix& o) {
  deleteMatrix();
  this->_rows = o._rows;
  this->_cols = o._cols;
  createMatrix();
  for (int i = 0; i < this->_rows; ++i) {
    for (int j = 0; j < this->_cols; ++j) {
      this->_matrix[i][j] = o._matrix[i][j];
    }
  }
  return *this;
}

S21Matrix S21Matrix::operator+(const S21Matrix& o) {
  S21Matrix res(*this);
  res.SumMatrix(o);
  return res;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& o) {
  this->SumMatrix(o);
  return *this;
}

S21Matrix S21Matrix::operator-(const S21Matrix& o) {
  S21Matrix res(*this);
  res.SubMatrix(o);
  return res;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& o) {
  this->SubMatrix(o);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& o) {
  this->MulMatrix(o);
  return *this;
}

S21Matrix S21Matrix::operator*(const S21Matrix& o) {
  S21Matrix res(*this);
  res.MulMatrix(o);
  return res;
}

S21Matrix& S21Matrix::operator*=(const double& num) {
  this->MulNumber(num);
  return *this;
}

S21Matrix S21Matrix::operator*(const double& num) {
  S21Matrix res(*this);
  res.MulNumber(num);
  return res;
}

double* S21Matrix::operator[](int row) const {
  if (row >= _rows)
    throw std::out_of_range("Incorrect input, index is out of range");

  return _matrix[row];
}

bool S21Matrix::operator==(const S21Matrix& o) { return this->EqMatrix(o); }

int S21Matrix::getRow() { return this->_rows; }

int S21Matrix::getCol() { return this->_cols; }

void S21Matrix::setRow(int row) {
  if (row <= 0) {
    throw std::length_error("Wrong size of matrix");
  }
  S21Matrix res(row, _cols);
  for (int i = 0; i < res._rows && i < this->_rows; ++i) {
    for (int j = 0; j < res._cols; ++j) {
      res(i, j) = this->_matrix[i][j];
    }
  }
  *this = res;
}

void S21Matrix::setCol(int col) {
  if (col <= 0) {
    throw std::length_error("Wrong size of matrix");
  }
  S21Matrix res(_rows, col);
  for (int i = 0; i < res._rows; ++i) {
    for (int j = 0; j < res._cols && j < this->_cols; ++j) {
      res(i, j) = this->_matrix[i][j];
    }
  }
  *this = res;
}