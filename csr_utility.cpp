#include <cstdlib>
#include <iostream>
#include <vector>
#include "csr_utility.h"

template struct CSR<int>;
template struct CSR<double>;
template std::vector<double> operator*(const CSR<double>&, const std::vector<double>&);
template std::vector<int> operator*(const CSR<int>&, const std::vector<int>&);
template CSR<int>& operator*=(CSR<int>&, const int);
template CSR<double>& operator*=(CSR<double>&, const double);
template CSR<double> transpose(CSR<double>&);

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

template <typename T>
std::vector<T> operator*(const CSR<T>& csr, const std::vector<T>& x){
	return csr.vector_mult(x);
}

template <typename T>
CSR<T>& operator*=(CSR<T>& csr, const T coefficient){
	for (auto& value : csr.values)
		value = value * coefficient;
	return csr;
}

template <typename T>
CSR<T> transpose(CSR<T>& old){
    CSR<T> newby;
    newby.columns = old.ptr.size() - 1;

    for (int i = 0; i < old.columns + 1; ++i)
        newby.ptr.push_back(0);
        
    for (const auto& ind : old.indices){
        newby.ptr[ind + 1]++;
        newby.values.push_back(0);
        newby.indices.push_back(0);
	}
        
    for (int i = 1; i < old.columns + 1; ++i)
        newby.ptr[i] += newby.ptr[i-1];
    newby.ptr[0] = 0;
        
    auto temp = newby.ptr;
    
    int v,c = 0;
    for(int i = 0; i < old.ptr.size() - 1; ++i){
     for(int j = old.ptr[i]; j < old.ptr[i + 1]; ++j){
        v = old.values[j];
        c = old.indices[j];
        newby.indices[temp[c]] = i;
        newby.values[temp[c]] = v;
        temp[c]++;
     }
    }
    
    return newby;
}
