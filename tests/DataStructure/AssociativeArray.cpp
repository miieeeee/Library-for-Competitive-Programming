#include "DataStructure/HashMap/HashMap.hpp"
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int q;
    cin >> q;
    HashMap<long long> hm(2*q);
    while(q--) {
        int t;
        cin >> t;
        if(t == 0) {
            long long k, v;
            cin >> k >> v;
            hm[k] = v;
        }
        else {
            long long k;
            cin >> k;
            cout << hm.get(k, 0) << "\n";
        }
    }
}