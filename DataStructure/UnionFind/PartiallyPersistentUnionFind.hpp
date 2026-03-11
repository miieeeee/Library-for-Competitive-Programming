#pragma once

#include <vector>
#include <algorithm>

/// @brief 追加した時刻毎にunionfindの結果が見れる
struct PartiallyPersistentUnionFind{
    // parは自分が根の時部分木のサイズを、そうでないとき親のノードを持つ
    std::vector<int> par;
    std::vector<int> ts;
    std::vector<std::vector<std::pair<int,int>>> size;
    int n;
    int now = 0;
    PartiallyPersistentUnionFind(int _n):n(_n){
        par.resize(n, 1);
        ts.resize(n, -1);
        size.resize(n, {std::make_pair(0, 1)});
    }

    int root(int v, int t){
        if(ts[v] > t) return v;
        return root(par[v], t);
    }

    int size(int v, int t){
        int v = root(v, t);
        int idx = upper_bound(size[v].begin(), size[v].end(), std::make_pair(t, -1)) - size[v].begin() - 1;
        return size[v][idx].second;
    }

    int unite(int u, int v){
        now++;
        int u = root(u, now), v = root(v, now);
        if(u == v) return now;
        if(par[u] < par[v]) std::swap(u, v);
        par[u] += par[v];
        par[v] = u;
        ts[v] = now;
        size[u].push_back(std::make_pair(now, par[u]));
        return now;
    }
};