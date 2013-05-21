//! \author Stephen McGruer

#ifndef SRC_MATRIX_INL_H_
#define SRC_MATRIX_INL_H_

#include "./matrix.h"

namespace computer_animation {

template <typename T> Matrix<T>::Matrix(int rows, int cols)
    : data_(rows * cols, 0.0f), num_rows_(rows), num_cols_(cols) {
}

template <typename T> T Matrix<T>::operator()(int row, int col) const {
  return data_[row * num_cols_ + col];
}

template <typename T> T& Matrix<T>::operator()(int row, int col) {
  return data_[row * num_cols_ + col];
}

template <typename T> void Matrix<T>::PrintMatrix() {
  printf("FloatMatrix: %dx%d\n", num_cols_, num_rows_);
  for (int row = 0; row < num_rows_; row++) {
    printf("|");
    for (int col = 0; col < num_cols_; col++) {
      printf("%f ", operator()(row, col));
    }
    printf("|\n");
  }
  printf("\n");
}

template <typename T> Matrix<T> operator*(const Matrix<T>& a,
    const Matrix<T>& b) {
  if (a.num_cols() != b.num_rows()) {
    return Matrix<T>(0, 0);
  }

  Matrix<T> result(a.num_rows(), b.num_cols());
  for (int i = 0; i < result.num_rows(); i++) {
    for (int j = 0; j < result.num_cols(); j++) {
      result(i, j) = 0;
      for (int k = 0; k < a.num_cols(); k++) {
        result(i, j) += a(i, k) * b(k, j);
      }
    }
  }

  return result;
}
}

#endif  // SRC_MATRIX_INL_H_
