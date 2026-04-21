#pragma once

template <typename G>
struct DsuOnTree {
private:
    int _n, _root;
    vector<int> _subsz;
    vector<int> _heavy;
    G _g;

    int dfs_sz(int v, int pv) {
        _subsz[v] = 1;
        int max_sz = 0;
        _heavy[v] = -1;

        for (auto nv : _g[v]) {
            if (nv == pv) continue;
            int sz_nv = dfs_sz(nv, v);
            _subsz[v] += sz_nv;

            if (sz_nv > max_sz) {
                max_sz = sz_nv;
                _heavy[v] = nv;
            }
        }
        return _subsz[v];
    }

    int _skip = -1;

    template <typename UPDATE>
    void dfs_update(int v, int pv, UPDATE &update) {
        update(v);
        for (auto nv : _g[v]) {
            if (nv == pv || nv == _skip) continue;
            dfs_update(nv, v, update);
        }
    }

public:
    DsuOnTree(G &g, int root)
        : _g(g), _n(g.size()), _subsz(g.size()), _heavy(g.size(), -1), _root(root) {}

    template <typename ADD, typename DEL, typename QUERY>
    void run(ADD &add, DEL &del, QUERY &query) {
        dfs_sz(_root, -1);

        auto dfs = [&](auto self, int v, int pv, bool keep) -> void {
            for (auto u : _g[v]) {
                if (u == pv || u == _heavy[v]) continue;
                self(self, u, v, false);
            }

            if (_heavy[v] != -1) {
                self(self, _heavy[v], v, true);
                _skip = _heavy[v];
            }

            for (auto u : _g[v]) {
                if (u == pv || u == _heavy[v]) continue;
                dfs_update(u, v, add);
            }
            add(v);

            query(v);

            _skip = -1;

            if (!keep) {
                dfs_update(v, pv, del);
            }
        };

        dfs(dfs, _root, -1, false);
    }
};