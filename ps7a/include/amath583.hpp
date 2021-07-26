//
// This file is part of the course materials for AMATH483/583 at the University of Washington,
// Spring 2020
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Andrew Lumsdaine
//

#ifndef AMATH583_AMATH583_HPP
#define AMATH583_AMATH583_HPP

#include "util.hpp"
#include "Matrix.hpp"
#include "Vector.hpp"
#include <algorithm>
#include <cassert>
#include <cmath>
#include <functional>
#include <random>


// ----------------------------------------------------------------
//
// Vector arithmetic
//
// ----------------------------------------------------------------
template <class Vector_t, 
	  std::enable_if_t<is_dense_vector <Vector_t>::value>* = nullptr >
void zeroize(Vector_t& x) {
  for (size_t i = 0; i < x.num_rows(); ++i) {
    x(i) = 0.0;
  }
}

template <class Vector_t, 
	  std::enable_if_t<is_dense_vector <Vector_t>::value>* = nullptr >
void unitize(Vector_t& x) {
  for (size_t i = 0; i < x.num_rows(); ++i) {
    x(i) = 1.0;
  }
}

template <class Vector_t,
	  std::enable_if_t<is_dense_vector <Vector_t>::value>* = nullptr >
void randomize(Vector_t& x, double scale = 1.0, double mean = 0.0) {
  std::default_random_engine             generator;
  std::uniform_real_distribution<double> distribution(mean - scale, mean + scale);
  static auto                            dice = std::bind(distribution, generator);

  for (size_t i = 0; i < x.num_rows(); ++i) {
    x(i) = dice();
  }
}

template <class Vector_t, 
	  std::enable_if_t<is_dense_vector <Vector_t>::value>* = nullptr >
double one_norm(const Vector_t& x) {
  double sum = 0.0;
  for (size_t i = 0; i < x.num_rows(); ++i) {
    sum += std::abs(x(i));
  }
  return sum;
}

template <class Vector_t, 
	  std::enable_if_t<is_dense_vector <Vector_t>::value>* = nullptr >
double two_norm(const Vector_t& x) {
  double sum = 0.0;
  for (size_t i = 0; i < x.num_rows(); ++i) {
    sum += x(i) * x(i);
  }
  return std::sqrt(sum);
}

template <class Vector_t, 
	  std::enable_if_t<is_dense_vector <Vector_t>::value>* = nullptr >
double inf_norm(const Vector_t& x);

template <class Vector_t, 
	  std::enable_if_t<is_dense_vector <Vector_t>::value>* = nullptr >
double p_norm(const Vector_t& x);

template <class Vector_1_t, class Vector_2_t, class Vector_3_t = Vector_1_t,
	  std::enable_if_t<   is_dense_vector <Vector_1_t>::value
			    && is_dense_vector <Vector_2_t>::value>* = nullptr >
Vector_3_t operator+(const Vector_1_t& x, const Vector_2_t& y);

template <class Vector_1_t, class Vector_2_t, class Vector_3_t = Vector_1_t,
	  std::enable_if_t<   is_dense_vector <Vector_1_t>::value
			      && is_dense_vector <Vector_2_t>::value>* = nullptr >
Vector_3_t operator-(const Vector_1_t& x, const Vector_2_t& y) {
  Vector_3_t z(x.num_rows());
  for (size_t i = 0; i < z.num_rows(); ++i) {
    z(i) = x(i) - y(i);
  }
  return z;
}

template <class Vector_t, 
	  std::enable_if_t<is_dense_vector <Vector_t>::value>* = nullptr >
Vector_t& operator*=(Vector_t& x, double alpha) {
  for (size_t i = 0; i < x.num_rows(); ++i) {
    x(i) *= alpha;
  }
  return x;
}

template <class Vector_t, 
	  std::enable_if_t<is_dense_vector <Vector_t>::value>* = nullptr >
