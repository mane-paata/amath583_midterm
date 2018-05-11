#include <iostream>

#include "AOSMatrix.hpp"


int main(int argc, char* argv[]){
	
	if(argc != 3){
		std::cout << "Usage: " << argv[0] << "[COO matrix file] [Vector file] [Destination file] " << std::endl;
		return -1;
	}

	std::filebuf fb;
  fb.open (argv[2], std::ios::out);
  std::ostream os(&fb);
	
	AOSMatrix A;
	A.readMatrix(argv[1]);
	A.streamMatrix(os);
}

