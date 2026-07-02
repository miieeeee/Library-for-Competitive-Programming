#include "DataStructure/Trie/BinaryTrie.hpp"
#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int q;
    cin >> q;

    BinaryTrie<int, 30> bt;
    while(q--) {
        int t, x;
        cin >> t >> x;
        if(t == 0 && bt.count(x) == 0) bt.add(x);
        if(t == 1) bt.del(x);
        if(t == 2) bt.apply_xor(x), cout << bt.kth_element(0) << "\n", bt.apply_xor(x);
    }
}
