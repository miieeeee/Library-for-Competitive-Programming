#pragma once

#include <vector>

struct UnionFind{
    std::vector<int> par;
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
            std::swap(x, y);
        }
        par[x] += par[y];
        par[y] = x;
        return true;
    }
};