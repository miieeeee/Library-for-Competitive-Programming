#pragma once
#include "Math/GCD/extGCD.hpp"

long long inv_mod(long long x, long long mod) {
    long long a, b;
    extGCD(x, mod, a, b);
    return a;
}