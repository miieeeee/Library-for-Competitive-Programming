#include <bits/stdc++.h>
using namespace std;
using ll = long long;
/*
T:群
merge(hi, lo, w) : potential[hi]-potential[lo]=wになるようにマージ
diff(hi, lo) : -potential[lo] + potential[hi]（非可換群を考慮）
*/
template<typename T>
struct PotentialUnionFind{
    int n;
    vector<int> par;
    vector<T> pot;
    PotentialUnionFind(int sz):n(sz){
        init(sz);
    }
    void init(int sz){
        par.resize(sz, -1);
        pot.resize(sz, T());
    }
    int root(int x){
        if(par[x] < 0) return x;
        int r = root(par[x]);
        pot[x] = pot[par[x]] + pot[x];
        return par[x] = r;
    }
    T potential(int x){
        root(x);
        return pot[x];
    }
    bool same(int x, int y){
        return root(x) == root(y);
    }
    bool merge(int hi, int lo, T w){
        int rhi = root(hi), rlo = root(lo);
        if(rhi == rlo) return false;
        n--;
        if(par[rlo] > par[rhi]) swap(rhi, rlo), swap(hi, lo), w = -w;
        par[rlo] += par[rhi];
        par[rhi] = rlo;
        pot[rhi] = pot[lo] + w - pot[hi];
        T ret = pot[rhi];
        return true;
    }
    T diff(int hi, int lo){
        return -potential(lo)+potential(hi);
    }
    int size(){
      return n;
    }
};