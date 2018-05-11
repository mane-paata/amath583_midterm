//
// This file is part of the course materials for AMATH483/583 at the University of Washington,
// Spring 2018
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Andrew Lumsdaine
//
#ifndef __CSRMATRIX_HPP
#define __CSRMATRIX_HPP

#include "Vector.hpp"
#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <vector>

class CSRMatrix {

public:
  CSRMatrix(size_t M, size_t N) : is_open(false), iRows(M), jCols(N), row_indices_(iRows + 1, 0) {}

  void openForPushBack() { is_open = true; }

  void closeForPushBack() {
    is_open = false;
    for (size_t i = 0; i < iRows; ++i) {
      row_indices_[i + 1] += row_indices_[i];
    }
    for (size_t i = iRows; i > 0; --i) {
      row_indices_[i] = row_indices_[i - 1];
    }
    row_indices_[0] = 0;
  }

  void push_back(size_t i, size_t j, double value) {
    assert(is_open);
    assert(i < iRows && i >= 0);
    assert(j < jCols && j >= 0);

    ++row_indices_[i];
    col_indices_.push_back(j);
    storage_.push_back(value);
  }

  void matvec(const Vector& x, Vector& y) const {
    for (size_t i = 0; i < iRows; ++i) {
      for (size_t j = row_indices_[i]; j < row_indices_[i + 1]; ++j) {
        y(i) += storage_[j] * x(col_indices_[j]);
      }
    }
  }

  void clear() {
    col_indices_.clear();
    storage_.clear();
    std::fill(row_indices_.begin(), row_indices_.end(), 0);
  }

  void streamMatrix(std::ostream& outputFile) const {

    outputFile << "AMATH 583 CSRMATRIX" << std::endl;
    outputFile << iRows << " " << jCols << std::endl;

    // Write data
    for (size_t i = 0; i < iRows; ++i) {
      for (size_t j = row_indices_[i]; j < row_indices_[i + 1]; ++j) {
        outputFile << storage_[j] << " ";
      }
      outputFile << std::endl;
    }

    // Write tailer
    outputFile << "THIS IS THE END" << std::endl;
  }

  size_t num_rows() const { return iRows; }
  size_t num_cols() const { return jCols; }
  size_t num_nonzeros() const { return storage_.size(); }

private:
  bool                is_open;
  size_t              iRows, jCols;
  std::vector<size_t> row_indices_, col_indices_;
  std::vector<double> storage_;
};

#endif    // __CSRMATRIX_HPP
