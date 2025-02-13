#ifndef VECTOR_UTILS
#define VECTOR_UTILS

template <typename T>
std::vector<T> operator+(const std::vector<T>& a, const std::vector<T>& b);

template <typename T>
std::vector<T> teleport(const T d, const int total);

#endif