Vector_t& operator+=(Vector_t& x, double alpha) {
  for (size_t i = 0; i < x.num_rows(); ++i) {
    x(i) += alpha;
  }
  return x;
}

template <class Vector_1_t, class Vector_2_t, class Vector_3_t = Vector_1_t,
	  std::enable_if_t<   is_dense_vector <Vector_1_t>::value
			    && is_dense_vector <Vector_2_t>::value>* = nullptr >
Vector_3_t& operator+=(Vector_1_t& x, const Vector_2_t& y) {
  assert(x.num_rows() == y.num_rows());
  for (size_t i = 0; i < x.num_rows(); ++i) {
    x(i) += y(i);
  }
  return x;
}

template <class Vector_t, 
	  std::enable_if_t<is_dense_vector <Vector_t>::value>* = nullptr >
Vector_t& operator-=(const Vector_t& x, const Vector_t& y);


// ----------------------------------------------------------------
//
// Matrix arithmetic
//
// ----------------------------------------------------------------
template <class Matrix_t,
	  std::enable_if_t<is_dense_matrix <Matrix_t>::value>* = nullptr >
void zeroize(Matrix_t& x);

template <class Matrix_t,
	  std::enable_if_t<is_dense_matrix <Matrix_t>::value>* = nullptr>
void randomize(Matrix_t& A) {
  std::default_random_engine             generator;
  std::uniform_real_distribution<double> distribution(2.0, 32.0);
  static auto                            dice = std::bind(distribution, generator);

  for (size_t i = 0; i < A.num_rows(); ++i) {
    for (size_t j = 0; j < A.num_cols(); ++j) {
      A(i, j) = dice();
    }
  }
}

template <class SparseMatrix_t,
	  std::enable_if_t<   is_sparse_matrix<SparseMatrix_t>::value>* = nullptr >
void piscetize(SparseMatrix_t& A, size_t xpoints, size_t ypoints) {
  A.piscetize(xpoints, ypoints);
}

template <class Matrix_t,
	  std::enable_if_t<is_dense_matrix <Matrix_t>::value>* = nullptr >
double one_norm(const Matrix_t& x);

template <class Matrix_t,
	  std::enable_if_t<is_dense_matrix <Matrix_t>::value>* = nullptr >
double two_norm(const Matrix_t& x);

template <class Matrix_t,
	  std::enable_if_t<is_dense_matrix <Matrix_t>::value>* = nullptr >
double inf_norm(const Matrix_t& x);

template <class Matrix_t,
	  std::enable_if_t<is_dense_matrix <Matrix_t>::value>* = nullptr >
double f_norm(const Matrix_t& A) {
  double sum = 0;
  for (size_t i = 0; i < A.num_rows(); ++i) {
    for (size_t j = 0; j < A.num_cols(); ++j) {
      sum += A(i, j) * A(i, j);
    }
  }
  return std::sqrt(sum);
}

template <class Matrix_1_t, class Matrix_2_t, class Matrix_3_t = Matrix_1_t,
	  std::enable_if_t<   is_dense_matrix <Matrix_1_t>::value
			   && is_dense_matrix <Matrix_2_t>::value>* = nullptr >
Matrix_3_t operator+(const Matrix_1_t& A, const Matrix_2_t& B) {
  assert(A.num_rows() == B.num_rows());
  assert(A.num_cols() == B.num_cols());
  Matrix_3_t C(A.num_rows(), A.num_cols());
  for (size_t i = 0; i < A.num_rows(); ++i) {
    for (size_t j = 0; j < A.num_cols(); ++j) {
      C(i, j) = A(i, j) + B(i, j);
    }
  }
  return C;
}

template <class Matrix_1_t, class Matrix_2_t, class Matrix_3_t = Matrix_1_t,
	  std::enable_if_t<   is_dense_matrix <Matrix_1_t>::value
			   && is_dense_matrix <Matrix_2_t>::value>* = nullptr >
