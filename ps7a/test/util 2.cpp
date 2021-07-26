

#include <iostream>

#include "util.hpp"

#include "COOMatrix.hpp"
#include "CSRMatrix.hpp"
#include "CSCMatrix.hpp"
#include "Matrix.hpp"
#include "Vector.hpp"


template <class SparseMatrix_t, class Vector_1_t, class Vector_2_t, 
	  std::enable_if_t<   is_sparse_matrix<SparseMatrix_t>::value
			   && is_dense_vector <Vector_1_t>    ::value
			   && is_dense_vector <Vector_2_t>    ::value>* = nullptr >
void mult(const SparseMatrix_t& A, const Vector_1_t& x, Vector_2_t& y) { 
  std::cout << "v.1 sparse dense matvec" << std::endl;
  A.matvec(x, y); 
}

template <class SparseMatrix_t, class Matrix_1_t, class Matrix_2_t, 
	  std::enable_if_t<   is_sparse_matrix<SparseMatrix_t>::value
			   && is_dense_matrix <Matrix_1_t>    ::value
			   && is_dense_matrix <Matrix_2_t>    ::value>* = nullptr >
void mult(const SparseMatrix_t& A, const Matrix_1_t& B, Matrix_2_t& C) { 
  std::cout << "v.2 sparse dense matmat" << std::endl;
  A.matmat(B, C); 
}

template <class SparseMatrix_t>
void mult(const SparseMatrix_t& A, const Matrix& B, Matrix& C) { 
  std::cout << "v.3 partially specialized" << std::endl;
  A.matmat(B, C); 
}

void mult(const CSRMatrix& A, const Matrix& B, Matrix& C) { 
  std::cout << "v.4 fully specialized" << std::endl;
  A.matmat(B, C);
}


int main() {

  
  std::cout << "COO is " << is_sparse_matrix<COOMatrix>::value << std::endl;
  std::cout << "Vector is " << is_sparse_matrix<Vector>::value << std::endl;
  std::cout << "Matrix is " << is_sparse_matrix<Matrix>::value << std::endl;

  std::cout << "COO is " << is_dense_matrix<COOMatrix>::value << std::endl;
  std::cout << "Vector is " << is_dense_matrix<Vector>::value << std::endl;
  std::cout << "Matrix is " << is_dense_matrix<Matrix>::value << std::endl;

  std::cout << "COO is " << is_dense_vector<COOMatrix>::value << std::endl;
  std::cout << "Vector is " << is_dense_vector<Vector>::value << std::endl;
  std::cout << "Matrix is " << is_dense_vector<Matrix>::value << std::endl;


  COOMatrix A(1,1);
  Matrix B(1,1), C(1,1);
  mult(A, B, C);

  Vector x(1), y(1);
  mult(A, x, y);

  CSRMatrix D(1,1);
  mult(D, B, C);

  CSCMatrix E(1,1);
  mult(E, B, C);

  Matrix F(1,1);
  mult(F, B, C);


  return 0;
}

