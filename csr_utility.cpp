#include <cstdlib>
#include <iostream>
#include <vector>
#include "csr_utility.h"

template struct CSR<int>;

template <typename T>
std::vector<T> CSR<T>::vector_mult(const std::vector<T>& x) const{
	int spot = 0, count = 0, sum = 0;
	std::vector<T> result;

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

