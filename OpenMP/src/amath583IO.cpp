//
// This file is part of the course materials for AMATH483/583 at the University of Washington,
// Spring 2020
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Andrew Lumsdaine
//

#include "amath583IO.hpp"
#include "COOMatrix.hpp"
#include "CSRMatrix.hpp"
#include "Matrix.hpp"
#include "Vector.hpp"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "AOSMatrix.hpp"
#include "CSCMatrix.hpp"

// ----------------------------------------------------------------
//
// Vector I/O
//
// ----------------------------------------------------------------
Vector read_vector(std::istream& input_stream) {
  std::string string_input;

  getline(input_stream, string_input);
  if (string_input.compare("AMATH 583 VECTOR") != 0) {
    std::cout << "Bad header " << string_input << std::endl;
    throw;
  }

  getline(input_stream, string_input);
  if (string_input.compare("THIS IS THE END") == 0) {
    return Vector(0);
  }

  if (stol(string_input) < 0) {
    std::cout << "Error: vector file contains invalid vector length.";
    throw;
  }

  size_t N = stol(string_input);
  Vector v(N);

  for (size_t i = 0; i < N; ++i) {
    getline(input_stream, string_input);
    v(i) = stod(string_input);
  }
  getline(input_stream, string_input);
  if (string_input.compare("THIS IS THE END") != 0) {
    std::cout << "Bad tailer " << string_input << std::endl;
    throw;
  }

  return v;
}

Vector read_vector(const std::string& filename) {
  std::ifstream input_file(filename);
  return read_vector(input_file);
}

void stream_vector(const Vector& x, std::ostream& outputFile) {
  outputFile << "AMATH 583 VECTOR" << std::endl;
  outputFile << x.num_rows() << std::endl;

  for (size_t i = 0; i < x.num_rows(); ++i) {    // Write data
    outputFile << std::setprecision(15) << std::scientific << x(i) << std::endl;
  }

  outputFile << "THIS IS THE END" << std::endl;    // Write tailer
}

void write_vector(const Vector& x, const std::string& filename) {
  if (filename == "") {
    stream_vector(x, std::cout);
  } else {
    std::ofstream output_file(filename);
    stream_vector(x, output_file);
  }
}

// ----------------------------------------------------------------
//
// Matrix I/O
//
// ----------------------------------------------------------------
Matrix read_matrix(std::istream& input_stream) {
  std::string string_input;

  getline(input_stream, string_input);
  if (string_input.compare("AMATH 583 MATRIX") != 0) {
    std::cout << "Error: matrix file does not contain a header.";
    throw;
  }

  getline(input_stream, string_input);
  if (string_input.compare("THIS IS THE END") == 0) return Matrix(0, 0);

  size_t num_rows = stol(string_input);
  getline(input_stream, string_input);
  size_t num_cols = stol(string_input);

  Matrix A(num_rows, num_cols);

  for (size_t i = 0; i < num_rows; i++) {
    for (size_t j = 0; j < num_cols; j++) {
      getline(input_stream, string_input);
      A(i, j) = stod(string_input);
    }
  }
  getline(input_stream, string_input);
  if (string_input.compare("THIS IS THE END") != 0) {
    std::cout << "Error: vector file does not contain proper footer.";
    throw;
  }
  return A;
}

Matrix read_matrix(const std::string& filename) {
  std::ifstream input_file(filename);
  return read_matrix(input_file);
}

void stream_matrix(const Matrix& A, std::ostream& outputFile) {
  outputFile << "AMATH 583 MATRIX" << std::endl;    // Write header
  outputFile << A.num_rows() << std::endl;
  outputFile << A.num_cols() << std::endl;

  for (size_t i = 0; i < A.num_rows(); i++) {
    for (size_t j = 0; j < A.num_cols(); j++) {
      outputFile << std::setprecision(15) << std::scientific << A(i, j) << std::endl;
    }
  }

  outputFile << "THIS IS THE END" << std::endl;    // Write tailer
}

