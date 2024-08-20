#include <gtest/gtest.h>

#include <iostream>

#include "../s21_matrix_oop.h"

/*
logic_error	- сообщения об ошибках во внутренней логике программы, таких как
нарушение логических предварительных условий или инвариантов класса.

domain_error - 	Этот класс определяет тип объектов, генерируемых в качестве
исключений для сообщения об ошибках предметной области. Как правило, предметной
областью математической функции является подмножество значений, для которых она
определена. Например, функция квадратного корня определена только для
неотрицательных чисел. Таким образом, отрицательное число для такой функции
будет квалифицироваться как ошибка домена.

invalid_argument - 	о недопустимых аргументах.

length_error - 	об ошибках изменения размера.

out_of_range - аргументы находятся вне диапазона.
*/

TEST(test_class, constructor) {
  S21Matrix mat;
  EXPECT_EQ(mat.getCol(), 0);
  EXPECT_EQ(mat.getRow(), 0);
}

TEST(test_class, param_constructor) {
  S21Matrix mat(50, 420);
  EXPECT_EQ(mat.getRow(), 50);
  EXPECT_EQ(mat.getCol(), 420);
}

TEST(test_class, copy_constructor) {
  S21Matrix mat(12, 12);
  S21Matrix copy(mat);

  EXPECT_EQ(copy.getCol(), 12);
  EXPECT_EQ(copy.getRow(), 12);
}

TEST(test_class, moved_constructor) {
  S21Matrix mat(12, 12);
  S21Matrix moved(std::move(mat));

  EXPECT_EQ(mat.getCol(), 0);
  EXPECT_EQ(mat.getRow(), 0);
  EXPECT_EQ(moved.getCol(), 12);
  EXPECT_EQ(moved.getRow(), 12);
}

TEST(test_class, brackets_operator) {
  S21Matrix mat(6, 9);
  EXPECT_EQ(mat(0, 0), 0);

  mat(0, 1) = 70;
  EXPECT_EQ(mat(0, 1), 70);

  mat(5, 8) = 70.420;
  EXPECT_EQ(mat(5, 8), 70.420);
  EXPECT_THROW(mat(10, 0), std::out_of_range);
}

TEST(test_class, square_brackets_operator) {
  S21Matrix mat(6, 9);
  EXPECT_EQ(mat[0][0], 0);

  mat[5][5] = 40;
  EXPECT_EQ(mat[5][5], 40);

  mat[5][8] = 76.86;
  EXPECT_EQ(mat[5][8], 76.86);
  EXPECT_THROW(mat[10], std::out_of_range);
}

TEST(test_mutators, valid_setRow) {
  S21Matrix mat(1, 1);
  EXPECT_THROW(mat.setRow(-3), std::length_error);
}

TEST(test_mutators, valid_setCol) {
  S21Matrix mat(1, 1);
  EXPECT_THROW(mat.setCol(-3), std::length_error);
}

TEST(test_mutators, setRow_up) {
  S21Matrix mat(2, 2);
  mat[1][1] = 4.5;

  mat.setRow(5);
  EXPECT_EQ(mat.getRow(), 5);
  EXPECT_EQ(mat[1][1], 4.5);
}

TEST(test_mutators, setRow_down) {
  S21Matrix mat(2, 2);
  mat[0][0] = 3.5;

  mat.setRow(1);
  EXPECT_EQ(mat.getRow(), 1);
  EXPECT_EQ(mat[0][0], 3.5);
}

TEST(test_mutators, setRow_zero) {
  S21Matrix mat;

  EXPECT_ANY_THROW(mat.setRow(0));
}

TEST(test_mutators, setCol_up) {
  S21Matrix mat(2, 2);
  mat[1][1] = 3.8;

  mat.setCol(5);
  EXPECT_EQ(mat.getCol(), 5);
  EXPECT_EQ(mat[1][1], 3.8);
}

TEST(test_mutators, setCol_down) {
  S21Matrix mat(2, 2);
  mat[0][0] = 4.5;

  mat.setCol(1);
  EXPECT_EQ(mat.getCol(), 1);
  EXPECT_EQ(mat[0][0], 4.5);
}

TEST(test_mutators, setCol_zero) {
  S21Matrix mat;
  EXPECT_ANY_THROW(mat.setCol(0));
}

