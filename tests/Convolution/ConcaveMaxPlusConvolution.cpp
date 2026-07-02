#include "Convolution/MaxPlusPlus/ConcaveMaxPlusConvolution.hpp"
#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
   
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    vector<int> b(m);
    for(int i=0; i<n; i++) cin >> a[i];
    for(int i=0; i<m; i++) cin >> b[i];
    for(auto &x : a) x = -x;
    for(auto &x : b) x = -x;

    auto c = concave_max_plus_convolution(b, a, -2001001001);
    for(int i=0; i<n+m-1; i++) cout << -c[i] << " ";
    cout << endl;
}