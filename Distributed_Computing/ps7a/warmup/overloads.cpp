//
// This file is part of the course materials for AMATH483/583 at the University of Washington,
// Spring 2020
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Andrew Lumsdaine
//

#include <cstddef>

#include "CSRMatrix.hpp"
#include "Matrix.hpp"

template <class Matrix_1_t, class Matrix_2_t, class Matrix_3_t>
void multiply(const Matrix_1_t& A, const Matrix_2_t& B, Matrix_3_t& C) {
  for (size_t i = 0; i < C.num_rows(); ++i) {
    for (size_t j = 0; j < C.num_cols(); ++j) {
      for (size_t k = 0; k < A.num_cols(); ++k) {
        C(i, j) += A(i, k) * B(k, j);
      }
    }
  }
}

template <class SparseMatrix_t, class Matrix_1_t, class Matrix_2_t>
void multiply(const SparseMatrix_t& A, const Matrix_1_t& B, Matrix_2_t& C) {
  A.matmat(B, C);
}

int main() {
  CSRMatrix A(10, 10);
  Matrix    B(10, 10);
  Matrix    C(10, 10);
  Matrix    D(10, 10);

  multiply(A, C, D);
  multiply(B, C, D);

  return 0;
}