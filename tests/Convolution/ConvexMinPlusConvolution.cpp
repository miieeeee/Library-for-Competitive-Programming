#include "Convolution/MinPlusPlus/ConvexMinPlusConvolutno.hpp"
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

    auto c = convex_min_plus_convolution(a, b, int(2e9));
    for(int i=0; i<n+m-1; i++) cout << c[i] << " ";
    cout << endl;
}