Matrix_3_t operator-(const Matrix_1_t& A, const Matrix_2_t& B) {
  assert(A.num_rows() == B.num_rows());
  assert(A.num_cols() == B.num_cols());
  Matrix_3_t C(A.num_rows(), A.num_cols());
  for (size_t i = 0; i < A.num_rows(); ++i) {
    for (size_t j = 0; j < A.num_cols(); ++j) {
      C(i, j) = A(i, j) - B(i, j);
    }
  }
  return C;
}


template <class Matrix_t>
Matrix_t& operator*=(double alpha, const Matrix_t& x);

template <class Matrix_1_t, class Matrix_2_t, class Matrix_3_t = Matrix_1_t,
	  std::enable_if_t<   is_dense_matrix <Matrix_1_t>::value
			   && is_dense_matrix <Matrix_2_t>::value>* = nullptr >
Matrix_3_t& operator+=(const Matrix_1_t& x, const Matrix_2_t& y);

template <class Matrix_1_t, class Matrix_2_t, class Matrix_3_t = Matrix_1_t,
	  std::enable_if_t<   is_dense_matrix <Matrix_1_t>::value
			   && is_dense_matrix <Matrix_2_t>::value>* = nullptr >
Matrix_3_t& operator-=(const Matrix_1_t& x, const Matrix_2_t& y);


// ----------------------------------------------------------------
//
// Matrix-vector operations
//
// ----------------------------------------------------------------
template <class Matrix_t, class Vector_t,
	  std::enable_if_t<   is_dense_matrix<Matrix_t>   ::value
 		           && is_dense_vector <Vector_t>::value>* = nullptr >
Vector_t mult(const Matrix_t& A, const Vector_t& x) {
  Vector_t y(A.num_rows());
  mult(A, x, y);
  return y;
}

template <class Matrix_t, class Vector_1_t, class Vector_2_t,
	  std::enable_if_t<   is_dense_matrix<Matrix_t>   ::value
			   && is_dense_vector <Vector_1_t>::value
			   && is_dense_vector <Vector_2_t>::value>* = nullptr >
void mult(const Matrix_t& A, const Vector_1_t& x, Vector_2_t& y) {
  assert(y.num_rows() == A.num_rows());
  for (size_t i = 0; i < A.num_rows(); ++i) {
    for (size_t j = 0; j < A.num_cols(); ++j) {
      y(i) += A(i, j) * x(j);
    }
  }
}


template <class SparseMatrix_t, class Vector_t,
	  std::enable_if_t<   is_sparse_matrix<SparseMatrix_t>::value
			   && is_dense_vector <Vector_t>      ::value>* = nullptr >
Vector mult(const SparseMatrix_t& A, const Vector_t& x) {
  Vector y(A.num_rows());
  mult(A, x, y);
  return y;
}

template <class SparseMatrix_t, class Vector_t,
	  std::enable_if_t<   is_sparse_matrix<SparseMatrix_t>::value
			   && is_dense_vector <Vector_t>      ::value>* = nullptr >
Vector_t mult(const Vector_t& x, const SparseMatrix_t& A) {
  Vector_t y(A.num_rows());
  mult(x, A, y);
  return y;
}

template <class SparseMatrix_t, class Vector_1_t, class Vector_2_t,
	  std::enable_if_t<   is_sparse_matrix<SparseMatrix_t>::value
			   && is_dense_vector <Vector_1_t>    ::value
			   && is_dense_vector <Vector_2_t>    ::value>* = nullptr >
void mult(const SparseMatrix_t& A, const Vector_1_t& x, Vector_2_t& y) { 
  A.matvec(x, y); 
}

template <class SparseMatrix_t, class Vector_1_t, class Vector_2_t,
	  std::enable_if_t<   is_sparse_matrix<SparseMatrix_t>::value
			   && is_dense_vector <Vector_1_t>    ::value
			   && is_dense_vector <Vector_2_t>    ::value>* = nullptr >
void mult(const Vector_1_t& x, const SparseMatrix_t& A, Vector_2_t& y) { 
  A.t_matvec(x, y); 
}