void write_matrix(const Matrix& A, const std::string& filename) {
  if (filename == "") {
    stream_matrix(A, std::cout);
  } else {
    std::ofstream outputFile(filename);
    stream_matrix(A, outputFile);
  }
}

// ----------------------------------------------------------------
//
// Sparse I/O
//
// ----------------------------------------------------------------
std::tuple<size_t, size_t, std::vector<std::tuple<size_t, size_t, double>>> read_mm(std::istream& input_stream) {
  std::string              string_input;
  bool                     file_symmetry = false;
  bool                     pattern       = false;
  bool                     binary64      = false;
  std::vector<std::string> header(6);

  // %%MatrixMarket matrix coordinate integer symmetric
  // %%MatrixMarket matrix coordinate real general
  // %%MatrixMarket matrix coordinate pattern symmetric

  std::getline(input_stream, string_input);
  std::stringstream h(string_input);
  for (auto& s : header)
    h >> s;

  if (header[0] != "%%MatrixMarket") {
    std::cerr << "Unsupported format" << std::endl;
    throw;
  }
  if (header[4] == "symmetric") {
    file_symmetry = true;
  } else if (header[4] == "unsymmetric" || header[4] == "general") {
    file_symmetry = false;
  } else {
    std::cerr << "Bad mmio format (symmetry): " << header[4] << std::endl;
    throw;
  }

  if (header[3] == "pattern") {
    pattern = true;
  } else if (header[3] == "real" || header[3] == "integer") {
    pattern = false;
  } else {
    std::cerr << "Bad mmio format (value type): " << header[3] << std::endl;
    throw;
  }

  if (header[5] != "") {
    if (header[5] == "binary64") {
      binary64 = true;
    } else {
      throw;
    }
  }

  while (std::getline(input_stream, string_input)) {
    if (string_input[0] != '%') break;
  }
  size_t n0, n1, nnz;
  std::stringstream(string_input) >> n0 >> n1 >> nnz;

  std::vector<std::tuple<size_t, size_t, double>> aos;
  if (file_symmetry) {
    aos.reserve(2 * nnz);
  } else {
    aos.reserve(nnz);
  }

  if (binary64) {
    std::vector<std::tuple<size_t, size_t>> bos(nnz);
    input_stream.read((char*)bos.data(), bos.size() * sizeof(std::tuple<size_t, size_t>));
    for (auto& j : bos) {
      aos.push_back({std::get<0>(j), std::get<1>(j), 1.0});
    }
  } else {

    for (size_t i = 0; i < nnz; ++i) {
      std::string buffer;
      size_t      d0, d1;
      double      v;

      std::getline(input_stream, buffer);

      if (true == pattern) {
        std::stringstream(buffer) >> d0 >> d1;
        aos.push_back({d0 - 1, d1 - 1, 1.0});
        if (file_symmetry) {
          aos.push_back({d1 - 1, d0 - 1, 1.0});
        }
      } else {
        std::stringstream(buffer) >> d0 >> d1 >> v;
        aos.push_back({d0 - 1, d1 - 1, v});
        if (file_symmetry) {
          aos.push_back({d1 - 1, d0 - 1, v});
        }
      }
    }
  }

  return std::make_tuple(n0, n1, aos);
}

std::tuple<size_t, size_t, std::vector<std::tuple<size_t, size_t, double>>> read_mm(std::string filename) {
  std::ifstream input_file(filename);
  return read_mm(input_file);
}

COOMatrix read_coomatrix(const std::string& filename) {
  std::tuple<size_t, size_t, std::vector<std::tuple<size_t, size_t, double>>> pack = read_mm(filename);

  size_t                                          M   = std::get<0>(pack);
  size_t                                          N   = std::get<1>(pack);
  std::vector<std::tuple<size_t, size_t, double>> aos = std::get<2>(pack);

  COOMatrix A(M, N);
  A.reserve(aos.size());

  for (size_t k = 0; k < aos.size(); ++k) {
    size_t i = std::get<0>(aos[k]);
    size_t j = std::get<1>(aos[k]);
    double v = std::get<2>(aos[k]);
    A.push_back(i, j, v);
  }

  return A;
}

