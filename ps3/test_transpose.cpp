

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