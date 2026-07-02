#include <bits/stdc++.h>
#include "Convolution/PlusGcdProd/gcd_convolution.hpp"
#include "atcoder/modint.hpp"
using namespace std;
using mint = atcoder::modint998244353;

int main() {
    int n;
    cin >> n;
    vector<mint> a(n+1), b(n+1);
    for(int i=1; i<=n; i++) {
        int x; cin >> x;
        a[i] = x;
    }
    for(int i=1; i<=n; i++) {
        int x; cin >> x;
        b[i] = x;
    }

    auto c = gcd_convolution(a, b);
    for(int i=1; i<=n; i++) {
        cout << c[i].val() << " ";
    }
    cout << endl;
}
