#include <vector>
#include "Eratosthenes.hpp"

/// @brief A[k] = \sum_{i: k|i} a[i]（倍数方向のゼータ変換）
/// @tparam T 
/// @param a 
template<typename T>
void divisor_zeta(std::vector<T> &a){
    int n = a.size();
    std::vector<bool> is_prime = eratosthenes(n);
    for(int i=2; i<n; i++){
        if(!is_prime[i]) continue;
        for(int k=1; k*i<n; k++){
            a[k*i] += a[k]; 
        }
    }
}

/// @brief A[n] = \sum_{n|i} a[i]（倍数方向のメビウス変換）
/// @tparam T 
/// @param a 
/// @param is_prime 
template<typename T>
void divisor_mobius(std::vector<T> &A){
    int n = A.size();
    std::vector<bool> is_prime = eratosthenes(n);
    for(int i=2; i<n; i++){
        if(!is_prime[i]) continue;
        for(int k=(n-1)/i; k>0; k--){
            A[k*i] -= A[k];
        }
    }
    return;
}