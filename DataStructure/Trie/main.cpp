#include "BinaryTrie.hpp"

int main(){
    auto bt = BinaryTrie<int, 30>();
    int q;
    cin >> q;
    while(q--){
        int t, x;
        cin >> t >> x;
        if(t == 0){
            if(bt.count(x)) continue;
            bt.add(x);
        }
        if(t == 1){
            bt.del(x);
        }
        if(t == 2){
            bt.add_xor(x);
            cout << bt.kth_element(0) << endl;
            bt.add_xor(x);
        }
    }
}