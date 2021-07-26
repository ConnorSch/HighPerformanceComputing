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

#include "getenv.hpp"

int main(int argc, char* argv[]) {

  for (int i = 1; i < argc; ++i) {
    std::string a = getenv(argv[i]);
    std::cout << argv[i] << "=" << a << std::endl;
  }

  return 0;
}