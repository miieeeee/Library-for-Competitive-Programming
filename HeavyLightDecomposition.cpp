#include<bits/stdc++.h>
#include<atcoder/all>
using namespace std;
using namespace atcoder;

template<typename G>
struct HeavyLightDecomposition{
    int n;
    G &g;
    vector<int> sz, in, out, par, rev, nxt, depth;
    HeavyLightDecomposition(G &g):g(g), n(g.size()), sz(g.size()), in(g.size()), out(g.size()), par(g.size()), rev(g.size()), nxt(g.size()), depth(g.size(),0){}
    void build(int root = 0){
        dfs_sz(root, -1);
        int t = 0;
        dfs_hld(root, -1, t);

    }
    void dfs_sz(int v, int pv){
        par[v] = pv;
        sz[v] = 1;
        for(int &nv : g[v]){
            if(nv == pv) continue;
            depth[nv] = depth[v]+1;
            dfs_sz(nv, v);
            sz[v] += sz[nv];
            if(sz[nv] > sz[g[v][0]]) swap(g[v][0], nv);
        }
        return;
    }

    void dfs_hld(int v, int pv, int &t){
        in[v] = t++;
        rev[in[v]] = v;
        for(int &nv : g[v]){
            if(nv == pv) continue;
            nxt[nv] = (nv == g[v][0] ? nxt[v] : nv);
            dfs_hld(nv, v, t);
        }
        out[v] = t;
    }

    int la(int v, int k){
        while(true){
            int u = nxt[v];
            if(in[v] - k >= in[u]) return rev[in[v]-k];
            k -= in[v] - in[u] + 1;
            v = par[u];
        }
    }

    int la(int u, int v, int k){
        int x = lca(u, v);
        int dist1 = depth[u] - depth[x];
        int dist2 = depth[v] - depth[x];
        if(dist1 + dist2 < k) return -1;
        if(dist1 >= k) return la(u, k);
        return la(v, dist1 + dist2 - k);
    }

    int lca(int u, int v){
        if(in[u] > in[v]){
            swap(u, v);
        }
        if(nxt[u] == nxt[v]) return u;
        return lca(u, par[nxt[v]]);
    }

    
    template<typename T, typename Q, typename F>
    T query(int u, int v, const T &e, const Q &q, const F &f, bool edge=false){
        T l = e, r = e;
        for(;;u=nxt[u]){
            if(in[u] < in[v]) swap(u, v), swap(l,r);
            if(nxt[u] == nxt[v]) break;
            l = f(q(nxt[in[u]], in[u]+1), l);
        }
        return f(f(q(in[v]+edge, in[u]+1), l), r);
    }

    template<typename Q>
    void add(int u, int v, const Q &q, bool edge=false){
        for(;;u=nxt[u]){
            if(in[u] < in[v]) swap(u, v);
            if(nxt[u] == nxt[v]) break;
            q(nxt[u], in[u]+1);
        }
        q(in[v]+edge, in[u]+1);
    }
};