// ----------------------------------------------------------------
//
// Matrix-Matrix operations
//
// ----------------------------------------------------------------
template <class Matrix_t,
	  std::enable_if_t<is_dense_matrix <Matrix_t>::value>* = nullptr >
Matrix_t copy(const Matrix_t& A) {
  Matrix_t B(A.num_cols(), A.num_rows());
  copy(A, B);
  return B;
}

template <class Matrix_1_t, class Matrix_2_t,
	  std::enable_if_t<   is_dense_matrix <Matrix_1_t>::value
			   && is_dense_matrix <Matrix_2_t>::value>* = nullptr >
void transpose(const Matrix_1_t& A, Matrix_2_t& At) {
  assert(At.num_rows() == A.num_cols());
  assert(At.num_cols() == A.num_rows());
  for (size_t i = 0; i < At.num_rows(); ++i) {
    for (size_t j = 0; j < At.num_cols(); ++j) {
      At(i, j) = A(j, i);
    }
  }
}

template <class Matrix_t,
	  std::enable_if_t<is_dense_matrix <Matrix_t>::value>* = nullptr >
Matrix_t transpose(const Matrix_t& A) {
  Matrix_t B(A.num_cols(), A.num_rows());
  transpose(A, B);
  return B;
}


template <class Matrix_1_t, class Matrix_2_t, class Matrix_3_t = Matrix_1_t,
	  std::enable_if_t<   is_dense_matrix <Matrix_1_t>::value
			   && is_dense_matrix <Matrix_2_t>::value>* = nullptr >
Matrix_3_t operator*(const Matrix_1_t& A, const Matrix_2_t& B);

template <class Matrix_1_t, class Matrix_2_t, class Matrix_3_t,
	  std::enable_if_t<   is_dense_matrix <Matrix_1_t>::value
			               && is_dense_matrix <Matrix_2_t>::value
			               && is_dense_matrix <Matrix_3_t>::value>* = nullptr >
void   mult(const Matrix_1_t& A, const Matrix_2_t& B, Matrix_3_t& C) {
  for (size_t i = 0; i < C.num_rows(); ++i) {
    for (size_t j = 0; j < C.num_cols(); ++j) {
      for (size_t k = 0; k < A.num_cols(); ++k) {
        C(i, j) += A(i, k) * B(k, j);
      }
    }
  }
}

template <class Matrix_1_t, class Matrix_2_t,
	  std::enable_if_t<   is_dense_matrix <Matrix_1_t>::value
			               && is_dense_matrix <Matrix_2_t>::value>* = nullptr >
void copy(const Matrix_1_t& A, Matrix_2_t& B) {
  assert(B.num_rows() == A.num_rows());
  assert(B.num_cols() == A.num_cols());
  for (size_t i = 0; i < B.num_rows(); ++i) {
    for (size_t j = 0; j < B.num_cols(); ++j) {
      B(i, j) = A(i, j);
    }
  }
}

template <class SparseMatrix_t, class Matrix_t,
	  std::enable_if_t<   is_sparse_matrix<SparseMatrix_t>::value
			   && is_dense_matrix <Matrix_t>      ::value>* = nullptr >
Matrix_t mult(const SparseMatrix_t& A, const Matrix_t& B) {
  Matrix_t C(A.num_rows(), B.num_cols());
  A.matmat(B, C);
  return C;
}

template <class SparseMatrix_t, class Matrix_1_t, class Matrix_2_t,
	  std::enable_if_t<   is_sparse_matrix<SparseMatrix_t>::value
			   && is_dense_matrix <Matrix_1_t>    ::value
			   && is_dense_matrix <Matrix_2_t>    ::value>* = nullptr >
void mult(const SparseMatrix_t& A, const Matrix_1_t& B, Matrix_2_t& C) { 
  A.matmat(B, C); 
}

#endif // AMATH583_AMATH583_HPP
