#pragma once
#include <vector>
#include "Math/GCD/extGCD.hpp"

std::pair<long long, long long> crt(const std::vector<long long> &b, const std::vector<long long> &m) {
    long long r = 0, M = 1;
    for (int i=0; i<(int)b.size(); i++) {
        long long p, q;
        long long d = extGCD(M, m[i], p, q);
        if((b[i] - r)%d != 0) return std::make_pair(0, -1);
        long long tmp = (b[i] - r) / d * p % (m[i]/d);
        r += M*tmp;
        M *= m[i]/d;
    }
    return std::make_pair((r%M + M)%M, M);
}