#pragma once

struct CentroidTree {
    int root;
    vector<int> par;
    vector<vector<int>> adj;
};

template <typename G>
struct CentroidDecomposition {
    private:
        G g;
        int n;
        vector<int> sz;
        vector<int> par;
        vector<bool> used;
        vector<vector<int>> adj;
        vector<int> depth;

        int dfs_sz(int v, int pv) {
            sz[v] = 1;
            for(auto &nv : g[v]) {
                if(nv == pv || used[nv]) continue;
                sz[v] += dfs_sz(nv, v);
            }

            return sz[v];
        }

        int get_centroid(int v, int pv, int tot) {
            for(auto &nv : g[v]) {
                if(nv == pv || used[nv]) continue;
                if(sz[nv]*2 > tot) { return get_centroid(nv, v, tot); }
            }
            return v;
        }

        int decompose(int v, int pv, int d) {
            int tot = dfs_sz(v, -1);
            int cen = get_centroid(v, -1, tot);
            used[cen] = true;
            par[cen] = pv;
            depth[cen] = d;
            if(pv != -1) {
                adj[pv].push_back(cen);
                adj[cen].push_back(pv);
            }
            for(auto &nv : g[cen]) {
                if(used[nv]) continue;
                decompose(nv, cen, d+1);
            }

            used[cen] = false;
            return cen;
        }
    public:
        CentroidDecomposition() {}
        CentroidDecomposition(G _g) : g(_g), n(g.size()) {}

        CentroidTree build() {
            par.resize(n);
            sz.resize(n);
            used.assign(n, false);
            adj.assign(n, {});
            depth.assign(n, 0);
            int root = decompose(0, -1, 0);

            return {root, par, adj};
        }

        int parent_of(int v) {
            return par[v];
        }
};