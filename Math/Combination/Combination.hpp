#pragma once
#include <vector>

template <typename T>
struct Combination {
    std::vector<T> fact, ifact;
    Combination(int sz): fact(sz+1), ifact(sz+1) {
        fact[0] = T(1);
        for(int i=0; i<sz; i++) {
            fact[i+1] = fact[i]*(i+1);
        }
        while(fact[sz] == 0) sz--;
        ifact[sz] = T(1) /fact[sz];
        for(int i=sz-1; i>=0; i--) {
            ifact[i] = ifact[i+1]*(i+1);
        } 
    }

    T P(int n, int r) const {
        if(r < 0 || n < r) return 0;
        return fact[n]*ifact[n-r];
    }

    T C(int n, int r) const {
        if(r < 0 || n < r) return 0;
        return fact[n]*ifact[r]*ifact[n-r];
    }
};