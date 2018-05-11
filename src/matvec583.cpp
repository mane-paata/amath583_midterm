//
// This file is part of the course materials for AMATH483/583 at the University of Washington,
// Spring 2018
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Andrew Lumsdaine
//

#include "matvec583.hpp"
#include "AOSMatrix.hpp"
#include "COOMatrix.hpp"
#include "CSCMatrix.hpp"
#include "CSRMatrix.hpp"
#include "Matrix.hpp"
#include "Vector.hpp"

Vector operator*(const Matrix& A, const Vector& x) {
  Vector y(x.num_rows());
  matvec(A, x, y);
  return y;
}

void matvec(const Matrix& A, const Vector& x, Vector& y) {
  for (size_t i = 0; i < A.num_rows(); ++i) {
    for (size_t j = 0; j < A.num_cols(); ++j) {
      y(i) += A(i, j) * x(j);
    }
  }
}

void matvec(const COOMatrix& A, const Vector& x, Vector& y) { A.matvec(x, y); }
void matvec(const AOSMatrix& A, const Vector& x, Vector& y) { A.matvec(x, y); }
void matvec(const CSRMatrix& A, const Vector& x, Vector& y) { A.matvec(x, y); }
void matvec(const CSCMatrix& A, const Vector& x, Vector& y) { A.matvec(x, y); }

