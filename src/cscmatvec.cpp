#include <iostream>

#include "CSCMatrix.hpp"
#include "amath583IO.hpp"
#include "amath583.hpp"

int main(int argc, char* argv[]){

	if(argc != 4){
		std::cout << "Usage: " << argv[0] << "[COO matrix file] [Vector file] [Destination file] " << std::endl;
		return -1;
	}

	CSCMatrix A;
	A.readMatrix(argv[1]);

	Vector x = readVector(argv[2]);

	if (A.num_cols() != x.num_rows()){
		std::cout << "Error: Matrix x Vector dimension mismatch" << std::endl ;
		exit(-1);
	}

	Vector y(A.num_cols());
	A.matvec(x,y);
	writeVector(y,argv[3]);

	return 0;
}