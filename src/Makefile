#
# This file is part of the course materials for AMATH483/583 at the University of Washington,
# Spring 2018
#
# Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
# https://creativecommons.org/licenses/by-nc-sa/4.0/
#
# Author: Andrew Lumsdaine, Tommaso Buvoli
#

CXX             = c++

OPTS            = -O3 -DNDEBUG # Also try -Ofast -march=native
LANG            = -std=c++11
PICKY           = -Wall 

CXXFLAGS        = $(LANG) $(OPTS) $(PICKY) 


.PHONY: clean all

#all: aosmatvec.exe cscmatvec.exe

all: aosmatvec.exe

# Rules for executables
aosmatvec.exe: aosmatvec.o AOSMatrix.o Vector.o matvec583.o amath583IO.o
	$(CXX) $(CXXFLAGS) $^ -o $@

cscmatvec.exe: cscmatvec.o CSCMatrix.o Vector.o matvec583.o amath583IO.o
	$(CXX) $(CXXFLAGS) $^ -o $@

# Generic rule for making object file from .cpp file
%.o          : %.cpp
	$(CXX) $(CXXFLAGS) -c $<

# Object file (.o) dependencies -- consequent is handled by generic rule
Vector.o     : Vector.cpp Vector.hpp
Matrix.o     : Matrix.cpp Matrix.hpp
COOMatrix.o  : COOMatrix.cpp COOMatrix.hpp
CSRMatrix.o  : CSRMatrix.cpp CSRMatrix.hpp
CSCMatrix.o  : CSCMatrix.cpp CSCMatrix.hpp

matvect583.o : matvec583.cpp matvec583.hpp Matrix.hpp Vector.hpp COOMatrix.hpp CSRMatrix.hpp CSCMatrix.hpp 
amath583IO.o : amath583IO.cpp amath583IO.hpp Matrix.hpp Vector.hpp COOMatrix.hpp CSRMatrix.hpp CSCMatrix.hpp 
aosmatvec.o  : aosmatvec.cpp amath583IO.hpp matvec583.hpp Matrix.hpp Vector.hpp COOMatrix.hpp CSRMatrix.hpp CSCMatrix.hpp 
cscmatvec.o  : cscmatvec.cpp amath583IO.hpp matvec583.hpp Matrix.hpp Vector.hpp COOMatrix.hpp CSRMatrix.hpp CSCMatrix.hpp 

clean:
	/bin/rm -f *.o *.exe *.gch *~ 