TEST(test_overload, equal_lvalue) {
  S21Matrix mat;
  S21Matrix x(3, 6);
  x(1, 2) = 3;
  x(2, 2) = 3;

  mat = x;

  EXPECT_EQ(mat.getRow(), 3);
  EXPECT_EQ(mat.getCol(), 6);
  EXPECT_EQ(mat(1, 2), 3);
  EXPECT_EQ(mat(2, 2), 3);
}

TEST(test_overload, equal_rvalue) {
  S21Matrix mat(2, 2);
  S21Matrix n;

  n = std::move(mat);

  EXPECT_EQ(n.getCol(), 2);
  EXPECT_EQ(n.getRow(), 2);
}

TEST(test_methods, eq_matrix) {
  S21Matrix mat(2, 2);
  S21Matrix n(2, 2);

  ASSERT_TRUE(mat == n);
}

TEST(test_methods, eq_matrix1) {
  S21Matrix mat(3, 2);
  S21Matrix n;

  mat[0][1] = 78;
  n = mat;

  ASSERT_TRUE(mat == n);
}

TEST(test_methods, eq_matrix2) {
  S21Matrix mat(2, 2);
  S21Matrix n(2, 2);
  n(0, 0) = 1;
  ASSERT_FALSE(mat == n);
}

TEST(test_methods, eq_matrix3) {
  S21Matrix mat(2, 2);
  S21Matrix n(2, 3);
  ASSERT_FALSE(mat == n);
}

TEST(test_methods, sum_matrix) {
  S21Matrix mat(2, 2);
  S21Matrix n(2, 2);

  mat(0, 0) = 1;
  n(0, 0) = 1;

  mat(1, 1) = 1;
  n(1, 1) = 1;

  mat.SumMatrix(n);

  EXPECT_EQ(mat(0, 0), 2);
  EXPECT_EQ(mat(1, 1), 2);
}

TEST(test_methods, operator_summation1) {
  S21Matrix mat(2, 2);
  S21Matrix n(2, 2);

  mat(0, 0) = 1;
  n(0, 0) = 1;

  mat(1, 1) = 1;
  n(1, 1) = 1;

  mat = mat + n;

  EXPECT_EQ(mat(0, 0), 2);
  EXPECT_EQ(mat(1, 1), 2);
}

TEST(test_methods, operator_summation2) {
  S21Matrix mat(2, 2);
  S21Matrix n(2, 2);

  mat(0, 0) = 1;
  n(0, 0) = 1;

  mat(1, 1) = 1;
  n(1, 1) = 1;

  mat += n + mat;

  EXPECT_EQ(mat(0, 0), 3);
  EXPECT_EQ(mat(1, 1), 3);
}

TEST(test_methods, sum_matrix_valid) {
  S21Matrix mat;
  S21Matrix n(1, 5);
  EXPECT_THROW(mat.SumMatrix(n), std::invalid_argument);
}

TEST(test_methods, sub_matrix_valid) {
  S21Matrix mat;
  S21Matrix n(1, 5);
  EXPECT_THROW(mat.SubMatrix(n), std::invalid_argument);
}

TEST(test_methods, sub_matrix) {
  S21Matrix mat(2, 2);
  S21Matrix n(2, 2);

  mat(0, 0) = 1;
  n(0, 0) = 1;

  mat(1, 1) = 1;
  n(1, 1) = 1;

  mat.SubMatrix(n);

  EXPECT_EQ(mat(0, 0), 0);
  EXPECT_EQ(mat(1, 1), 0);
}

TEST(test_methods, operator_subtraction1) {
  S21Matrix mat(2, 2);
  S21Matrix n(2, 2);

  mat(0, 0) = 1;
  n(0, 0) = 1;

  mat(1, 1) = 1;
  n(1, 1) = 1;

  mat -= n;

  EXPECT_EQ(mat(0, 0), 0);
  EXPECT_EQ(mat(1, 1), 0);
}

TEST(test_methods, operator_subtraction2) {
  S21Matrix mat(2, 2);
  S21Matrix n(2, 2);

  mat(0, 0) = 1;
  n(0, 0) = 1;

  mat(1, 1) = 1;
  n(1, 1) = 1;

  mat = mat - n;

  EXPECT_EQ(mat(0, 0), 0);
  EXPECT_EQ(mat(1, 1), 0);
}

