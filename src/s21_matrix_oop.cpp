#include "s21_matrix_oop.h"

// Constructors

S21Matrix::S21Matrix() {
  rows_ = 0;
  cols_ = 0;
  matrix_ = nullptr;
}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows_ < 1 || cols_ < 1) throw invalid_argument("Incorrect matrix size");
  matrix_ = new double *[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = 0;
    }
  }
}

S21Matrix::S21Matrix(const S21Matrix &other)
    : rows_(other.rows_), cols_(other.cols_) {
  if (other.matrix_ != nullptr) {
    matrix_ = new double *[rows_];
    for (int i = 0; i < rows_; i++) {
      matrix_[i] = new double[cols_];
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] = other.matrix_[i][j];
      }
    }
  } else {
    matrix_ = nullptr;
  }
}

S21Matrix::S21Matrix(S21Matrix &&other)
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

// Destructor

S21Matrix::~S21Matrix() {
  if (matrix_ != nullptr) {
    for (int i = 0; i < rows_; i++) delete[] matrix_[i];
    delete[] matrix_;
    rows_ = 0;
    cols_ = 0;
    matrix_ = nullptr;
  }
}

// Accessors

int S21Matrix::getRows() { return rows_; }

int S21Matrix::getCols() { return cols_; }

double **S21Matrix::getMatrix() { return matrix_; }

// Mutators

void S21Matrix::setRows(int n) {
  if (n < 1) throw std::invalid_argument("Row's count should be more 0");
  S21Matrix tmp(n, cols_);
  int min_rows = n <= rows_ ? n : rows_;
  for (int i = 0; i < min_rows; i++) {
    for (int j = 0; j < cols_; j++) {
      tmp.matrix_[i][j] = matrix_[i][j];
    }
  }
  *this = tmp;
}

void S21Matrix::setCols(int m) {
  if (m < 1) throw std::invalid_argument("Column's count should be more 0");
  S21Matrix tmp(rows_, m);
  int min_cols = m <= cols_ ? m : cols_;
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < min_cols; j++) {
      tmp.matrix_[i][j] = matrix_[i][j];
    }
  }
  *this = tmp;
}

// some operators overloads

S21Matrix &S21Matrix::operator=(const S21Matrix &o) {
  if (matrix_ != nullptr) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;

    rows_ = o.rows_;
    cols_ = o.cols_;
    matrix_ = new double *[rows_];
    for (int i = 0; i < rows_; i++) {
      matrix_[i] = new double[cols_];
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] = o.matrix_[i][j];
      }
    }
  }

  return *this;
}

S21Matrix &S21Matrix::operator=(S21Matrix &&o) {
  if (matrix_ != nullptr) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;

    rows_ = o.rows_;
    cols_ = o.cols_;
    matrix_ = o.matrix_;

    o.rows_ = 0;
    o.cols_ = 0;
    o.matrix_ = nullptr;
  }

  return *this;
}

bool S21Matrix::operator==(const S21Matrix &other) {
  return this->EqMatrix(other);
}

double &S21Matrix::operator()(int row, int col) { return matrix_[row][col]; }

double &S21Matrix::operator()(int row, int col) const {
  return matrix_[row][col];
}

