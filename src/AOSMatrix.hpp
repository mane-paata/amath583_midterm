//
// This file is part of the course materials for AMATH483/583 at the University of Washington,
// Spring 2018
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Andrew Lumsdaine
//

#ifndef __AOSMATRIX_HPP
#define __AOSMATRIX_HPP

#include <cassert>
#include <cstddef>
#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>

#include "Vector.hpp"

std::vector<std::string> split(const std::string&, char); // implemented in amath585IO.cpp

class AOSMatrix {
public:
  AOSMatrix() {} // default constructor
  AOSMatrix(size_t M, size_t N) {
    num_rows_ = M;
    num_cols_ = N;
  }
  
  void push_back(size_t i, size_t j, double val) {
    assert(i < num_rows_ && i >= 0);
    assert(j < num_cols_ && j >= 0);

    for (size_t k=0; k< storage_.size(); ++k){
      if (storage_[k].row == i && storage_[k].col == j){
        std::cout << "Error: Attempt to push back duplicate element (" <<i<<","<< j<< ")."<<std::endl;
        exit(-1);
      }
    }

    Element a;
    a.row = i;
    a.col = j;
    a.val = val;
    storage_.push_back(a);
  }

  void clear() {
    num_cols_ = 0;
    num_rows_ =0;
    storage_.clear();
  }

  void reserve(size_t n) {
    assert(n >= 0); 
    storage_.reserve(n);
  }

  size_t num_rows()   const { return num_rows_; }
  size_t num_cols()   const { return num_cols_; }

  size_t num_nonzeros() const { return storage_.size(); }

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
    long           row_index;
    long           col_index;
    double           value;

    while (getline(inputStream, string_input) && string_input.compare("THIS IS THE END") != 0) {
      line_data = split(string_input, ' ');
      if (line_data.size() == 3) {
        row_index = stol(line_data[0]);
        col_index = stol(line_data[1]);
        value     = stod(line_data[2]);

        if (row_index < 0 || row_index > num_rows ){
          std::cout << "Error: Row number:"<< row_index << " not with in range (0 - "<< num_rows_ << ")" << std::endl;
          exit(-1); 
        }
        
        if (col_index < 0 || col_index > num_cols ){
          std::cout << "Error: Col number:"<< col_index << " not with in range (0 - "<< num_cols_ << ")" << std::endl;
          exit(-1); 
        }

        push_back(row_index, col_index, value);
      } 
      else {
        std::cout << "Error: COO Matrix file contains invalid row";
        exit(-1);
      }
    }

    if (string_input.compare("THIS IS THE END") != 0){
      std::cout << "Error: Matrix file does not contain proper footer.";
      exit(-1);
    }
  }

  void streamMatrix(std::string filename) {
    std::ofstream outputFile(filename);
    return streamMatrix(outputFile);
  }

  void streamMatrix(std::ostream& outputStream) const {

    outputStream << "AMATH 583 COOMATRIX" << std::endl;
    outputStream << num_rows_ << " " << num_cols_ << std::endl;
    outputStream << storage_.size() << std::endl;

    // Write data
    for (size_t  i = 0; i < storage_.size(); ++i) {
    outputStream << storage_[i].row << " ";
    outputStream << storage_[i].col << " ";
    outputStream << std::setprecision(15) << std::scientific << storage_[i].val << " ";
    outputStream << std::endl;
    }
  
    // Write tailer
    outputStream << "THIS IS THE END" << std::endl;
  }

  void matvec(const Vector& x, Vector& y) const {
    for(size_t k = 0; k < storage_.size(); ++k){
      y(storage_[k].row) += storage_[k].val* x(storage_[k].col);
    }
  }

private:
  class Element {
  public:
    size_t row, col;
    double val;
  };
  size_t num_rows_, num_cols_;
  std::vector<Element> storage_;
};

#endif // __AOSMATRIX_HPP
