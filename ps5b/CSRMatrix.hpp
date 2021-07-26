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

// Any additional includes go here
#include <iomanip>
#include <thread>

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

  // Your overload(s) for parallel matvec and/or t_matvec go here
  // No skeleton this time

  void matvec_p(const Vector& x, Vector& y, size_t parts) const {
      size_t blocksize = num_rows_ / parts;
      std::vector<std::thread> mvf;
      for (size_t i = 0; i < parts; ++i) {
          mvf.push_back(std::thread(&CSRMatrix::matvec_helper,this, std::cref(x), std::ref(y), (i * blocksize), (i + 1) * blocksize));
      }
      for (size_t i = 0; i < parts; ++i){
          mvf[i].join();
      }
  }

  void matvec_helper(const Vector& x, Vector& y, size_t begin, size_t end) const{
      for (size_t i = begin; i < end; ++i) {
          for (size_t j = row_indices_[i]; j < row_indices_[i + 1]; ++j) {
              y(i) += storage_[j] * x(col_indices_[j]);
          }
      }
  }

  void t_matvec_p(const Vector& x, Vector& y, size_t parts) const {
    size_t blocksize = num_rows_ / parts;
    std::vector<std::thread> mvf;
    for (size_t i = 0; i < parts; ++i) {
      mvf.push_back(std::thread(&CSRMatrix::t_matvec_helper,this, std::cref(x), std::ref(y), (i * blocksize), (i + 1) * blocksize));
    }
    for (size_t i = 0; i < parts; ++i){
      mvf[i].join();
    }
  }

  void t_matvec_helper(const Vector& x, Vector& y, size_t begin, size_t end) const{
    for (size_t i = begin; i < end; ++i) {
      for (size_t j = row_indices_[i]; j < row_indices_[i + 1]; ++j) {
        y(col_indices_[j]) += storage_[j] * x(i);
      }
    }
  }

  void matvec(const Vector& x, Vector& y) const {
    for (size_t i = 0; i < num_rows_; ++i) {
      double tmp = y(i);
      for (size_t j = row_indices_[i]; j < row_indices_[i + 1]; ++j) {
        tmp += storage_[j] * x(col_indices_[j]);
      }
      y(i) = tmp;
    }
  }

  void t_matvec(const Vector& x, Vector& y) const {
    for (size_t i = 0; i < num_rows_; ++i) {
      for (size_t j = row_indices_[i]; j < row_indices_[i + 1]; ++j) {
        y(col_indices_[j]) += storage_[j] * x(i);
      }
    }
  }

  void matmat(const Matrix& B, Matrix& C) const { /* Write Me */
    for (size_t i = 0; i < num_rows_; ++i) {
      for (size_t j = row_indices_[i]; j < row_indices_[i + 1]; ++j) {
        for (size_t k = 0; k < B.num_cols(); ++k) {
          C(i, k) += storage_[j] * B(col_indices_[j], k);
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

private:
  bool                is_open;
  size_t              num_rows_, num_cols_;
  std::vector<size_t> row_indices_, col_indices_;
  std::vector<double> storage_;
};

#endif    // AMATH583_CSRMATRIX_HPP