TEST(test_methods, mul_matrices) {
  size_t rows = 2;
  size_t cols = 3;

  S21Matrix mat(rows, cols);
  S21Matrix n(cols, rows);

  for (size_t i = 0, c = 1; i < rows; i++)
    for (size_t j = 0; j < cols; j++) mat[i][j] = c++;

  for (size_t i = 0, c = 7; i < cols; i++)
    for (size_t j = 0; j < rows; j++) n[i][j] = c++;

  mat.MulMatrix(n);

  S21Matrix res(2, 2);
  res[0][0] = 58;
  res[0][1] = 64;
  res[1][0] = 139;
  res[1][1] = 154;

  ASSERT_TRUE(mat.EqMatrix(res));
}

TEST(test_methods, mul_matrices2) {
  size_t rows = 2;
  size_t cols = 3;

  S21Matrix mat(rows, cols);
  S21Matrix n(cols + 1, rows);

  EXPECT_ANY_THROW(mat * n);
}

TEST(test_methods, eqmul_operator) {
  size_t rows = 2;
  size_t cols = 3;

  S21Matrix mat(rows, cols);
  S21Matrix n(cols, rows);

  for (size_t i = 0, c = 1; i < rows; i++)
    for (size_t j = 0; j < cols; j++) mat[i][j] = c++;

  for (size_t i = 0, c = 7; i < cols; i++)
    for (size_t j = 0; j < rows; j++) n[i][j] = c++;

  mat *= n;

  S21Matrix res(2, 2);
  res[0][0] = 58;
  res[0][1] = 64;
  res[1][0] = 139;
  res[1][1] = 154;

  ASSERT_TRUE(mat.EqMatrix(res));
}

TEST(test_methods, eqmul_operator_num) {
  size_t rows = 2;
  size_t cols = 3;

  S21Matrix mat(rows, cols);

  for (size_t i = 0, c = 1; i < rows; i++)
    for (size_t j = 0; j < cols; j++) mat[i][j] = c++;

  mat *= 2;

  S21Matrix res(2, 3);
  res[0][0] = 2;
  res[0][1] = 4;
  res[0][2] = 6;
  res[1][0] = 8;
  res[1][1] = 10;
  res[1][2] = 12;

  ASSERT_TRUE(mat.EqMatrix(res));
}

TEST(test_methods, mul_operator) {
  size_t rows = 2;
  size_t cols = 3;

  S21Matrix mat(rows, cols);
  S21Matrix n(cols, rows);

  for (size_t i = 0, c = 1; i < rows; i++)
    for (size_t j = 0; j < cols; j++) mat[i][j] = c++;

  for (size_t i = 0, c = 7; i < cols; i++)
    for (size_t j = 0; j < rows; j++) n[i][j] = c++;

  mat = mat * n;

  S21Matrix res(2, 2);
  res[0][0] = 58;
  res[0][1] = 64;
  res[1][0] = 139;
  res[1][1] = 154;

  ASSERT_TRUE(mat == res);
}

TEST(test_methods, mul_operator_num) {
  size_t rows = 2;
  size_t cols = 3;

  S21Matrix mat(rows, cols);

  for (size_t i = 0, c = 1; i < rows; i++)
    for (size_t j = 0; j < cols; j++) mat[i][j] = c++;

  mat = mat * 2.0;

  S21Matrix res(2, 3);
  res[0][0] = 2;
  res[0][1] = 4;
  res[0][2] = 6;
  res[1][0] = 8;
  res[1][1] = 10;
  res[1][2] = 12;

  ASSERT_TRUE(mat == res);
}

TEST(test_methods, transpose) {
  size_t rows = 2;
  size_t cols = 3;

  S21Matrix mat(rows, cols);
  S21Matrix res(cols, rows);

  for (size_t i = 0, c = 1; i < rows; i++)
    for (size_t j = 0; j < cols; j++, c++) {
      mat[i][j] = c;
      res[j][i] = c;
    }
  mat = mat.Transpose();

  ASSERT_TRUE(mat == res);
}

TEST(test_methods, determinant) {
  S21Matrix mat(2, 3);

  EXPECT_ANY_THROW(mat.Determinant());
}

