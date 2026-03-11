#include <bits/stdc++.h>
// #include "../../Algorithm/Monotone/monotone_minima.hpp"
using namespace std;

template <class T>
vector<T> concave_max_plus_convolution(const vector<T> &a, const vector<T> &b, T e) {
  const int n = a.size();
  const int m = b.size();
  const auto get = [&](int i, int j) {
    if(j >= n || i-j < 0 || i-j >= m) return e;
    return a[j] + b[i - j];
  };
  const auto comp = [&](T x, T y){
    return x > y;
  };
  vector<pair<int, T>> amax = monotone_minima<T>(n + m - 1, n, get, comp);
  vector<T> c(n + m - 1);
  for (int i=0; i < n+m-1; i++){
    c[i] = amax[i].second;
  }
  return c;
}
