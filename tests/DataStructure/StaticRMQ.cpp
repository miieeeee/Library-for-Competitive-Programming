#include "DataStructure/SparseTable/SparseTable.hpp"
#include <iostream>
#include <vector>
using namespace std;

int op(int a, int b) {
    return min(a, b);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, q;
    cin >> n >> q;

    SparseTable<int, op> st(n);
    for(int i=0; i<n; i++) {
        int a; cin >> a;
        st.set(i, a);
    }
    st.build();

    while(q--) {
        int l, r;
        cin >> l >> r;
        cout << st.prod(l, r) << "\n";
    }
}