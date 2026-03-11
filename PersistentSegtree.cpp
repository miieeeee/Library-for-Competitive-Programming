#include<bits/stdc++.h>
using namespace std;
template<typename S, auto op, auto e>
struct PersistentSegtree{
    struct Node{
        Node *l,*r;
        S value;
    };
    Node *last;
    int sz;
    int log;
    vector<Node*> roots;
    PersistentSegtree(vecotr<T> &data):sz(data.size()){
        log = 1;
        while(log<sz){
            log <<= 1;
        }
        log <<= 1;
        roots.reserve(1<<20);
        last = build(v);
        roots.push_back(last);
    }
    PersistentSegtree(int n):sz(n){
        log = 1;
        while(log<sz){
            log <<= 1;
        }
        log <<= 1;
        Node *root;
        root->l = nullptr;
        root->r = nullptr;
        roots.reserve(1<<20);
    }
    Node *build(vector<S> &data, int l=0, int r=sz){
        Node *ret;
        if(r-l == 1){
            ret->value = data[l];
            return &ret;
        }
        Node *nl = build(data, l, (l+r)/2), *nr = build(data, (l+r)/2, r);
        ret->l = nl, ret->r = nr;
        ret->value = op(nl->value, nr->value); 
        return &ret;
    }
    Node *update(Node *node, int p, S x, int l, int r){
        if(p < l || p >= r) return *node;
        Node ret;
        if(r-l == 1){
            ret.value = x;
            return &ret;
        }
        Node *nl = update(l, (l+r)/2), *nr = update((l+r)/2, r);
        ret.l = nl, ret.r = nr;
        ret.value = op(nl->value, nr->value);
        return &ret;
    }
    Node *update(int t, int p, S x, int l, int r){
        return update(roots[t], p, x, l, r);
    }
    S prod(Node *node, int l, int r, int i=0, int j=sz){
        if(r <= i || l >= j) return S();
        if(l <= i && j <= r) return node->value;
        return op(prod(node->l, l, r, i, (i+j)/2), prod(node->r, l, r, (i+j)/2, j));
    }
    S prod(int t, int l, int r){
        return prod(roots[t], l, r);
    }
};

int main(){
    
}