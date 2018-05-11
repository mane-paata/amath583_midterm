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

    void readMatrix(std::string file) { // read from file
        std::string string_input;
        std::ifstream inputStream(file);

        getline(inputStream, string_input);
        if (string_input.compare("AMATH 583 COOMATRIX") != 0) {
            std::cout << "Error: Matrix file does not contain a header.";
            throw;
        }

        getline(inputStream, string_input);
        if (string_input.compare("THIS IS THE END") == 0) {
            clear();
            return;
        }
        
        std::istringstream line(string_input);
        long num_rows;
        line >> num_rows;
        if (num_rows < 0) {
            std::cout << "Error: Matrix file contains invalid num rows";
            throw;
        }

        long num_cols;
        line >> num_cols;
        if (num_cols < 0) {
            std::cout << "Error: matrix file contains invalid num columns";
            throw;
        }

        getline(inputStream, string_input);
        long size = stol(string_input);
        if (size < 0) {
            std::cout << "Error: matrix file contains invalid num elements";
            throw;
        }

        num_rows_ = num_rows;
        num_cols_ = num_cols;

        size_t row, col;
        double val;
        for (size_t i = 0; i < size; i++) {
            getline(inputStream, string_input);
            std::istringstream line(string_input);
            std::string str;
            bool invalidline = false;

            // row
            if(getline(line, str, ' ')) row = stol(str);
            else                        invalidline = true;
            
            // col
            if(getline(line, str, ' ')) col = stol(str);
            else                        invalidline = true;
            
            // value
            if(getline(line, str, ' ')) val = stod(str);
            else                        invalidline = true;
               
            if (invalidline || getline(line, str, ' ')){
                std::cout << "Error: Invalid entry in input file. Expected: row, col, val. Actual: "<< string_input << std::endl;
                throw;
            }
            
            push_back(row, col, val);
        }

        getline(inputStream, string_input);
        if (string_input.compare("THIS IS THE END") != 0) {
            std::cout << "Error: vector file does not contain proper footer.";
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
            y(storage_[k].row) = storage_[k].val* x(storage_[k].col);
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