S21Matrix &S21Matrix::operator+=(const S21Matrix &other) {
  SumMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator+(const S21Matrix &other) {
  S21Matrix res = S21Matrix(*this);
  res.SumMatrix(other);
  return res;
}

S21Matrix &S21Matrix::operator-=(const S21Matrix &other) {
  SubMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) {
  S21Matrix res = S21Matrix(*this);
  res.SubMatrix(other);
  return res;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) {
  S21Matrix res = S21Matrix(*this);
  res.MulMatrix(other);
  return res;
}

S21Matrix S21Matrix::operator*(const double num) {
  S21Matrix res = S21Matrix(*this);
  res.MulNumber(num);
  return res;
}

S21Matrix S21Matrix::operator*=(const S21Matrix &other) {
  MulMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*=(const double num) {
  MulNumber(num);
  return *this;
}

// some public methods

bool S21Matrix::EqMatrix(const S21Matrix &other) {
  bool result = true;
  if (rows_ == 0 && cols_ == 0 && other.rows_ == 0 && other.cols_ == 0) {
    result = true;
  } else if (rows_ != other.rows_ || cols_ != other.cols_) {
    result = false;
  } else {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        if (std::fabs(matrix_[i][j] - other.matrix_[i][j]) > 1e-8) {
          result = false;
          break;
        }
      }
    }
  }
  return result;
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (matrix_ == nullptr || cols_ < 1 || rows_ < 1 ||
      other.matrix_ == nullptr || other.cols_ < 1 || other.rows_ < 1) {
    throw std::invalid_argument("Incorrect matrix");
  } else if (cols_ != other.cols_ || rows_ != other.rows_) {
    throw std::invalid_argument("Different dimensions of matrices");
  } else {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (matrix_ == nullptr || cols_ < 1 || rows_ < 1 ||
      other.matrix_ == nullptr || other.cols_ < 1 || other.rows_ < 1) {
    throw std::invalid_argument("Incorrect matrix");
  } else if (cols_ != other.cols_ || rows_ != other.rows_) {
    throw std::invalid_argument("Different dimensions of matrices");
  } else {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  if (matrix_ == nullptr || cols_ < 1 || rows_ < 1) {
    throw std::invalid_argument("Incorrect matrix");
  } else {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (matrix_ == nullptr || cols_ < 1 || rows_ < 1 ||
      other.matrix_ == nullptr || other.cols_ < 1 || other.rows_ < 1) {
    throw std::invalid_argument("Incorrect matrix");
  } else if (cols_ != other.rows_) {
    throw std::invalid_argument("Different dimensions of matrices");
  } else {
    S21Matrix res(rows_, other.cols_);
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < other.cols_; j++) {
        for (int k = 0; k < other.rows_; k++)
          res.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
    *this = res;
  }
}

S21Matrix S21Matrix::Transpose() {
  if (matrix_ == nullptr || cols_ < 1 || rows_ < 1) {
    throw std::invalid_argument("Incorrect matrix");
  } else {
    S21Matrix res(cols_, rows_);
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) res.matrix_[j][i] = matrix_[i][j];
    }
    *this = res;
  }
  return *this;
}

S21Matrix S21Matrix::GetMinor(int row, int col) {
  S21Matrix tmp(rows_ - 1, cols_ - 1);
  for (int i = 0, res_i = 0; i < rows_; i++) {
    for (int j = 0, res_j = 0; j < cols_; j++) {
      if (i != row && j != col) {
        tmp.matrix_[res_i][res_j] = matrix_[i][j];
        res_j++;
        if (res_j == cols_ - 1) {
          res_j = 0;
          res_i++;
        }
      }
    }
  }
  return tmp;
}

S21Matrix S21Matrix::CalcComplements() {
  double det = 0.0;
  S21Matrix res(rows_, cols_);
  if (matrix_ == nullptr || cols_ < 1 || rows_ < 1) {
    throw std::invalid_argument("Incorrect matrix");
  } else if (cols_ != rows_) {
    throw std::invalid_argument("The matrix is ​​not square");
  } else {
    if (rows_ == 1) {
      res.matrix_[0][0] = 1;
    } else {
      S21Matrix minor(rows_ - 1, cols_ - 1);
      for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
          minor = GetMinor(i, j);
          det = minor.Determinant();
          res.matrix_[i][j] = pow(-1, (i + j)) * det;
        }
      }
    }
  }
  return res;
}

double S21Matrix::Determinant() {
  double det = 0.0;
  double sign = 1.0;
  if (matrix_ == nullptr || cols_ < 1 || rows_ < 1) {
    throw std::invalid_argument("Incorrect matrix");
  } else if (cols_ != rows_) {
    throw std::invalid_argument("The matrix is ​​not square");
  } else {
    if (rows_ == 1) {
      det = matrix_[0][0];
    } else if (rows_ == 2) {
      det = matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
    } else {
      S21Matrix tmp(rows_ - 1, cols_ - 1);
      for (int i = 0; i < rows_; i++) {
        tmp = GetMinor(0, i);
        sign = (i % 2) ? -1.0 : 1.0;
        det += sign * matrix_[0][i] * tmp.Determinant();
      }
    }
  }
  return det;
}

S21Matrix S21Matrix::InverseMatrix() {
  double det = 0.0;
  S21Matrix res(1, 1);
  if (matrix_ == nullptr || cols_ < 1 || rows_ < 1) {
    throw std::invalid_argument("Incorrect matrix");
  } else if (cols_ != rows_) {
    throw std::invalid_argument("The matrix is ​​not square");
  } else {
    det = Determinant();
    if (std::fabs(det) < 1e-8) {
      throw std::invalid_argument("The determinant of the matrix is ​​0");
    } else {
      S21Matrix adj_matrix = CalcComplements();
      res = adj_matrix.Transpose();
      res.MulNumber(1 / det);
    }
  }
  return res;
}