TEST(test_methods, determinant_zero) {
  size_t size = 5;
  S21Matrix mat(5, 5);

  for (size_t i = 0; i < size; i++)
    for (size_t j = 0; j < size; j++) mat[i][j] = j;

  ASSERT_NEAR(0, mat.Determinant(), 1e-06);
}

TEST(test_methods, determinant_5x5) {
  size_t size = 5;
  S21Matrix mat(size, size);

  mat[0][1] = 6;
  mat[0][2] = -2;
  mat[0][3] = -1;
  mat[0][4] = 5;
  mat[1][3] = -9;
  mat[1][4] = -7;
  mat[2][1] = 15;
  mat[2][2] = 35;
  mat[3][1] = -1;
  mat[3][2] = -11;
  mat[3][3] = -2;
  mat[3][4] = 1;
  mat[4][0] = -2;
  mat[4][1] = -2;
  mat[4][2] = 3;
  mat[4][4] = -2;

  double res = mat.Determinant();
  ASSERT_NEAR(res, 2480, 1e-6);
}

TEST(test_methods, determinant_3x3) {
  size_t size = 3;
  S21Matrix mat(size, size);

  mat[0][0] = 2;
  mat[0][1] = 3;
  mat[0][2] = 1;
  mat[1][0] = 7;
  mat[1][1] = 4;
  mat[1][2] = 1;
  mat[2][0] = 9;
  mat[2][1] = -2;
  mat[2][2] = 1;

  double res = mat.Determinant();
  ASSERT_NEAR(res, -32, 1e-6);
}

TEST(test_methods, determinant_2x2) {
  size_t size = 2;
  S21Matrix mat(size, size);

  mat[0][0] = -5;
  mat[0][1] = -4;
  mat[1][0] = -2;
  mat[1][1] = -3;

  double res = mat.Determinant();
  ASSERT_NEAR(res, 7, 1e-6);
}

TEST(test_methods, complements_3x3) {
  size_t rows = 3;
  size_t cols = 3;

  S21Matrix example(rows, cols);
  S21Matrix result(rows, cols);

  example[0][0] = 1;
  example[0][1] = 2;
  example[0][2] = 3;
  example[1][0] = 0;
  example[1][1] = 4;
  example[1][2] = 2;
  example[2][0] = 5;
  example[2][1] = 2;
  example[2][2] = 1;

  result[0][0] = 0;
  result[0][1] = 10;
  result[0][2] = -20;
  result[1][0] = 4;
  result[1][1] = -14;
  result[1][2] = 8;
  result[2][0] = -8;
  result[2][1] = -2;
  result[2][2] = 4;

  S21Matrix res = example.CalcComplements();

  ASSERT_TRUE(res == result);
}

TEST(test_methods, CalcComplements_throw) {
  S21Matrix mat(3, 12);
  EXPECT_ANY_THROW(mat.CalcComplements());
}

TEST(test_methods, complements_3x3_1) {
  size_t rows = 3;
  size_t cols = 3;

  S21Matrix example(rows, cols);
  S21Matrix result(rows, cols);

  example[0][0] = 1.0;
  example[0][1] = 2.0;
  example[0][2] = 3.0;
  example[1][0] = 0.0;
  example[1][1] = 4.0;
  example[1][2] = 2.0;
  example[2][0] = 5.0;
  example[2][1] = 2.0;
  example[2][2] = 1.0;

  result[0][0] = 0.0;
  result[0][1] = 10.0;
  result[0][2] = -20.0;
  result[1][0] = 4.0;
  result[1][1] = -14.0;
  result[1][2] = 8.0;
  result[2][0] = -8.0;
  result[2][1] = -2.0;
  result[2][2] = 4.0;

  S21Matrix res = example.CalcComplements();

  ASSERT_TRUE(res == result);
}

TEST(test_class, zero_size) { EXPECT_ANY_THROW(S21Matrix(0, 1)); }

TEST(test_methods, complements_3x3_2) {
  size_t rows = 3;
  size_t cols = 3;

  S21Matrix example(rows, cols);
  S21Matrix result(rows, cols);

  example[0][0] = 1;
  example[0][1] = 2;
  example[0][2] = 3;
  example[1][1] = 4;
  example[1][2] = 2;
  example[2][0] = 5;
  example[2][1] = 2;
  example[2][2] = 1;

  result[0][1] = 10;
  result[0][2] = -20;
  result[1][0] = 4;
  result[1][1] = -14;
  result[1][2] = 8;
  result[2][0] = -8;
  result[2][1] = -2;
  result[2][2] = 4;

  S21Matrix res = example.CalcComplements();
  ASSERT_TRUE(res == result);
}

