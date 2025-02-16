#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>
#include "csr_utility.h"
#include "vector_utility.h"

int main(int argc, char ** argv){
	if (argc < 2) std::cerr << "Expected format is ./page_rank <input file>\n";
	std::ifstream file {argv[1]};
	//Might want to do an error check here

	CSR<double> * csr_input = new CSR<double>;
	file >> csr_input;
	std::cout << csr_input;
	//std::cout << "\n" << csr_input->columns << "\n";

	CSR<double> * csr = new CSR<double>;
	std::cout << transpose(csr_input, csr);
	
	unsigned N = csr->ptr.size() - 1;
	double vo_start = 1 / (double) N;

	std::vector<double> V;
	std::vector<double> Vo;
	for (unsigned i = 0; i < N; ++i){
		V.push_back(0.0);
		Vo.push_back(vo_start);
	}
	std::cout << Vo;

	(*csr) *= 2.0;
	std::cout << csr;

	V = csr * Vo;
	std::cout << V;
		
	//result = csr * x;
	//for (const auto& val : result) std::cout << val << "\n";
	//std::cout << result;
	//std::vector<int> adder {9,9,9};
	//result = result + adder;
	//for (const auto& val : result) std::cout << val << "\n";
	//std::cout << result;

	//csr *= 2.0;
	//for (const auto& val : csr.values) std::cout << val << "\n";
	//std::cout << csr->values;
	delete csr;
	delete csr_input;
	return 0;
}
