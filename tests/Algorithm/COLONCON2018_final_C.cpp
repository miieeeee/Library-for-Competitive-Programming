#include <bits/stdc++.h>
using namespace std;

#include "Algorithm/Monotone/monotone_minima.hpp"

// https://atcoder.jp/contests/colopl2018-final/tasks/colopl2018_final_c
int main() {
    using ll = long long;
    int n;
    cin >> n;
    vector<ll> a(n);
    for(int i=0; i<n; i++) cin >> a[i];
    auto get = [&](int i, int j) -> ll {
        return a[j] + (ll)(j-i)*(j-i);
    };
    auto comp = [&](ll x, ll y) -> bool {
        return x < y;
    };

    auto ans = monotone_minima<ll>(n, n, get, comp);

    for(auto [_, x] : ans) cout << x << endl;
}