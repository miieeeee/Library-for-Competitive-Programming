#pragma once

#include <vector>
#include "Math/Modint/MontgomeryModint64.hpp"

bool miller_rabin(long long n) {
    using mint = MontgomeryModInt64;

    if(n < 2 || (n&1) == 0) return n == 2;
    long long d = n-1;
    while((d&1) == 0) d >>= 1;

    std::vector<long long> as;
    if(n < (1<<30)) as = {2, 7, 61};
    else as = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};

    mint::set_mod(n);
    for(long long a : as) {
        if(a >= n) break;
        long long t = d;
        mint x = mint(a).pow(d);
        if(x != 1) {
            while(t < n-1 && x != n-1) {
                x *= x;
                t <<= 1;
            }
            if(t == n-1 && x != n-1) return false;
        }
    }
    return true;
} // https://drken1215.hatenablog.com/entry/2023/05/23/233000