void write_coomatrix(const COOMatrix& A, const std::string& filename) {
  std::ofstream output_file(filename);
  std::cout << "%%MatrixMarket matrix coordinate real general" << std::endl;
  std::cout << A.num_rows() << " " << A.num_cols() << " " << A.num_nonzeros() << std::endl;
  A.stream_coordinates(output_file);
}

CSRMatrix read_csrmatrix(const std::string& filename) {
  using element                                         = std::tuple<size_t, size_t, double>;
  std::tuple<size_t, size_t, std::vector<element>> pack = read_mm(filename);

  size_t                                          M   = std::get<0>(pack);
  size_t                                          N   = std::get<1>(pack);
  std::vector<std::tuple<size_t, size_t, double>> aos = std::get<2>(pack);

  // sort by row
  std::sort(aos.begin(), aos.end(), [](element& a, element& b) -> bool { return (std::get<0>(a) < std::get<0>(b)); });

  CSRMatrix A(M, N);
  A.open_for_push_back();

  for (size_t k = 0; k < aos.size(); ++k) {
    size_t i = std::get<0>(aos[k]);
    size_t j = std::get<1>(aos[k]);
    double v = std::get<2>(aos[k]);
    A.push_back(i, j, v);
  }
  A.close_for_push_back();

  return A;
}

void write_csrmatrix(const CSRMatrix& A, std::string filename) {
  std::ofstream output_file(filename);
  std::cout << "%%MatrixMarket matrix coordinate real general" << std::endl;
  std::cout << A.num_rows() << " " << A.num_cols() << " " << A.num_nonzeros() << std::endl;
  A.stream_coordinates(output_file);
}

CSCMatrix read_cscmatrix(const std::string& filename) {
  using element                                         = std::tuple<size_t, size_t, double>;
  std::tuple<size_t, size_t, std::vector<element>> pack = read_mm(filename);

  size_t                                          M   = std::get<0>(pack);
  size_t                                          N   = std::get<1>(pack);
  std::vector<std::tuple<size_t, size_t, double>> aos = std::get<2>(pack);

  // sort by column
  std::sort(aos.begin(), aos.end(), [](element& a, element& b) -> bool { return (std::get<1>(a) < std::get<1>(b)); });

  CSCMatrix A(M, N);
  A.open_for_push_back();

  for (size_t k = 0; k < aos.size(); ++k) {
    size_t i = std::get<0>(aos[k]);
    size_t j = std::get<1>(aos[k]);
    double v = std::get<2>(aos[k]);
    A.push_back(i, j, v);
  }
  A.close_for_push_back();

  return A;
}

void write_cscmatrix(const CSCMatrix& A, std::string filename) {
  std::ofstream output_file(filename);
  std::cout << "%%MatrixMarket matrix coordinate real general" << std::endl;
  std::cout << A.num_rows() << " " << A.num_cols() << " " << A.num_nonzeros() << std::endl;
  A.stream_coordinates(output_file);
}

AOSMatrix read_aosmatrix(const std::string& filename) {
  std::tuple<size_t, size_t, std::vector<std::tuple<size_t, size_t, double>>> pack = read_mm(filename);

  size_t                                          M   = std::get<0>(pack);
  size_t                                          N   = std::get<1>(pack);
  std::vector<std::tuple<size_t, size_t, double>> aos = std::get<2>(pack);

  AOSMatrix A(M, N);
  A.reserve(aos.size());

  for (size_t k = 0; k < aos.size(); ++k) {
    size_t i = std::get<0>(aos[k]);
    size_t j = std::get<1>(aos[k]);
    double v = std::get<2>(aos[k]);
    A.push_back(i, j, v);
  }

  return A;
}

void write_aosmatrix(const AOSMatrix& A, std::string filename) {
  std::ofstream output_file(filename);
  std::cout << "%%MatrixMarket matrix coordinate real general" << std::endl;
  std::cout << A.num_rows() << " " << A.num_cols() << " " << A.num_nonzeros() << std::endl;
  A.stream_coordinates(output_file);
}
