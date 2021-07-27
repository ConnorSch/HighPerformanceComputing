//
// This file is part of the course materials for AMATH483/583 at the University of Washington,
// Spring 2020
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Andrew Lumsdaine
//


#include "Matrix.hpp"
#include <string>
#include <iostream>

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

int main() {
  std::string A = "ten";
  int B = 10;
  Matrix C(10, 10);

  multiply(A, B, C);

  return 0;
}