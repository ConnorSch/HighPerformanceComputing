

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


TEST_CASE("Matrices can be transpose", "[Matrix_transpose]") {
  const size_t m_rows = 35, n_cols = 57;
  Matrix A(m_rows, n_cols);
  Matrix B = transpose(A);
  REQUIRE(A.num_rows() == B.num_cols());
  REQUIRE(A.num_cols() == B.num_rows());
  Matrix C = transpose(B);
  REQUIRE(A.num_rows() == C.num_rows());
  REQUIRE(A.num_cols() == C.num_cols());

  A(0,0) = 1.25;
  A(3,3) = -1.3;
  A(0,13) = 8.67;
  A(13,0) = -5.309;

  B = transpose(A);
  REQUIRE(B(0,0) == 1.25);
  REQUIRE(B(3,3) == -1.3);
  REQUIRE(B(0,13) == -5.309);
  REQUIRE(B(13,0) == 8.67);
  REQUIRE(B(1,1) == 0.0);

  C = transpose(B);
  REQUIRE(C(0,0) == 1.25);
  REQUIRE(C(3,3) == -1.3);
  REQUIRE(C(0,13) == 8.67);
  REQUIRE(C(13,0) == -5.309);
  REQUIRE(C(1,1) == 0.0);
}


template <class Fun>
void run_test(Fun f) {
  for (size_t m_rows = 32; m_rows <= 128; m_rows *= 2) {
  const size_t n_cols = 64;
  Matrix A(m_rows, n_cols);
  Matrix B(m_rows, n_cols);
  randomize(A);
  randomize(B);

  Matrix C = transpose(B);
  REQUIRE(f_norm(C) != 0.0);

  Matrix E(m_rows, m_rows);
  Matrix F(m_rows, m_rows);
  REQUIRE(f_norm(E) == 0.0);
  REQUIRE(f_norm(F) == 0.0);

  mult_0(A, C, E);
  f(A, B, F);
  REQUIRE(f_norm(E) != 0.0);
  REQUIRE(f_norm(F) != 0.0);
  REQUIRE(f_norm(E-F) < 1.e-12*f_norm(E));
  }
}

TEST_CASE("Matrix multiply transpose: C = A*B^T 0", "[trans_mult_0]") {
  run_test(mult_trans_0);
}
TEST_CASE("Matrix multiply transpose: C = A*B^T 1", "[trans_mult_1]") {
  run_test(mult_trans_1);
}
TEST_CASE("Matrix multiply transpose: C = A*B^T 2", "[trans_mult_2]") {
  run_test(mult_trans_2);
}
TEST_CASE("Matrix multiply transpose: C = A*B^T 3", "[trans_mult_3]") {
  run_test(mult_trans_3);
}
TEST_CASE("Matrix multiply transpose: C = A*B^T 4", "[trans_mult_4]") {
  for (size_t m_rows = 32; m_rows <= 128; m_rows *= 2) {
    Matrix A(m_rows, 64);
    randomize(A);
    Matrix B = transpose(A);
    Matrix C(m_rows, m_rows);
    Matrix D(m_rows, m_rows);
    mult_0(A, B, C);
    mult_trans_4(A, D);
    REQUIRE(f_norm(C-D) < 1.e-12*f_norm(C));
  }
}
 
TEST_CASE("Matrix multiply transpose: C = A*B^T 5", "[trans_mult_5]") { 
  run_test(mult_trans_5);  
}