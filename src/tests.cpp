#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

TEST(Constructor, Default) {
  S21Matrix a;
  EXPECT_EQ(a.getRows(), 0);
  EXPECT_EQ(a.getCols(), 0);
  EXPECT_EQ(a.getMatrix(), nullptr);
}

TEST(Constructor, Parametres1) {
  S21Matrix a(3, 5);
  EXPECT_EQ(a.getRows(), 3);
  EXPECT_EQ(a.getCols(), 5);
  EXPECT_NE(a.getMatrix(), nullptr);

  for (int i = 0; i < a.getRows(); i++) {
    for (int j = 0; j < a.getCols(); j++) EXPECT_EQ(a.getMatrix()[i][j], 0.0);
  }
}

TEST(Constructor, Parametres2) { EXPECT_ANY_THROW(S21Matrix a(-1, 5)); }

TEST(Constructor, Copy) {
  S21Matrix a(3, 5);
  S21Matrix b(a);
  EXPECT_EQ(3, b.getRows());
  EXPECT_EQ(5, b.getCols());
  EXPECT_TRUE(a == b);
}

TEST(Constructor, Move) {
  S21Matrix a(3, 5);
  S21Matrix b(std::move(a));
  EXPECT_EQ(3, b.getRows());
  EXPECT_EQ(5, b.getCols());
  EXPECT_EQ(0, a.getRows());
  EXPECT_EQ(0, a.getCols());
  EXPECT_EQ(a.getMatrix(), nullptr);
  EXPECT_NE(b.getMatrix(), nullptr);
}

TEST(Getters, Rows) {
  S21Matrix a(3, 4);
  EXPECT_TRUE(a.getRows() == 3);
}

TEST(Getters, Cols) {
  S21Matrix a(3, 4);
  EXPECT_TRUE(a.getCols() == 4);
}

TEST(Getters, Matrix) {
  S21Matrix a(3, 4);
  double **other = a.getMatrix();
  EXPECT_TRUE(a.getMatrix() == other);
}

TEST(Setters, RowsIncrease) {
  S21Matrix a(3, 5);
  int newRows = 8;
  a.setRows(newRows);
  EXPECT_TRUE(a.getRows() == newRows && a(newRows - 1, 4) == 0);
}

TEST(Setters, RowsDecrease) {
  S21Matrix a(3, 4);
  a.setRows(1);
  EXPECT_TRUE(a.getRows() == 1);
}

TEST(Setters, ColsIncrease) {
  S21Matrix a(3, 5);
  int newCols = 8;
  a.setCols(newCols);
  EXPECT_TRUE(a.getCols() == newCols && a(2, newCols - 1) == 0);
}

TEST(Setters, ColsDecrease) {
  S21Matrix a(3, 4);
  a.setCols(1);
  EXPECT_TRUE(a.getCols() == 1);
}

TEST(Functions, EqMatrixTest1) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);

  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;

  b(0, 0) = 1;
  b(0, 1) = 2;
  b(1, 0) = 3;
  b(1, 1) = 4;

  EXPECT_TRUE(a.EqMatrix(b));
}

TEST(Functions, EqMatrixTest2) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  S21Matrix c(2, 3);

  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;

  b(0, 0) = 1;
  b(0, 1) = 2;
  b(1, 0) = 3;
  b(1, 1) = 5;

  EXPECT_FALSE(a.EqMatrix(b));
  EXPECT_FALSE(a.EqMatrix(c));
}

TEST(Functions, SumMatrixTest) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  S21Matrix res(2, 2);

  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;

  b(0, 0) = 1;
  b(0, 1) = 2;
  b(1, 0) = 3;
  b(1, 1) = 4;

  res(0, 0) = 2;
  res(0, 1) = 4;
  res(1, 0) = 6;
  res(1, 1) = 8;

  a.SumMatrix(b);
  EXPECT_TRUE(a == res);
  b.setCols(5);
  EXPECT_ANY_THROW(a.SumMatrix(b));
  S21Matrix c;
  EXPECT_ANY_THROW(a.SumMatrix(c));
}

