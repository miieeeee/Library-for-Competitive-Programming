#include <bits/stdc++.h>
#include "Convolution/PlusXorProd/xor_convolution.hpp"
#include "atcoder/modint.hpp"
using namespace std;
using mint = atcoder::modint998244353;

int main() {
    int n;
    cin >> n;
    vector<mint> a(1<<n), b(1<<n);
    for(int i=0; i<(1<<n); i++) {
        int x; cin >> x;
        a[i] = x;
    }
    for(int i=0; i<(1<<n); i++) {
        int x; cin >> x;
        b[i] = x;
    }

    auto c = xor_convolution(a, b);

    for(int i=0; i<(1<<n); i++) {
        cout << c[i].val() << " ";
    }
    cout << endl;
}