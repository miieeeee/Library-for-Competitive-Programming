#include <bits/stdc++.h>
#include "DataStructure/UnionFind/PersistentUnionFind.hpp"
#include "DataStructure/HashMap/HashMap.hpp"

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    using PUF = PersistentUnionFind;
    PUF uf;
    HashMap<PUF::np> ver(q+1);
    ver[-1] = uf.build(n);

    for(int i=0; i<q; i++) {
        int t;
        cin >> t;
        if(t == 0) {
            int k, u, v;
            cin >> k >> u >> v;
            ver[i] = uf.merge(ver[k], u, v).second;
        }
        else {
            int k, u, v;
            cin >> k >> u >> v;
            cout << (uf.same(ver[k], u, v) ? 1 : 0) << endl;
        }
    }
}