

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

TEST_CASE("Take f norm of a Matrix", "[Two Norm]") {
  Matrix A(13, 17);
  SECTION("f_norm") {
    REQUIRE(f_norm(A) == 0.0);
    A(0, 0) = 1;
    REQUIRE(f_norm(A) == 1.0);
    A(4,9) = A(3,9) = A(1,1) = 1.0;
    REQUIRE(f_norm(A) == 2.0);
  }
}

TEST_CASE("Matrices can be substracted", "[operator-]") {
   Matrix A(86, 75);
   Matrix B(86, 75);
   randomize(A);
   randomize(B);

   REQUIRE(f_norm(A) > 0);
   REQUIRE(f_norm(B) > 0);
   REQUIRE(f_norm(A-A) == 0.0);   
   REQUIRE(f_norm(B-B) == 0.0);   
   REQUIRE(f_norm(A-B) != 0.0);      
}