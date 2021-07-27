//
// This file is part of the course materials for AMATH483/583 at the University of Washington,
// Spring 2018
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Andrew Lumsdaine
//
#ifndef AMATH583_CSRMATRIX_HPP
#define AMATH583_CSRMATRIX_HPP

#include "Matrix.hpp"
#include "Vector.hpp"

#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <vector>

#include <future>

class CSRMatrix {
public:
  CSRMatrix(size_t M, size_t N) : is_open(false), num_rows_(M), num_cols_(N), row_indices_(num_rows_ + 1, 0) {}

  void open_for_push_back() { is_open = true; }

  void close_for_push_back() {
    is_open = false;
    for (size_t i = 0; i < num_rows_; ++i) {
      row_indices_[i + 1] += row_indices_[i];
    }
    for (size_t i = num_rows_; i > 0; --i) {
      row_indices_[i] = row_indices_[i - 1];
    }
    row_indices_[0] = 0;
  }

  void push_back(size_t i, size_t j, double value) {
    assert(is_open);
    assert(i < num_rows_ && i >= 0);
    assert(j < num_cols_ && j >= 0);

    ++row_indices_[i];
    col_indices_.push_back(j);
    storage_.push_back(value);
  }

  void clear() {
    col_indices_.clear();
    storage_.clear();
    std::fill(row_indices_.begin(), row_indices_.end(), 0);
  }

  size_t num_rows() const { return num_rows_; }
  size_t num_cols() const { return num_cols_; }
  size_t num_nonzeros() const { return storage_.size(); }

  void stream_coordinates(std::ostream& output_file) const {
    for (size_t i = 0; i < num_rows_; ++i) {
      for (size_t j = row_indices_[i]; j < row_indices_[i + 1]; ++j) {
        output_file << i << " ";
        output_file << col_indices_[j] << " ";
        output_file << storage_[j];
        output_file << std::endl;
      }
    }
  }

  void matvec(const Vector& x, Vector& y) const {
#pragma omp parallel for
    for (size_t i = 0; i < num_rows_; ++i) {
      for (size_t j = row_indices_[i]; j < row_indices_[i + 1]; ++j) {
        y(i) += storage_[j] * x(col_indices_[j]);
      }
    }
  }

  void t_matvec(const Vector& x, Vector& y) const {
    for (size_t i = 0; i < num_rows_; ++i) {
      for (size_t j = row_indices_[i]; j < row_indices_[i + 1]; ++j) {
        y(col_indices_[j]) += storage_[j] * x(i);
      }
    }
  }

  void matmat(const Matrix& B, Matrix& C) const {

    if (B.num_cols() <= 2) {
      for (size_t k = 0; k < B.num_cols(); ++k) {
	
#pragma omp parallel for 
	for (size_t i = 0; i < num_rows_; ++i) {
	  for (size_t j = row_indices_[i]; j < row_indices_[i + 1]; ++j) {
	    
	    double alpha  = storage_[j];
	    size_t jj = col_indices_[j];
	    
	    C(i, k) += alpha * B(jj, k);
	  }
	}
      }
    } else {
      
#pragma omp parallel for 
      for (size_t i = 0; i < num_rows_; ++i) {
	for (size_t j = row_indices_[i]; j < row_indices_[i + 1]; ++j) {
	  
	  double alpha  = storage_[j];
	  size_t jj = col_indices_[j];
	  
	  for (size_t k = 0; k < B.num_cols(); ++k) {
	    C(i, k) += alpha * B(jj, k);
	  }
	}
      }
    }
  }

  void stochastify() {
    for (size_t i = 0; i < num_rows_; ++i) {
      double degree = static_cast<double>(row_indices_[i + 1] - row_indices_[i]);
      for (size_t j = row_indices_[i]; j < row_indices_[i + 1]; ++j) {
        storage_[j] = 1. / degree;
      }
    }
  }

  void piscetize(size_t xpoints, size_t ypoints) {
    assert(num_rows() == num_cols());
    assert(xpoints * ypoints == num_rows());
    
    clear();
    open_for_push_back();
    
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
    close_for_push_back();
  }


private:
  bool                is_open;
  size_t              num_rows_, num_cols_;
  std::vector<size_t> row_indices_, col_indices_;
  std::vector<double> storage_;
};

#endif    // AMATH583_CSRMATRIX_HPP
