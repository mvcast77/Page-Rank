#include <cstdlib>
#include <iostream>
#include <vector>

template <typename T>
struct CSR {
	CSR(){}
	std::vector<T> values;
	std::vector<int> indices;
	std::vector<int> ptr;
	std::vector<T>& vector_mult(const std::vector<T>& x, std::vector<T>& result) const;
};

template <typename T>
std::vector<T>& CSR<T>::vector_mult(const std::vector<T>& x, std::vector<T>& result) const{
	int spot = 0, count = 0, sum = 0;
	result.clear();

	for (int i = 0; i < ptr.size() - 1; ++i){
		sum = count = 0;
		for (int j = 0; count < ptr[i+1] - ptr[i]; ++j){
			if (j == indices[spot]){
				sum += x[j] * values[spot];
				++spot; ++count;
			}
		}
		result.push_back(sum);
	}
	return result;
}

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
	result = csr.vector_mult(x, result);
	for (const auto& val : result) std::cout << val << "\n";
	return 0;
}