TEST(Functions, SubMatrixTest) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  S21Matrix res(2, 2);

  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;

  b(0, 0) = 1;
  b(0, 1) = 2;
  b(1, 0) = 3;
  b(1, 1) = 4;

  res(0, 0) = 0;
  res(0, 1) = 0;
  res(1, 0) = 0;
  res(1, 1) = 0;

  a.SubMatrix(b);
  EXPECT_TRUE(a == res);
  b.setCols(5);
  EXPECT_ANY_THROW(a.SubMatrix(b));
  S21Matrix c;
  EXPECT_ANY_THROW(a.SubMatrix(c));
}

TEST(Functions, MulMatrixTest) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  S21Matrix res(2, 2);

  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;

  b(0, 0) = 1;
  b(0, 1) = 2;
  b(1, 0) = 3;
  b(1, 1) = 4;

  res(0, 0) = 7;
  res(0, 1) = 10;
  res(1, 0) = 15;
  res(1, 1) = 22;

  a.MulMatrix(b);
  EXPECT_TRUE(a == res);
  b.setRows(5);
  EXPECT_ANY_THROW(a.MulMatrix(b));
  S21Matrix c;
  EXPECT_ANY_THROW(a.MulMatrix(c));
}

TEST(Functions, MulNumberTest) {
  S21Matrix a(2, 2);
  S21Matrix res(2, 2);

  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;

  res(0, 0) = 5;
  res(0, 1) = 10;
  res(1, 0) = 15;
  res(1, 1) = 20;

  a.MulNumber(5);
  EXPECT_TRUE(a == res);
  S21Matrix c;
  EXPECT_ANY_THROW(c.MulNumber(5));
}

TEST(Functions, Transpose) {
  S21Matrix a(2, 2);
  S21Matrix res(2, 2);

  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;

  res(0, 0) = 1;
  res(0, 1) = 3;
  res(1, 0) = 2;
  res(1, 1) = 4;

  a.Transpose();
  EXPECT_TRUE(a == res);
  S21Matrix c;
  EXPECT_ANY_THROW(c.Transpose());
}

TEST(Functions, CalcComplements) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 3);
  S21Matrix res(2, 2);

  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;

  res(0, 0) = 4;
  res(0, 1) = -3;
  res(1, 0) = -2;
  res(1, 1) = 1;

  EXPECT_TRUE(a.CalcComplements() == res);
  S21Matrix c;
  EXPECT_ANY_THROW(c.CalcComplements());

  EXPECT_ANY_THROW(b.CalcComplements());
  S21Matrix d(1, 1);
  d(0, 0) = 5;
  S21Matrix e(1, 1);
  e(0, 0) = 1;
  EXPECT_TRUE(d.CalcComplements() == e);
}

TEST(Functions, Determinant1) {
  S21Matrix a(2, 2);

  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;

  double det = 0.0;
  det = a.Determinant();

  EXPECT_TRUE(det == -2);
  a.setCols(5);
  EXPECT_ANY_THROW(a.Determinant());
  S21Matrix c;
  EXPECT_ANY_THROW(c.Determinant());
}

TEST(Functions, Determinant2) {
  S21Matrix a(3, 3);

  a(0, 0) = 1;
  a(0, 1) = 2;
  a(0, 2) = 3;
  a(1, 0) = 4;
  a(1, 1) = 5;
  a(1, 2) = 6;
  a(2, 0) = 7;
  a(2, 1) = 8;
  a(2, 2) = 9;

  double det = 0.0;
  det = a.Determinant();

  EXPECT_TRUE(det == 0);
}

