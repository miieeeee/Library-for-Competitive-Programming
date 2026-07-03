#include "Math/Prime/Eratosthenes.hpp"
#include "DataStructure/HashMap/HashMap.hpp"
#include <atcoder/modint>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
using mint = atcoder::modint998244353;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;  
    string s;
    cin >> n >> s;
    Eratostheness et(n+1);
    HashMap<mint> f(2*et.divisor_enum(n).size()), g(2*et.divisor_enum(n).size());
    for(int d : et.divisor_enum(n)) {
        string t(d, '?');
        for(int i=0; i<n; i++) {
            if(s[i] == '.') t[i%d] = '#';
        }
        int cnt = 0;
        for(int i=0; i<d; i++) cnt += t[i] == '?';
        g[d] = mint(2).pow(cnt);
    }

    for(auto x : et.divisor_enum(n)) {
        for(auto d : et.divisor_enum(x)) {
            f[x] += et.mu[x/d]*g[d];
        }
    }

    cout << (g[n] - f[n]).val() << "\n";
}