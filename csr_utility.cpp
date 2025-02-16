#include <cstdlib>
#include <iostream>
#include <vector>
#include <utility>
#include <typeinfo>
#include "csr_utility.h"

//template struct CSR<int>;
template struct CSR<double>;
template std::vector<double> operator*(const CSR<double>*, const std::vector<double>&);
template std::vector<int> operator*(const CSR<int>*, const std::vector<int>&);
//template void CSR::operator*=(const int coefficient);
//template void CSR::operator*=(const double coefficient);
template CSR<double>* transpose(CSR<double>*, CSR<double>*);
//template std::istream& operator>>(std::istream&, CSR<int>&);
template std::istream& operator>>(std::istream&, CSR<double>*);
template std::ostream& operator<<(std::ostream&, const CSR<double>*);

template <typename T>
std::vector<T> CSR<T>::vector_mult(const std::vector<T>& x) const{
	int spot = 0, count = 0;
	T sum = 0;
	std::vector<T> result;

	for (int i = 0; i < ptr.size() - 1; ++i){
		sum = count = 0;
		for (int j = 0; count < ptr[i+1] - ptr[i]; ++j){
			if (j == indices[spot]){
				sum += x[j] * values[spot];
				++spot; ++count;
				//std::cout << sum << ", ";
			}
		}
		result.push_back(sum);
	}
	return result;
}

template <typename T>
std::vector<T> operator*(const CSR<T>* csr, const std::vector<T>& x){
	return csr->vector_mult(x);
}

template <typename T>
void CSR<T>::operator*=(const T coefficient){
	for (auto& value : this->values)
		value = value * coefficient;
	//return csr;
}

template <typename T>
CSR<T>* transpose(CSR<T>* old, CSR<T>* newby){
    //CSR<T> newby;
    newby->columns = old->ptr.size() - 1;

    for (int i = 0; i < old->columns + 1; ++i)
        newby->ptr.push_back(0);
        
    for (const auto& ind : old->indices){
        newby->ptr[ind + 1]++;
        newby->values.push_back(0);
        newby->indices.push_back(0);
	}
        
    for (int i = 1; i < old->columns + 1; ++i)
        newby->ptr[i] += newby->ptr[i-1];
    newby->ptr[0] = 0;
        
    auto temp = newby->ptr;
    
    T v,c = 0;
    for(int i = 0; i < old->ptr.size() - 1; ++i){
     for(int j = old->ptr[i]; j < old->ptr[i + 1]; ++j){
        v = old->values[j];
        c = old->indices[j];
        newby->indices[temp[c]] = i;
        newby->values[temp[c]] = v;
        temp[c]++;
     }
    }
    
    return newby;
}


template <typename T>
std::istream& operator>>(std::istream& file, CSR<T>* csr){

	unsigned first_num;
	unsigned second_num;
	char buf;
	unsigned tracker = 0;
	unsigned count;
	T non_zero;
	std::vector<std::pair<unsigned, unsigned>> buffer;
	unsigned max_row_col = 0;

	csr->ptr.push_back(0);
	while (file >> first_num){
		//Below while loop solves the silent node problem
		while (first_num > tracker){
			csr->ptr.push_back(0);
			++tracker;
		}
		//New row found, prepping coordinates belonging to row
		csr->ptr.push_back(0);
		count = 0;
		file >> buf >> second_num;
		++count;

		buffer.push_back({first_num, second_num});

		while(file.peek() == ','){
			file >> buf >> second_num;

			buffer.push_back({first_num, second_num});

			++count;
		}
		//All non-zero coordinates in row should be read into buffer

		max_row_col = second_num > max_row_col ? second_num : max_row_col;
		max_row_col = first_num > max_row_col ? first_num : max_row_col;

		T non_zero = 1 / (T) count;
		//std::cout << typeid(non_zero).name() << "\n" << count << "\n" << (1 / count) << "\n";
		//Populating non-zeroes in row major order
		for (const auto& coordinate : buffer){
			csr->values.push_back(non_zero);
			//std::cout << non_zero << "\n";
			csr->indices.push_back(coordinate.second);
			csr->ptr[coordinate.first + 1]++;
		}
		buffer.clear();
		++tracker;
	}
	//adjusting ptr to contains entry numbers, as per requirement
	for (int i = 1; i < csr->ptr.size(); ++ i) csr->ptr[i] += csr->ptr[i-1];

	csr->columns = max_row_col + 1;

	return file;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const CSR<T>* csr){
	os << "[";
	for (const auto& val : csr->values) os << val << ", ";
	os << "]\n";
	os << "[";
	for (const auto& ind : csr->indices) os << ind << ", ";
	os << "]\n";
	os << "[";
	for (const auto& pts : csr->ptr) os << pts << ", ";
	os << "]\n";

	return os;
}
