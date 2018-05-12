#include <iostream>

#include "AOSMatrix.hpp"
#include "amath583IO.hpp"


int main(int argc, char* argv[]){
	
	if(argc != 4){
		std::cout << "Usage: " << argv[0] << "[COO matrix file] [Vector file] [Destination file] " << std::endl;
		return -1;
	}

	//std::filebuf fb;
  //fb.open (argv[2], std::ios::out);
  //std::ostream os(&fb);
	
	AOSMatrix A;
	A.readMatrix(argv[1]);
	//A.streamMatrix(os);

	COOMatrix B = readCOOMatrix(argv[1]);

	Vector x = readVector(argv[2]);
	Vector b(x.num_rows());
	Vector c(x.num_rows());

	A.matvec(x,b);
	writeVector(b,"mat_vec_aos.txt");

	B.matvec(x,c);
	writeVector(c, "mat_vec_coo.txt");
}

