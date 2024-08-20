#ifndef __S21MATRIX_H__
#define __S21MATRIX_H__

#include <cmath>
#include <cstring>
#include <iostream>
#define EPS 10e-6

class S21Matrix {
 private:
  // attributes
  int _rows, _cols;  // rows and columns attributes
  double** _matrix;  // pointer to the memory where the matrix will be allocated

  // privte methods
  void createMatrix();
  void deleteMatrix();
  S21Matrix createMinor(int row, int col);

 public:
  S21Matrix();                    // default constructor
  S21Matrix(int rows, int cols);  // parameterized constructor
  S21Matrix(const S21Matrix& o);  // copy cnstructor
  S21Matrix(S21Matrix&& o);       // move cnstructor
  ~S21Matrix();                   // destructor

  // some operators overloads
  S21Matrix& operator=(const S21Matrix& o);  // assignment operator overload
  double& operator()(int row, int col);      // index operator overload
  int& operator()(int row, int col) const;
  S21Matrix& operator+=(const S21Matrix& o);
  S21Matrix operator+(const S21Matrix& o);
  S21Matrix& operator-=(const S21Matrix& o);
  S21Matrix operator-(const S21Matrix& o);
  S21Matrix& operator*=(const S21Matrix& o);
  S21Matrix operator*(const S21Matrix& o);
  S21Matrix& operator*=(const double& num);
  S21Matrix operator*(const double& num);
  bool operator==(const S21Matrix& o);
  double* operator[](int row) const;

  // some public methods
  bool EqMatrix(const S21Matrix& o);
  void SumMatrix(const S21Matrix& o);
  void SubMatrix(const S21Matrix& o);
  void MulMatrix(const S21Matrix& o);
  void MulNumber(const double num);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();

  int getRow();
  int getCol();
  void setRow(int row);
  void setCol(int col);

  //   void printMatrix();
};

#endif