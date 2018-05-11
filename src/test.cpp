#include <iostream>
#include <vector>


int main(){
	std::vector<int>::size_type sz;

	std::vector<int> foo;
	sz = foo.capacity();
	std::cout << "making foo grow \n" << std::endl;
	std::cout << "Default : " << sz << std::endl;
	for(int i =0; i < 50 ; ++i){
		foo.push_back(i);
		if(sz != foo.capacity()){
			sz = foo.capacity();
			std::cout << "capacity changed" << sz << std::endl;
			std::cout << "vector values " << foo[i] << std::endl;
		}
	}
	std::vector<int> bar;
	sz = bar.capacity();
	bar.reserve(100);
	std::cout << "making bar grow \n" << std::endl;
	for(int i=0; i<100; ++i){
		bar.push_back(i);
		if(sz!=bar.capacity()){
			sz = bar.capacity();
			std::cout << "capacity changed \n" << sz << std::endl;
		}
	}
	
	return 0;
}