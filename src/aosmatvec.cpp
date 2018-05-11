#include <iostream>

#include "AOSMatrix.hpp"


int main(int argc, char* argv[]){
	
	if(argc != 3){
		std::cout << "Usage: " << argv[0] << "[COO matrix file] [Vector file] [Destination file] " << std::endl;
		return -1;
	}
	
	AOSMatrix A;
	try{
	A.readMatrix()
	}catch
	return 0;
}

