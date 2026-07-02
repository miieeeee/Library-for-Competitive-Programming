#pragma once

#include "Algorithm/Monotone/monotone_minima.hpp"

/// @brief 非凹数列と凹数列の max plus convolution
/// @tparam T 
/// @param a 非凹数列
/// @param b 凹数列
/// @param e -INF
/// @return 
template <class T>
std::vector<T> concave_max_plus_convolution(const std::vector<T> &a, const std::vector<T> &b, T e) {
  const int n = a.size();
  const int m = b.size();
  const auto get = [&](int i, int j) {
    if(j >= n || i-j < 0 || i-j >= m) return e;
    return a[j] + b[i - j];
  };
  const auto comp = [&](T x, T y){
    return x > y;
  };
  std::vector<std::pair<int, T>> amax = monotone_minima<T>(n + m - 1, n, get, comp);
  std::vector<T> c(n + m - 1);
  for (int i=0; i < n+m-1; i++){
    c[i] = amax[i].second;
  }
  return c;
}
