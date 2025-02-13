#ifndef CSR_UTIL
#define CSR_UTIL


template <typename T>
struct CSR {
	CSR(){}
	std::vector<T> values;
	std::vector<int> indices;
	std::vector<int> ptr;
	std::vector<T>& vector_mult(const std::vector<T>& x, std::vector<T>& result) const;
};

#endif
