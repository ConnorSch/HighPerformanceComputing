//
// This file is part of the course materials for AMATH483/583 at the University of Washington,
// Spring 2020
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Andrew Lumsdaine
//

#define CATCH_CONFIG_MAIN    // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include "Vector.hpp"
#include "amath583.hpp"
#include <cstddef>

TEST_CASE("Vectors can be created and initialized", "[Vector]") {
  Vector x(50);
  REQUIRE(x.num_rows() == 50);

  SECTION("test initial values") {
    for (size_t i = 0; i < 50; ++i) {
      REQUIRE(x(i) == 0.0);
    }
  }

  SECTION("test filling values") {
    for (size_t i = 0; i < 50; ++i) {
      x(i) = 50 - i;
    }
    for (size_t i = 0; i < 50; ++i) {
      REQUIRE(x(i) == 50 - i);
    }
  }
}

TEST_CASE("Zeroize vector", "[Zeroize]") {
  Vector x(50);
  SECTION("zeroize") {
    for (size_t i = 0; i < 50; ++i) {
      x(i) = i * i;
    }
    for (size_t i = 0; i < 50; ++i) {
      REQUIRE(x(i) == i * i);
    }
    zeroize(x);
    for (size_t i = 0; i < 50; ++i) {
      REQUIRE(x(i) == 0);
    }
  }
}
