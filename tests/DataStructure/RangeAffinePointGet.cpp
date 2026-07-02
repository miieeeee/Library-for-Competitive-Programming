#include "DataStructure/SegTree/DualSegtree.hpp"
#include "atcoder/modint.hpp"
#include <iostream>
#include <vector>
using namespace std;
using mint = atcoder::modint998244353;

struct S {
    mint b, c;
};

S composition(S f, S g) {
    return {f.b*g.b, f.b*g.c + f.c};
}

S id() {
    return {1, 0};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    DualSegtree<S, composition, id> seg(n);
    vector<int> a(n);
    
    for(int i=0; i<n; i++) {
        cin >> a[i];
    }

    while(q--) {
        int t; cin >> t;
        if(t == 0) {
            int l, r, b, c;
            cin >> l >> r >> b >> c;
            seg.apply(l, r, {b, c});
        }
        else {
            int i; cin >> i;
            auto f = seg.get(i);
            cout << (f.b*a[i] + f.c).val() << "\n";
        }
    }
}
