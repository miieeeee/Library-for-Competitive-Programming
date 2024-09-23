#include<bits/stdc++.h>
using namespace std;
struct UnionFind{
    vector<int> par;
    UnionFind(int n){
        par.resize(n, -1);
    }
    int root(int x){
        if(par[x] < 0) return x;
        return par[x] = root(par[x]);
    }
    bool same(int x, int y){
        return root(x) == root(y);
    }
    bool merge(int x, int y){
        x = root(x), y = root(y);
        if(x == y) return false;
        if(par[x] < par[y]){
            swap(x, y);
        }
        par[x] += par[y];
        par[y] = x;
        return true;
    }
};
struct RangeParallelUnionFind{
    vector<UnionFind> ufs;
    RangeParallelUnionFind(int n){
        int sz = 0;
        while((1<<sz+1) <= n) sz++;
        ufs.resize(sz+2, UnionFind(n));
    }
    int root(int x){
        return ufs[0].root(x);
    }
    bool same(int x, int y){
        return root(x)==root(y);
    }
    template<typename F> void merge(int x, int y, int len, F f){
        if(len == 0){
            return;
        }
        if(len == 1){
            _merge(x, y, 0, f);
            return;
        }
        int k = 0;
        while((1<<k+1)<=len-1) k++;
        _merge(x, y, k, f);
        _merge(x+len-(1<<k), y+len-(1<<k), k, f);
    }
    private:
    template<typename F> void _merge(int x, int y, int k, F f){
        if(k == 0){
            int a = ufs[0].root(x), b = ufs[0].root(y);
            if(ufs[0].merge(x, y)){
                int c = ufs[0].root(x);
                f(c, a^b^c);
            }
            return;
        }
        if(!ufs[k].merge(x, y)){
            return;
        }
        _merge(x, y, k-1, f);
        _merge(x+(1<<k-1), y+(1<<k-1), k-1, f);
    }
};