//
// This file is part of the course materials for AMATH483/583 at the University
// of Washington,
// Spring 2018
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0
// International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Andrew Lumsdaine
//
#ifndef __MATVEC583_HPP
#define __MATVEC583_HPP

#include "AOSMatrix.hpp"
#include "COOMatrix.hpp"
#include "CSCMatrix.hpp"
#include "CSRMatrix.hpp"
#include "Matrix.hpp"
#include "Vector.hpp"

void matvec(const Matrix& A, const Vector& x, Vector& y);
void matvec(const COOMatrix& A, const Vector& x, Vector& y);
void matvec(const AOSMatrix& A, const Vector& x, Vector& y);
void matvec(const CSRMatrix& A, const Vector& x, Vector& y);
void matvec(const CSCMatrix& A, const Vector& x, Vector& y);

#endif    // __MATVEC583_HPP
