#include "Math/Prime/Eratosthenes.hpp"

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    Eratostheness et(n);
    for(int i=1; i<n; i++) {
        int sum = 0;
        for(auto d : et.divisor_enum(i)) {
            sum += et.mu[d];
        }
        assert(sum == (i == 1));
    }
}