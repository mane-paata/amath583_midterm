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
        if (i > num_rows_ || i < 0){
            std::cout << "Error: Row number:"<< i << " not with in range (0 - "<< num_rows_ << ")" << std::endl;
            throw; 
        }
        if(j > num_cols_ || j < 0){
            std::cout << "Error: Col number:"<< j << " not with in range (0 - "<< num_cols_ << ")" << std::endl;
            throw; 
        }

        for (size_t k=0; k< storage_.size(); ++k){
            if (storage_[k].row == i && storage_[k].col == j){
                std::cout << "Error: Attempt to push back duplicate element (" <<i<<","<< j<< ")."<<std::endl;
                throw;
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

    size_t num_rows()     const { return num_rows_; }
    size_t num_cols()     const { return num_cols_; }

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
            throw;
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
            throw;
        }

        if (num_rows < 0) {
            std::cout << "Error: matrix file contains invalid num rows";
            throw;
        }

        if (num_cols < 0) {
            std::cout << "Error: matrix file contains invalid num columns";
            throw;
        }

        getline(inputStream, string_input);
        size = stol(string_input);
        if(size < 0){
            std::cout << "Error: matrix file contains invalid num non zero (size)";
            throw;
        }

        num_rows_ = num_rows; num_cols_  = num_cols;
        long                     row_index;
        long                     col_index;
        double                   value;

        while (getline(inputStream, string_input) && string_input.compare("THIS IS THE END") != 0) {
            line_data = split(string_input, ' ');
            if (line_data.size() == 3) {
                row_index = stol(line_data[0]);
                col_index = stol(line_data[1]);
                value     = stod(line_data[2]);
                push_back(row_index, col_index, value);
            } 
            else {
                std::cout << "Error: COO Matrix file contains invalid row";
                throw;
            }
        }

        if (string_input.compare("THIS IS THE END") != 0){
            std::cout << "Error: Matrix file does not contain proper footer.";
            throw;
        }
    }

    void streamMatrix(std::ostream& outputFile) const {

        outputFile << "AMATH 583 COOMATRIX" << std::endl;
        outputFile << num_rows_ << " " << num_cols_ << std::endl;
        outputFile << storage_.size() << std::endl;

        // Write data
        for (size_t  i = 0; i < storage_.size(); ++i) {
        outputFile << storage_[i].row << " ";
        outputFile << storage_[i].col << " ";
        outputFile << std::setprecision(15) << std::scientific << storage_[i].val << " ";
        outputFile << std::endl;
        }
    
        // Write tailer
        outputFile << "THIS IS THE END" << std::endl;
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