TEST(test_methods, inverese_3x3) {
  size_t size = 3;
  S21Matrix example(size, size);
  S21Matrix result(size, size);

  result[0][0] = 44300.0 / 367429.0;
  result[0][1] = -236300.0 / 367429.0;
  result[0][2] = 200360.0 / 367429.0;
  result[1][0] = 20600.0 / 367429.0;
  result[1][1] = 56000.0 / 367429.0;
  result[1][2] = -156483.0 / 367429.0;
  result[2][0] = 30900.0 / 367429.0;
  result[2][1] = 84000.0 / 367429.0;
  result[2][2] = -51010.0 / 367429.0;

  example[0][0] = 2.8;
  example[0][1] = 1.3;
  example[0][2] = 7.01;
  example[1][0] = -1.03;
  example[1][1] = -2.3;
  example[1][2] = 3.01;
  example[2][0] = 0;
  example[2][1] = -3;
  example[2][2] = 2;

  ASSERT_TRUE(example.InverseMatrix() == result);
}

TEST(test_methods, inverese_3x3_1) {
  size_t size = 3;
  S21Matrix example(size, size);
  S21Matrix result(size, size);
  result[0][0] = 1.0;
  result[0][1] = -1.0;
  result[0][2] = 1.0;
  result[1][0] = -38.0;
  result[1][1] = 41.0;
  result[1][2] = -34.0;
  result[2][0] = 27.0;
  result[2][1] = -29.0;
  result[2][2] = 24.0;

  example[0][0] = 2.0;
  example[0][1] = 5.0;
  example[0][2] = 7.0;
  example[1][0] = 6.0;
  example[1][1] = 3.0;
  example[1][2] = 4.0;
  example[2][0] = 5.0;
  example[2][1] = -2.0;
  example[2][2] = -3.0;

  ASSERT_TRUE(example.InverseMatrix() == result);
}

TEST(test_methods, inverse_throw) {
  S21Matrix mat(2, 3);
  EXPECT_ANY_THROW(mat.InverseMatrix());

  S21Matrix n(2, 2);
  EXPECT_ANY_THROW(n.InverseMatrix());
}

TEST(test_methods, inverse_1x1) {
  S21Matrix mat(1, 1);
  mat[0][0] = 21.20;
  double result = 1 / mat[0][0];
  double expected = mat.InverseMatrix()[0][0];
  ASSERT_NEAR(result, expected, 1e-06);
}

TEST(test_methods, inverese_3x3_2) {
  size_t size = 3;
  S21Matrix example(size, size);
  S21Matrix result(size, size);

  example[0][0] = 2;
  example[0][1] = 5;
  example[0][2] = 7;
  example[1][0] = 6;
  example[1][1] = 3;
  example[1][2] = 4;
  example[2][0] = 5;
  example[2][1] = -2;
  example[2][2] = -3;

  result[0][0] = 1;
  result[0][1] = -1;
  result[0][2] = 1;
  result[1][0] = -38;
  result[1][1] = 41;
  result[1][2] = -34;
  result[2][0] = 27;
  result[2][1] = -29;
  result[2][2] = 24;
  ASSERT_TRUE(example.InverseMatrix() == result);
}

TEST(test_methods, inverese_3x3_3) {
  size_t size = 3;
  S21Matrix example(size, size);
  S21Matrix result(size, size);

  example[0][0] = 2;
  example[0][1] = 5;
  example[0][2] = 7;
  example[1][0] = 6;
  example[1][1] = 3;
  example[1][2] = 4;
  example[2][0] = 5;
  example[2][1] = -2;
  example[2][2] = -3;

  result[0][0] = 1;
  result[0][1] = -1;
  result[0][2] = 1;
  result[1][0] = -38;
  result[1][1] = 41;
  result[1][2] = -34;
  result[2][0] = 27;
  result[2][1] = -29;
  result[2][2] = 24;
  ASSERT_TRUE(example.InverseMatrix() == result);
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}