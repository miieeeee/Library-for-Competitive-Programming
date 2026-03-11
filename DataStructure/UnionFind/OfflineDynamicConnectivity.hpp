#pragma once

struct RollbackUnionFind{
    using ll = long long;
    using P = pair<int, int>;
    vector<int> par;
    stack<P> history;
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

struct OfflineDynamicConnectivity{
    RollbackUnionFind uf;
    vector<vector<pair<int,int>>> seg;
    vector<vector<pair<int,int>>> qadd,qdel;
    map<pair<int,int>,pair<int,int>> cnt;
    int v,q,segsz;
    OfflineDynamicConnectivity(int v, int q):v(v),q(q),uf(v),qadd(q),qdel(q){
        segsz = 1;
        while(segsz < q){
            segsz <<= 1;
        }
        seg.resize(2*segsz);
    }

    void add_edge(int u, int v, int t){
        qadd[t].emplace_back(u, v);
    }

    void del_edge(int u, int v, int t){
        qdel[t].emplace_back(u, v);
    }

    void build(){
        for(int i=0;i<q;i++){
            for(auto& e : qadd[i]){
                auto& dat = cnt[e];
                if(dat.first++ == 0){
                    dat.second = i;
                }
            }
            for(auto& e : qdel[i]){
                auto& dat = cnt[e];
                if(--dat.first == 0){
                    segment(e, dat.second, i);
                }
            }
        }
        for(auto& [e,dat] : cnt){
            if(dat.first > 0){
                segment(e, dat.second, q);
            }
        }
    }

    template<typename ADD, typename DEL, typename QUERY>
    void dfs(const ADD& add, const DEL& del, const QUERY& query, int id, int l, int r){
        if(q <= l) return;
        int state = uf.get_state();
        vector<pair<int,int>> es;
        for(auto& [u,v] : seg[id]){
            if(!uf.issame(u, v)){
                uf.unite(u, v);
                add(u, v);
                es.emplace_back(u, v);
            }
        }
        if(l+1 == r){
            query(l);
        }
        else{
            dfs(add, del, query, 2*id, l, (l+r)>>1);
            dfs(add, del, query, 2*id+1, (l+r)>>1, r);
        }
        for(auto& [u,v] : es){
            del(u,v);
        }
        uf.rollback(state);
    }

    template<typename ADD, typename DEL, typename QUERY>
    void run(const ADD& add, const DEL& del, const QUERY& query){
        dfs(add, del, query, 1, 0, segsz);
    }

    private:
    void segment(pair<int,int> e, int l, int r){
        int L = l + segsz;
        int R = r + segsz;
        while (L < R) {
            if (L & 1) seg[L++].push_back(e);
            if (R & 1) seg[--R].push_back(e);
            L >>= 1, R >>= 1;
        }
    }
};