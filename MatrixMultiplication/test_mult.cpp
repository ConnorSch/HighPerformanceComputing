

#include "Matrix.hpp"
#include "amath583.hpp"


#define CATCH_CONFIG_MAIN    // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include <cstddef>
#include "Matrix.hpp"
#include "amath583.hpp"


TEST_CASE("Matrices can be created and initialized", "[Matrix]") {
  const size_t m_rows = 32, n_cols = 64;
  Matrix A(m_rows, n_cols);
  REQUIRE(A.num_rows() == m_rows);
  REQUIRE(A.num_cols() == n_cols);

  SECTION("test initial values") {
    for (size_t i = 0; i < m_rows; ++i) {
      for (size_t j = 0; j < n_cols; ++j) {
        REQUIRE(A(i, j) == 0.0);
      }
    }
  }

  SECTION("test filling values") {
    for (size_t i = 0; i < m_rows; ++i) {
      for (size_t j = 0; j < n_cols; ++j) {
        A(i, j) = (50 - i) * j;
      }
    }
    for (size_t i = 0; i < m_rows; ++i) {
      for (size_t j = 0; j < n_cols; ++j) {
        REQUIRE(A(i, j) == (50 - i) * j);
      }
    }
  }
}

template <class Fun>
double run_test(Fun f) {
  const size_t m_rows = 32, n_cols = 64;
  Matrix A(m_rows, n_cols);
  Matrix B(n_cols, m_rows);
  Matrix C (A.num_rows(), B.num_cols());
  Matrix D (A.num_rows(), B.num_cols());
  randomize(A);
  randomize(B);
  REQUIRE(f_norm(A) != 0.0);
  REQUIRE(f_norm(B) != 0.0);
  REQUIRE(f_norm(C) == 0.0);
  REQUIRE(f_norm(D) == 0.0);

  for (size_t i = 0; i < C.num_rows(); ++i) {
    for (size_t j = 0; j < C.num_cols(); ++j) {
      for (size_t k = 0; k < A.num_cols(); ++k) {
        C(i, j) += A(i, k) * B(k, j);
      }
    }
  }
  REQUIRE(f_norm(C) != 0.0);
  f(A, B, D);
  REQUIRE(f_norm(D) != 0.0);

  return(f_norm(C-D)/f_norm(C));
}

TEST_CASE("Matrix multiply: C = A*B 0", "[mult_0]") {
  REQUIRE(run_test(mult_0) < 1.e-12);
} 
TEST_CASE("Matrix multiply: C = A*B 1", "[mult_1]") {
  REQUIRE(run_test(mult_1) < 1.e-12);
} 
TEST_CASE("Matrix multiply: C = A*B 2", "[mult_2]") {
  REQUIRE(run_test(mult_2) < 1.e-12);
} 
TEST_CASE("Matrix multiply: C = A*B 3", "[mult_3]") {
  REQUIRE(run_test(mult_3) < 1.e-12);
}