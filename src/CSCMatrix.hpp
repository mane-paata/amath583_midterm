//
// This file is part of the course materials for AMATH483/583 at the University of Washington,
// Spring 2018
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Andrew Lumsdaine
//
#ifndef __CSCMATRIX_HPP
#define __CSCMATRIX_HPP

#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <numeric>
#include <vector>

#include "Vector.hpp"

// note: Matrix elemetns are 0-indexed
class CSCMatrix {

public:
  CSCMatrix() {}   // empty constructor
  
  CSCMatrix(size_t M, size_t N) { /* write me */ }

  void push_back(size_t i, size_t j, double val) { /* write me */ }

  void closeForPushBack() { /* write me */ }

  void openForPushBack() { is_open = true; }

  void clear() { /* write me */ }

  void reserve(size_t n) { /* write me */ }

  size_t num_rows() const { return 0; } /* fix me */
  size_t num_cols() const { return 0; } /* fix me */

  size_t numNonzeros() const { return 0; } /* fix me */

  void matvec(const Vector& x, Vector& y) const { /* write me */ }

  void readMatrix(std::string file) {    // read from file
                                         // write me 
  }

private:
  size_t                 num_rows_, num_cols_;
  std::vector<double> storage_;
  bool                is_open;
  std::vector<int>    row_indices_, col_indices_;
};

#endif    // __CSCMATRIX_HPP
