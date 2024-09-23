#include<bits/stdc++.h>
using namespace std;

template<typename S, typename F, auto mapping, auto composition, auto id>
struct DualSegtree{
    int n;
    int siz;
    int log;
    vector<F> lazy;
    vector<S> data;
    DualSegtree(vector<S> data, bool prop=true):data(data),prop(prop){
        n = data.size();
        log = 1;
        while((1<<log)<n) log++;
        siz = 1<<log;
        lazy.resize(2*(1<<log), id());
    }
    void apply(int l, int r, F f){
        all_apply(l, r, f);
        return;
    }
    S get(int idx){
        all_apply(idx, idx+1, id());
        return mapping(lazy[siz+idx], data[idx]);
    }
    private:
    bool prop;
    void push(int idx){
        lazy[2*idx] = composition(lazy[idx], lazy[2*idx]);
        lazy[2*idx+1] = composition(lazy[idx], lazy[2*idx+1]);
        lazy[idx] = id();
        return;
    }
    void all_apply(int l, int r, F f){
        if(l == r) return;
        l += siz, r += siz;
        if(prop) for(int i=log; i>=1; i--){
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i); 
        }
        while(l < r){
            if(l&1){
                lazy[l] = composition(f, lazy[l]);
                l++;
            }
            if(r&1){
                r--;
                lazy[r] = composition(f, lazy[r]);
            }
            l >>= 1, r >>= 1;
        }
        return;
    }
};