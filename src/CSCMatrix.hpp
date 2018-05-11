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
  
  CSCMatrix(size_t M, size_t N) : is_open(false), num_rows_(M), num_cols_(N), col_indices_(num_cols_ + 1, 0) {}

  void openForPushBack() { is_open = true; }
  
  void closeForPushBack() {
    is_open = false;
    for (size_t i = 0; i < num_cols_; ++i) {
      col_indices_[i + 1] += col_indices_[i];
    }
    for (size_t i = num_cols_; i > 0; --i) {
      col_indices_[i] = col_indices_[i - 1];
    }
    col_indices_[0] = 0;
  }

  void push_back(size_t i, size_t j, double value) {
    assert(is_open);
    assert(i < num_rows_ && i >= 0);
    assert(j < num_cols_ && j >= 0);

    ++col_indices_[j];
    row_indices_.push_back(i);
    storage_.push_back(value);
  }
  
  void clear() {
    row_indices_.clear();
    storage_.clear();
    std::fill(col_indices_.begin(), col_indices_.end(), 0);
  }

  void reserve(size_t n) { 
    storage_.reserve(n);
    row_indices_.reserve(n);
    col_indices_.reserve(n);
  }

  size_t num_rows() const { return num_rows_; }
  size_t num_cols() const { return num_cols_; }
  size_t num_nonzeros() const { return storage_.size(); }

  void matvec(const Vector& x, Vector& y) const {
    /* Review: mostly needs fixing */
    for (size_t i = 0; i < num_cols_; ++i) {
      for (size_t j = col_indices_[i]; j < col_indices_[i + 1]; ++j) {
        y(i) += storage_[j] * x(row_indices_[j]);
      }
    }
  }

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
