#include<bits/stdc++.h>
#include "2Dsegtree.hpp"
using namespace std;

int op(int a, int b){
    return min(a, b);
}
int e(){
    return int(1e9);
}
int main(){
    int h, w;
    cin >> h >> w;
    SegmentTree2D<int, op, e> seg(h, w);
    for(int i=0; i<h; i++){
        for(int j=0; j<w; j++){
            int x;
            cin >> x;
            seg.set(i, j, x);
        }
    }
    seg.build();
    cout << seg.query(0, 0, 2, 2) << endl;
}