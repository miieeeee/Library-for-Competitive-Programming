#include <vector>
#include <algorithm>
#include "Math/Prime/divisor_transform.hpp"

template<typename T>
std::vector<T> lcm_convolution(const std::vector<T> &a, const std::vector<T> &b){
    int n = std::max(a.size(), b.size());
    std::vector<T> A(n, 0), B(n, 0);
    for(int i=0; i<(int)a.size(); i++) A[i] = a[i];
    for(int i=0; i<(int)b.size(); i++) B[i] = b[i];
    divisor_zeta(A); divisor_zeta(B);
    std::vector<T> CONV(n);
    for(int i=1; i<n; i++){
        CONV[i] = A[i]*B[i]; 
    }
    divisor_mobius(CONV);
    return CONV;
}