#pragma once 

template<typename G>
struct HLDecomposition{
    int n, root;
    G g;
    vector<int> sz, in, out, par, rev, head, depth;
    private:
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
                head[nv] = (nv == g[v][0] ? head[v] : nv);
                dfs_hld(nv, v, t);
            }
            out[v] = t;
        }

        vector<pair<int, int>> ascend(int u, int v) const {
            vector<pair<int, int>> ret;
            while(head[u] != head[v]) {
                ret.emplace_back(in[head[u]], in[u]+1);
                u = par[head[u]];
            }
            if(u != v) ret.emplace_back(in[v]+1, in[u]+1);
            return ret;
        }
    public:
        HLDecomposition(G &_g):g(_g), n(_g.size()), sz(_g.size()), in(_g.size()), out(_g.size()), par(_g.size()), rev(_g.size()), head(_g.size()), depth(_g.size(), 0){}

        void build(int _root = 0){
            root = _root;
            dfs_sz(_root, -1);
            int t = 0;
            dfs_hld(_root, -1, t);

        }

        int la(int v, int k){
            while(true){
                int u = head[v];
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
            if(head[u] == head[v]) return u;
            return lca(u, par[head[v]]);
        }

        int index(int u) const {
            return in[u];
        }

        // f(left, right, bool reverse)
        // (u - parent[u]) edge weight -> (u) vertex weight
        template <typename F>
        void path_query(int u, int v, bool edge, const F& f){
            int l = lca(u, v);
            auto utl = ascend(u, l);
            auto ltv = ascend(v, l);
            reverse(ltv.begin(), ltv.end());
            for(auto [a, b] : utl) f(a, b, true);
            if(!edge) f(in[l], in[l]+1, false);
            for(auto [a, b] : ltv) f(a, b, false);
        }

        // f(left, right)
        // (u - parent[u]) edge weight -> (u) vertex weight
        template <typename F>
        void subtree_query(int x, bool edge, const F& f) {
            f(in[x] + int(edge), out[x]);
        }
};