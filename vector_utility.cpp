#include <cstdlib>
#include <vector>
#include "vector_utility.h"

template std::vector<int> operator+(const std::vector<int>&, const std::vector<int>&);

template <typename T>
std::vector<T> operator+(const std::vector<T>& a, const std::vector<T>& b){
	std::vector<T> result;

	int b_ind = 0;
	for (const auto& val : a)
		result.push_back(val + b[b_ind]);

	return result;
}

//template <typename T>
//std::vector<T> teleport(
