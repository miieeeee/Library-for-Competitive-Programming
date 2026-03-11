#include <bits/stdc++.h>
#include "DataStructure/SegTree/DynamicSegTree.hpp"
using namespace std;

struct Monoid {
    using value_type = long long;
    static long long op(long long a, long long b) { return a+b; }
    static long long id() { return 0; }
};

int main(){
    int n, q;
    cin >> n >> q;
    DynamicSegTree<Monoid, 1<<20> seg(0, n);
    auto root = seg.new_root();
    vector<long long> a(n);
    for(int i=0; i<n; i++) {
        int x;
        cin >> x;
        a[i] = x; 
        root = seg.set(root, i, x);
    }

    while(q--) {
        int t;
        cin >> t;
        if(t == 0) {
            int p, x;
            cin >> p >> x;
            a[p] += x;
            root = seg.set(root, p, a[p]);
        }
        else {
            int l, r;
            cin >> l >> r;
            cout << seg.prod(root, l, r) << endl;
        }

    }
}