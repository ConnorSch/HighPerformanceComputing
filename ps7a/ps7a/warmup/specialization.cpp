//
// This file is part of the course materials for AMATH483/583 at the University of Washington,
// Spring 2020
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Andrew Lumsdaine
//

#include <iostream>

#include "Matrix.hpp"

template <class Matrix_1_t, class Matrix_2_t, class Matrix_3_t>
void multiply(const Matrix_1_t& A, const Matrix_2_t& B, Matrix_3_t& C) {
  std::cout << "Generic multiply" << std::endl;
  for (size_t i = 0; i < C.num_rows(); ++i) {
    for (size_t j = 0; j < C.num_cols(); ++j) {
      for (size_t k = 0; k < A.num_cols(); ++k) {
        C(i, j) += A(i, k) * B(k, j);
      }
    }
  }
}

template <>
void multiply(const ColMatrix& A, const ColMatrix& B, ColMatrix& C) {
  std::cout << "Specialized ColMatrix multiply" << std::endl;
  for (size_t j = 0; j < C.num_cols(); ++j) {
    for (size_t k = 0; k < A.num_cols(); ++k) {
      for (size_t i = 0; i < C.num_rows(); ++i) {
        C(i, j) += A(i, k) * B(k, j);
      }
    }
  }
}

template <>
void multiply(const RowMatrix& A, const RowMatrix& B, RowMatrix& C) {
  std::cout << "Specialized RowMatrix multiply" << std::endl;
  for (size_t i = 0; i < C.num_rows(); ++i) {
    for (size_t k = 0; k < A.num_cols(); ++k) {
      for (size_t j = 0; j < C.num_cols(); ++j) {
        C(i, j) += A(i, k) * B(k, j);
      }
    }
  }
}

int main() {

  RowMatrix A(10, 10);
  RowMatrix B(10, 10);
  RowMatrix C(10, 10);

  ColMatrix D(10, 10);
  ColMatrix E(10, 10);
  ColMatrix F(10, 10);

  multiply(A, B, C);
  multiply(D, E, F);
  multiply(A, B, D);

  return 0;
}