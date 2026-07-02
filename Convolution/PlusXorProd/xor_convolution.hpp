#pragma once

#include "Convolution/PlusXorProd/fast_hadmard_transform.hpp"

template<typename T>
std::vector<T> xor_convolution(std::vector<T> a, std::vector<T> b) {
    assert(a.size() == b.size());

    int sz = a.size();
    fast_hadmard_transform(a, false);
    fast_hadmard_transform(b, false);

    for(int i=0; i<sz; i++) {
        a[i] *= b[i];
    }

    fast_hadmard_transform(a, true);

    return a;
}