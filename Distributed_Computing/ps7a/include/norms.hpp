//
// This file is part of the course materials for AMATH483/583 at the University of Washington,
// Spring 2020
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Andrew Lumsdaine
//

#include <cmath>
#include <iostream>

#include "Timer.hpp"
#include "Vector.hpp"
#include "amath583.hpp"

#include "omp.h"

double norm_seq(const Vector& x) {
  double sum = 0;

  for (size_t i = 0; i < x.num_rows(); ++i) {
    sum += x(i) * x(i);
  }
  return std::sqrt(sum);
}

double norm_block_reduction(const Vector& x) {
  double sum = 0;

  /* Fix Me (using reduction) */
#pragma omp parallel reduction(+ : sum) shared(x)
  {
    size_t tid       = omp_get_thread_num();
    size_t parts     = omp_get_num_threads();
    size_t blocksize = x.num_rows() / parts;
    size_t begin     = tid * blocksize;
    size_t end       = (tid + 1) * blocksize;
    if (tid == parts - 1) {
      end = x.num_rows();
    }

    for (size_t i = begin; i < end; ++i) {
      sum += x(i) * x(i);
    }
  }
  return std::sqrt(sum);
}

double norm_block_critical(const Vector& x) {
  double sum = 0;

  /* Fix Me (without reduction) */
#pragma omp parallel shared(x)
  {
    size_t tid       = omp_get_thread_num();
    size_t parts     = omp_get_num_threads();
    size_t blocksize = x.num_rows() / parts;
    size_t begin     = tid * blocksize;
    size_t end       = (tid + 1) * blocksize;
    if (tid == parts - 1) {
      end = x.num_rows();
    }

    double local_sum = 0;
    for (size_t i = begin; i < end; ++i) {
      local_sum += x(i) * x(i);
    }
#pragma omp critical
    sum += local_sum;
  }
  return std::sqrt(sum);
}

double norm_cyclic_critical(const Vector& x) {
  double sum = 0;

  /* Parallelize me */
#pragma omp parallel shared(x)
  {
    size_t tid    = omp_get_thread_num();
    size_t parts  = omp_get_num_threads();
    size_t begin  = tid;
    size_t end    = x.num_rows();
    size_t stride = parts;

    double local_sum = 0.0;
    for (size_t i = begin; i < end; i += stride) {
      local_sum += x(i) * x(i);
    }
#pragma omp critical
    sum += local_sum;
  }
  return std::sqrt(sum);
}

double norm_cyclic_reduction(const Vector& x) {
  double sum = 0;

  /* Parallelize me */
#pragma omp parallel reduction(+ : sum) shared(x)
  {
    size_t tid    = omp_get_thread_num();
    size_t parts  = omp_get_num_threads();
    size_t begin  = tid;
    size_t end    = x.num_rows();
    size_t stride = parts;

    for (size_t i = begin; i < end; i += stride) {
      sum += x(i) * x(i);
    }
  }

  return std::sqrt(sum);
}

double norm_parfor(const Vector& x) {
  double sum = 0;
  // #pragma omp parallel for reduction(+:sum) shared(x) schedule(static,x.num_rows()/omp_get_num_threads())
  // #pragma omp parallel for reduction(+ : sum)

  /* Parallelize me with parallel for */
#pragma omp parallel for reduction(+:sum)
  for (size_t i = 0; i < x.num_rows(); ++i) {
    sum += x(i) * x(i);
  }

  return std::sqrt(sum);
}
