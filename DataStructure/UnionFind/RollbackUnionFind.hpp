#pragma once

struct RollbackUnionFind{
    vector<int> par;
    stack<pair<int, int>> history;
    int inner_snap;
    RollbackUnionFind(int sz) : inner_snap(0) {par.assign(sz,-1);}

    bool unite(int x,int y){
        x = find(x),y = find(y);
        history.emplace(x,par[x]);
        history.emplace(y,par[y]);
        if(x==y) return false;
        if(par[x] > par[y]) swap(x,y);
        par[x] += par[y];
        par[y] = x;
        return true;
    }

    int find(int k){
        if(par[k] < 0) return k;
        return find(par[k]);
    }

    int issame(int x,int y){
        return find(x) == find(y);
    }

    int size(int k){
        return (-par[find(k)]);
    }

    void undo(){
        par[history.top().first] = history.top().second;
        history.pop();
        par[history.top().first] = history.top().second;
        history.pop();
    }

    void snapshot(){
        inner_snap = int(history.size() >> 1);
    }

    int get_state(){
        return int(history.size() >> 1);
    }

    void rollback(int state = -1){
        if(state == -1) state = inner_snap;
        state <<= 1;
        assert(state <= (int)history.size());
        while(state < (int)history.size()) undo();
    }

};