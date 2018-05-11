#include <iostream>
#include <fstream>
//#include <string>

//using namespace std;

int main(){
	std::string input_line, second;
	std::ifstream infile("inputCOOMatrix.txt");
	while(!infile.eof()){
		getline(infile, input_line);
		std::cout << input_line << std::endl;
		getline(infile, second);
		std::cout << second << std::endl;
	}
	return 0;
}