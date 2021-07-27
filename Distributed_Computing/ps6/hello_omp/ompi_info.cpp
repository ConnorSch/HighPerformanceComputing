//
// This file is part of the course materials for AMATH483/583 at the University of Washington,
// Spring 2020
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Andrew Lumsdaine
//

#include <cstdlib>
#include <iostream>
#include <string>
#include <thread>

#include <omp.h>

#include "getenv.hpp"

int omp_thread_count() {
  int n = 0;
#pragma omp parallel reduction(+:n)
  n += 1;
  return n;
}

int main() {

  std::string envName = "OMP_NUM_THREADS";
  std::cout << envName << "        = " << getenv(envName) << std::endl;

  std::cout << "hardware_concurrency() = " << std::thread::hardware_concurrency() << std::endl;
  std::cout << "omp_get_max_threads()  = " << omp_get_max_threads() << std::endl;
  std::cout << "omp_get_num_threads()  = " << omp_get_num_threads() << std::endl;
  std::cout << "omp_thread_count() = " << omp_thread_count() << std::endl;

  return 0;
}
