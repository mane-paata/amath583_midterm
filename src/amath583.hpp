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

#include <fstream>
#include <iostream>
#include <string>

#include "AOSMatrix.hpp"
#include "COOMatrix.hpp"
#include "CSCMatrix.hpp"
#include "CSRMatrix.hpp"
#include "Matrix.hpp"
#include "Vector.hpp"

double readDouble(std::string);

Vector operator+(const Vector& x, const Vector& y);

Vector operator*(const Matrix& A, const Vector& x);
Vector operator*(const COOMatrix& A, const Vector& x);
Vector operator*(const AOSMatrix& A, const Vector& x);
Vector operator*(const CSRMatrix& A, const Vector& x);
Vector operator*(const CSCMatrix& A, const Vector& x);

void   streamVector(const Vector&);
void   streamVector(const Vector&, std::ostream&);
void   writeVector(const Vector&, std::string);
Vector readVector(std::string);
Vector readVector(std::istream&);
Vector readVector();
void   zeroize(Matrix&);
void   zeroize(Vector&);
void   randomize(Vector&);
void   randomize(Matrix&);

template<class T>
void writeNumber(std::string file_path, T value) {
  std::ofstream out_file(file_path);
  if (out_file.is_open()) {
    out_file << value;
    out_file.close();
  } else {
    std::cout << "ERROR: Unable to write output file!";
    std::exit(-1);
  }
}

template<class T>
bool writeNumber(T value, std::string path) {
  std::ofstream out_file(path.c_str());
  return writeNumber(value, out_file);
}

void   piscetize(COOMatrix& A, size_t xpoints, size_t ypoints);


