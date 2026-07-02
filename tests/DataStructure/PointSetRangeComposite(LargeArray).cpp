#include "DataStructure/SegTree/DynamicSegTree.hpp"
#include <atcoder/modint>
#include <iostream>
using namespace std;
using mint = atcoder::modint998244353;

struct X {
    mint c, d;
};
struct MX {
    using value_type = X;
    static X op(X a, X b) {
        return  {b.c*a.c, b.c*a.d + b.d};
    }
    static X id() {
        return {1, 0};
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    const int SZ = 1<<20;
    DynamicSegTree<MX, SZ> seg(0, n+1);
    auto root = seg.new_root();
    while(q--) {
        int t;
        cin >> t;
        if(t == 0) {
            int p, c, d;
            cin >> p >> c >> d;
            root = seg.set(root, p, {c, d});
        }
        else {
            int l, r, x;
            cin >> l >> r >> x;
            auto f = seg.prod(root, l, r);
            cout << (f.c*x + f.d).val() << "\n";
        }
    }
}