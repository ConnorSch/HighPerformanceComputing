//
// This file is part of the course materials for AMATH483/583 at the University of Washington,
// Spring 2020
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Andrew Lumsdaine
//
#ifndef AMATH583_AOS_HPP
#define AMATH583_AOS_HPP

#include <cassert>
#include <tuple>
#include <vector>

#include "Vector.hpp"

class AOSMatrix {
private:
  typedef std::tuple<size_t, size_t, double> element;

public:
  AOSMatrix(size_t M, size_t N) : num_rows_(M), num_cols_(N) {}

  void push_back(size_t i, size_t j, double val) { /* Write Me */
    assert(i < num_rows_ && i >= 0);
    assert(j < num_cols_ && j >= 0);

    storage_.push_back(element(i, j, val));
  }

  void clear() { storage_.clear(); }

  void reserve(size_t n) {
    assert(n >= 0);

    storage_.reserve(n);
  }

  size_t num_rows() const { return num_rows_; }
  size_t num_cols() const { return num_cols_; }
  size_t num_nonzeros() const { return storage_.size(); }

  void stream_coordinates(std::ostream& output_file) const {
    for (size_t i = 0; i < storage_.size(); ++i) {
      output_file << std::get<0>(storage_[i]) << " ";
      output_file << std::get<1>(storage_[i]) << " ";
      output_file << std::get<2>(storage_[i]) << " ";
      output_file << std::endl;
    }
  }

  void matvec(const Vector& x, Vector& y) const {
    for (size_t k = 0; k < storage_.size(); ++k) {
      y(std::get<0>(storage_[k])) += std::get<2>(storage_[k]) * x(std::get<1>(storage_[k]));
    }
  }

  void t_matvec(const Vector& x, Vector& y) const {
    for (size_t k = 0; k < storage_.size(); ++k) {
      y(std::get<1>(storage_[k])) += std::get<2>(storage_[k]) * x(std::get<0>(storage_[k]));
    }
  }

  void matmat(const Matrix& B, Matrix& C) const {
    for (size_t i = 0; i < storage_.size(); ++i) {
      for (size_t k = 0; k < B.num_cols(); ++k) {
        C(std::get<0>(storage_[i]), k) += std::get<2>(storage_[i]) * B(std::get<1>(storage_[i]), k);
      }
    }
  }

  void piscetize(size_t xpoints, size_t ypoints) {
    assert(num_rows() == num_cols());
    assert(xpoints * ypoints == num_rows());
    
    clear();
    
    for (size_t j = 0; j < xpoints; j++) {
      for (size_t k = 0; k < ypoints; k++) {
	size_t jrow = j * ypoints + k;
	
	if (j != 0) {
	  size_t jcol = (j - 1) * ypoints + k;
	  push_back(jrow, jcol, -1.0);
	}
	if (k != 0) {
	  size_t jcol = j * ypoints + (k - 1);
	  push_back(jrow, jcol, -1.0);
	}
	
	push_back(jrow, jrow, 4.0);
	
	if (k != ypoints - 1) {
	  size_t jcol = j * ypoints + (k + 1);
	  push_back(jrow, jcol, -1.0);
	}
	if (j != xpoints - 1) {
	  size_t jcol = (j + 1) * ypoints + k;
	  push_back(jrow, jcol, -1.0);
	}
      }
    }
  }


private:
  size_t               num_rows_, num_cols_;
  std::vector<element> storage_;
};

#endif    // AMATH583_AOS_HPP
