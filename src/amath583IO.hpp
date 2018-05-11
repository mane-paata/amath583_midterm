//
// This file is part of the course materials for AMATH483/583 at the University of Washington,
// Spring 2018
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Tommaso Buvoli,  Andrew Lumsdaine
//
#ifndef __AMATH583IO_HPP
#define __AMATH583IO_HPP

#include <complex>
#include <iomanip>
#include <string>

#include "AOSMatrix.hpp"
#include "COOMatrix.hpp"
#include "CSCMatrix.hpp"
#include "CSRMatrix.hpp"
#include "Matrix.hpp"
#include "Vector.hpp"

// == Vector IO Functions  ===========================================================================
Vector readVector();
Vector readVector(std::string path);
Vector readVector(std::istream&);

void streamVector(const Vector&);
void streamVector(const Vector&, std::ostream&);
void writeVector(const Vector&, std::string);

// == Matrix IO Functions  ===========================================================================
Matrix readMatrix();
Matrix readMatrix(std::string path);
Matrix readMatrix(std::istream&);

void streamMatrix(const Matrix&);
void streamMatrix(const Matrix&, std::ostream&);
void writeMatrix(const Matrix&, std::string);

//// == Sparse Matrix IO Functions  ==================================================================
COOMatrix readCOOMatrix();
COOMatrix readCOOMatrix(std::string path);
COOMatrix readCOOMatrix(std::istream&);

void streamCOOMatrix(const COOMatrix&);
void streamCOOMatrix(const COOMatrix&, std::ostream&);
void writeCOOMatrix(const COOMatrix&, std::string);

std::vector<std::string> split(const std::string&,
                               char);    // TAKEN FROM: https://www.fluentcpp.com/2017/04/21/how-to-split-a-string-in-c/

// == Number IO Functions  ===========================================================================
double readDouble();
double readDouble(std::istream&);
double readDouble(std::string);

std::complex<double> readComplexDouble(std::ifstream& file);
std::complex<double> readComplexDouble(std::string path);

void streamComplexDouble(const std::complex<double>);
void streamComplexDouble(const std::complex<double>, std::ostream&);
void writeComplexDouble(const std::complex<double>, std::string);

template<class NUMT>
void streamNumber(NUMT value) {
  streamNumber(value, std::cout);
}

template<class NUMT>
void streamNumber(NUMT value, std::ostream& out_file) {
  out_file << std::setprecision(15) << std::scientific << value;
}

template<class NUMT>
void writeNumber(NUMT value, std::string file_path) {
  std::ofstream out_file(file_path);
  streamNumber(value, out_file);
}


void writeMatrix(const COOMatrix& A, const std::string& filename);
void streamMatrix(const COOMatrix& A);
void streamMatrix(const COOMatrix& A, std::ostream& outputFile);

void writeMatrix(const CSRMatrix& A, const std::string& filename);
void streamMatrix(const CSRMatrix& A);
void streamMatrix(const CSRMatrix& A, std::ostream& outputFile);

#endif
