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
#include <vector>
#include <iostream>
#include <fstream>

#include "Vector.hpp"

class AOSMatrix {
public:
    AOSMatrix() {} // default constructor
    AOSMatrix(size_t M, size_t N) {
        num_rows_ = M;      // new lines written
        num_cols_ = N;
    }
    void push_back(size_t i, size_t j, double val) {
        assert(i < num_rows_ && i >= 0);        //new fixed
        assert(j < num_cols_ && j >= 0);

        storage_.row.push_back(i);
        storage_.col.push_back(j);
        storage_.val.push_back(val);
    }

    void clear() {
        storage_.clear();                // new line
    }

    void reserve(size_t n) {
        assert(n >= 0);                   //new lines written

        storage_.reserve(n);

    }

    size_t num_rows()     const { return num_rows_; } // fixed 
    size_t num_cols()     const { return num_cols_; } // fixed 

    size_t num_nonzeros() const { return storage_.size(); } //fixed 

    void readMatrix(std::string file) { // read from file
        std::string input_line;
        std::ifstream infile(file);
        
        getline(infile, input_line);
        if (input_line.compare("AMATH 583 COOMATRIX") != 0) {
            std::cout << "Error: matrix file does not contain a header." << std::endl;
            exit(-1);
        } 
        
        getline(infile, input_line);
        if (string_input.compare("THIS IS THE END") == 0)
            clear();

        

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