TEST(Functions, InverseMatrixTest1) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 3);
  S21Matrix res(2, 2);

  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;

  res(0, 0) = -2;
  res(0, 1) = 1;
  res(1, 0) = 1.5;
  res(1, 1) = -0.5;

  EXPECT_TRUE(a.InverseMatrix() == res);
  EXPECT_ANY_THROW(b.InverseMatrix());
  S21Matrix c;
  EXPECT_ANY_THROW(c.InverseMatrix());
}

TEST(Functions, InverseMatrixTest2) {
  S21Matrix a(2, 2);

  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 2;
  a(1, 1) = 4;

  EXPECT_ANY_THROW(a.InverseMatrix());
}

TEST(Operators, Equal) {
  S21Matrix a;
  S21Matrix b;
  EXPECT_TRUE(a == b);
}

TEST(Operators, Assignment) {
  S21Matrix a(3, 4);
  S21Matrix b(1, 1);
  b = a;
  ASSERT_TRUE(a == b);
}

TEST(Operators, SubMatrix) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  S21Matrix res(2, 2);

  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;

  b(0, 0) = 1;
  b(0, 1) = 2;
  b(1, 0) = 3;
  b(1, 1) = 4;

  res(0, 0) = 0;
  res(0, 1) = 0;
  res(1, 0) = 0;
  res(1, 1) = 0;

  EXPECT_TRUE((a - b) == res);
}

TEST(Operators, SumMatrix) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  S21Matrix res(2, 2);

  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;

  b(0, 0) = 1;
  b(0, 1) = 2;
  b(1, 0) = 3;
  b(1, 1) = 4;

  res(0, 0) = 2;
  res(0, 1) = 4;
  res(1, 0) = 6;
  res(1, 1) = 8;

  EXPECT_TRUE((a + b) == res);
}

TEST(Operators, SumMatrixIncrement) {
  S21Matrix a(2, 2);
  S21Matrix res(2, 2);

  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;

  a += a;

  res(0, 0) = 2;
  res(0, 1) = 4;
  res(1, 0) = 6;
  res(1, 1) = 8;

  EXPECT_TRUE(a == res);
}

TEST(Operators, SubMatrixDecrement) {
  S21Matrix a(2, 2);
  S21Matrix res(2, 2);

  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;

  a -= a;

  EXPECT_TRUE(a == res);
}

TEST(Operators, MulMatrix) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  S21Matrix res(2, 2);

  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;

  b(0, 0) = 1;
  b(0, 1) = 2;
  b(1, 0) = 3;
  b(1, 1) = 4;

  res(0, 0) = 7;
  res(0, 1) = 10;
  res(1, 0) = 15;
  res(1, 1) = 22;

  EXPECT_TRUE((a * b) == res);
}

TEST(Operators, MulMatrixIncrement) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  S21Matrix res(2, 2);

  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;

  b(0, 0) = 1;
  b(0, 1) = 2;
  b(1, 0) = 3;
  b(1, 1) = 4;

  res(0, 0) = 7;
  res(0, 1) = 10;
  res(1, 0) = 15;
  res(1, 1) = 22;

  a *= b;

  EXPECT_TRUE(a == res);
}

TEST(Operators, MulNums) {
  S21Matrix a(2, 2);
  S21Matrix res(2, 2);

  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;

  res(0, 0) = 5;
  res(0, 1) = 10;
  res(1, 0) = 15;
  res(1, 1) = 20;

  EXPECT_TRUE((a * 5) == res);
}

TEST(Operators, MulNumsIncrement) {
  S21Matrix a(2, 2);
  S21Matrix res(2, 2);

  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;

  res(0, 0) = 5;
  res(0, 1) = 10;
  res(1, 0) = 15;
  res(1, 1) = 20;
  a *= 5;
  EXPECT_TRUE(a == res);
}

TEST(Operators, ReturnElement1) {
  S21Matrix a(2, 2);

  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;

  ASSERT_TRUE(a(1, 1) == 4);
}

TEST(Operators, ReturnElement2) {
  const S21Matrix b(2, 2);
  double const_value = b(0, 0);
  ASSERT_TRUE(const_value == 0);
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}