//
// This file is part of the course materials for AMATH483/583 at the University of Washington,
// Spring 2020
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Andrew Lumsdaine
//

#ifndef AMATH583_CNORM_HPP
#define AMATH583_CNORM_HPP

#include "Timer.hpp"
#include "Vector.hpp"
#include "amath583.hpp"
#include "norm_utils.hpp"

#include <cassert>
#include <cmath>
#include <future>
#include <iomanip>
#include <iostream>
#include <string>
#include <thread>

// Write me
double cyclic_two_norm(const Vector& x, size_t partitions) {
  double sum = 0.0;

  size_t stride = partitions;
  std::vector<std::future <double>> norm;
  for (int i = 0; i < partitions; ++i){
      norm.push_back(std::async(std::launch::async, [&x, stride, i]() -> double {
          double partial_x = 0.0;
          for (size_t j = i ; j < x.num_rows(); j += stride) {
              partial_x += x(j) * x(j);
          }
          return partial_x;
      }));
  }

  for (int i = 0; i < partitions; ++i){
      sum += norm[i].get();
  }

  return std::sqrt(sum);
}



#endif    // AMATH583_CNORM_HPP
