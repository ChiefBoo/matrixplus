#ifndef SRC_S21_MATRIX_OOP_H_
#define SRC_S21_MATRIX_OOP_H_

#include <cmath>
#include <iostream>

using namespace std;

class S21Matrix {
 private:
  // attributes
  int rows_, cols_;
  double** matrix_;

 public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other);
  ~S21Matrix();

  int getRows();
  int getCols();
  double** getMatrix();
  void setRows(int n);
  void setCols(int m);

  // // some operators overloads
  S21Matrix operator+(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other);
  S21Matrix operator*(const S21Matrix& other);
  S21Matrix operator*(const double num);
  S21Matrix& operator=(const S21Matrix& o);  // assignment operator overload
  S21Matrix& operator=(S21Matrix&& o);
  bool operator==(const S21Matrix& other);
  double& operator()(int row, int col);  // index operator overload
  double& operator()(int row, int col) const;
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix operator*=(const S21Matrix& other);
  S21Matrix operator*=(const double num);

  // some public methods
  bool EqMatrix(const S21Matrix& other);   // ==
  void SumMatrix(const S21Matrix& other);  // +=
  void SubMatrix(const S21Matrix& other);  //-=
  void MulNumber(const double num);        // *=
  void MulMatrix(const S21Matrix& other);  // *=
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();

  S21Matrix GetMinor(int row, int col);
};

#endif  // SRC_S21_MATRIX_OOP_H_