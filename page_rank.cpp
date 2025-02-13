#include <cstdlib>
#include <iostream>
#include <vector>
#include "csr_utility.h"
#include "vector_utility.h"

int main(void){
	CSR<int> csr;
	csr.values.push_back(1);
	csr.values.push_back(2);
	csr.values.push_back(3);
	csr.values.push_back(4);
	csr.values.push_back(5);
	csr.values.push_back(6);
	csr.indices.push_back(0);
	csr.indices.push_back(2);
	csr.indices.push_back(0);
	csr.indices.push_back(2);
	csr.indices.push_back(1);
	csr.indices.push_back(3);
	csr.ptr.push_back(0);
	csr.ptr.push_back(2);
	csr.ptr.push_back(4);
	csr.ptr.push_back(6);

	std::vector<int> result {9,9,9};
	std::vector<int> x {1,0,2,0};
	result = csr * x;
	for (const auto& val : result) std::cout << val << "\n";
	std::vector<int> adder {9,9,9};
	result = result + adder;
	for (const auto& val : result) std::cout << val << "\n";

	csr *= 2;
	for (const auto& val : csr.values) std::cout << val << "\n";
	return 0;
}
