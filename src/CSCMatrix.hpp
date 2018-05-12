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

std::vector<std::string> split(const std::string&, char); // implemented in amath585IO.cpp

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
    col_indices_.reserve(n+1);
  }

  size_t num_rows() const { return num_rows_; }
  size_t num_cols() const { return num_cols_; }
  size_t num_nonzeros() const { return storage_.size(); }

  void matvec(const Vector& x, Vector& y) const {
     for (size_t i = 0; i < num_cols_; ++i) {
      for (size_t j = col_indices_[i]; j < col_indices_[i + 1]; ++j) {
        y(i) += storage_[j] * x(row_indices_[j]);
      }
    }
  }

  void readMatrix(std::string filename) {
    std::ifstream inputFile(filename);
    return readMatrix(inputFile);
  }

  void readMatrix(std::istream& inputStream) {
    std::string string_input;

    getline(inputStream, string_input);
    if (string_input.compare("AMATH 583 COOMATRIX") != 0) {
      std::cout << "Error: matrix file does not contain a header.";
      exit(-1);
    }

    getline(inputStream, string_input);
    if (string_input.compare("THIS IS THE END") == 0) {
      clear();
      return;
    }

    std::vector<std::string> line_data;
    long num_rows, num_cols, size;
    
    line_data = split(string_input, ' ');
    if (line_data.size() == 2){
      num_rows = stol(line_data[0]);
      num_cols = stol(line_data[1]);
    }else {
      std::cout << "Error: Invalid data found. Expected num_rows, num_cols. Found: "<< string_input<< std::endl;
      exit(-1);
    }

    if (num_rows < 0) {
      std::cout << "Error: matrix file contains invalid num rows";
      exit(-1);
    }

    if (num_cols < 0) {
      std::cout << "Error: matrix file contains invalid num columns";
      exit(-1);
    }

    getline(inputStream, string_input);
    size = stol(string_input);
    if(size < 0){
      std::cout << "Error: matrix file contains invalid num non zero (size)";
      exit(-1);
    }

    num_rows_ = num_rows; num_cols_  = num_cols;
    reserve(size);

    long  row_index;
    long  col_index;
    double value;

    openForPushBack();
    while (getline(inputStream, string_input) && string_input.compare("THIS IS THE END") != 0) {
      line_data = split(string_input, ' ');
      if (line_data.size() == 3) {
        row_index = stol(line_data[0]);
        col_index = stol(line_data[1]);
        value   = stod(line_data[2]);
        push_back(row_index, col_index, value);
      } 
      else {
        std::cout << "Error: COO Matrix file contains invalid row";
        exit(-1);
      }
    }
    closeForPushBack();

    if (string_input.compare("THIS IS THE END") != 0){
      std::cout << "Error: COO Matrix file does not contain proper footer.";
      exit(-1);
    }
  }

private:
  bool        is_open;
  size_t        num_rows_, num_cols_;
  std::vector<double> storage_;
  std::vector<int>  row_indices_, col_indices_;
};

#endif  // __CSCMATRIX_HPP
