#pragma once

template <typename G> 
struct CentroidDecompositionBinaryTree {
    G g;
    int n;
    private:
        struct Index {
            int vid, p;
        };
        struct QueryRange {
            int vid, lp, rp;
        };
        struct Node {
            int id, cen, siz, lid, rid, pid, sid;
            Node() {}
            Node(int _id, int _cen, int _siz, int _lid, int _rid, int _pid, int _sid): id(_id), cen(_cen), siz(_siz), lid(_lid), rid(_rid), pid(_pid), sid(_sid) {}
        };
        struct AncestorInfo {
            int node_id, dist_to_cen;
        };

        int __bt_node_count = 0;
        vector<vector<int>> vecs;
        vector<vector<int>> vecs_depth_seps;
        vector<vector<Index>> indexes;
        vector<bool> used;
        vector<Node> bt_nodes;
        vector<int> depth, depth2;
        vector<int> sz;
        vector<int> leaves;
        vector<vector<AncestorInfo>> ancestors;

        int dfs(int v, int pv, int dep) {
            sz[v] = 1;
            depth[v] = dep;
            for(auto nv : g[v]) {
                if(used[nv] || pv == nv) continue;
                sz[v] += dfs(nv, v, dep+1);
            }

            return sz[v];
        }

        int get_centroid(int v, int pv, const int &tot) {
            for(auto nv : g[v]) {
                if(!used[nv] && pv != nv && sz[nv]*2 > tot) return get_centroid(nv, v, tot);
            }

            return v;
        }

        int new_node(int cen, const vector<int> &vec, const vector<int> &seps, int lid=-1, int rid=-1, int sid=-1) {
            int vid = __bt_node_count++;
            vecs.push_back(vec);
            vecs_depth_seps.push_back(seps);
            bt_nodes.emplace_back(vid, cen, vec.size(), lid, rid, -1, sid);

            return vid;
        }

        int merge(int lid, int rid) {
            Node l_node = bt_nodes[lid];
            Node r_node = bt_nodes[rid];
            assert(l_node.cen == r_node.cen);
            auto &lsep = vecs_depth_seps[lid];
            auto &rsep = vecs_depth_seps[rid];
            int max_depth = max(int(lsep.size()), int(rsep.size()))-2;
            vector<int> vec;
            vector<int> seps(max_depth+2, l_node.siz + r_node.siz);
            vec.reserve(l_node.siz + r_node.siz);
            int lp = 0, rp = 0;
            for(int i=0; i<=max_depth; i++) {
                seps[i] = vec.size();
                while(i+1 < lsep.size() && lp < lsep[i+1]) vec.push_back(vecs[lid][lp++]);
                while(i+1 < rsep.size() && rp < rsep[i+1]) vec.push_back(vecs[rid][rp++]);
            }

            int id = new_node(l_node.cen, vec, seps, lid, rid);
            bt_nodes[lid].pid = id;
            bt_nodes[rid].pid = id;
            bt_nodes[lid].sid = rid;
            bt_nodes[rid].sid = lid;

            return id;
        }

        void rearrange(int node_id, int root) {
            vector<int> que;
            vector<int> par;
            vector<int> dep;
            vector<int> seps;
            que.push_back(root);
            dep.push_back(1);
            par.push_back(-1);
            seps.push_back(0);
            for(int i=0; i<que.size(); i++) {
                if(int(seps.size()) <= dep[i]) seps.push_back(i);
                int v = que[i];
                for(auto nv : g[v]) {
                    if(used[nv] || par[i] == nv) continue;
                    que.push_back(nv);
                    par.push_back(v);
                    dep.push_back(dep[i]+1);
                }
            }
            seps.push_back(que.size());

            vecs[node_id] = que;
            vecs_depth_seps[node_id] = seps;
        }

        int decompose(int v, int d) {
            int tot = dfs(v, -1, 0);
            int cen = get_centroid(v, -1, tot);
            used[cen] = true;
            using P = pair<int, int>; 
            priority_queue<P, vector<P>, greater<P>> que;
            {
                vector<int> vs = {cen};
                vector<int> sep = {0, 1};
                int node_id = new_node(cen, vs, sep);
                que.push({1, node_id});
                leaves[cen] = node_id;
            }
            for(auto nv : g[cen]) {
                if(used[nv]) continue;
                int node_id = decompose(nv, d+1);
                rearrange(node_id, nv);
                bt_nodes[node_id].cen = cen;
                que.push({bt_nodes[node_id].siz, node_id}); // cen始点のbfs順になっている必要がある
            }

            // merge
            while(que.size() >= 2) {
                auto [asz, a] = que.top(); que.pop();
                auto [bsz, b] = que.top(); que.pop();
                int c = merge(a, b);
                que.push({bt_nodes[c].siz, c});
            }

            used[cen] = false;

            return que.top().second;
        }

        void build_indexes() {
            for(int vid=0; vid<__bt_node_count; vid++) {
                for(int p=0; p<vecs[vid].size(); p++) {
                    indexes[vecs[vid][p]].push_back({vid, p});
                }
            }
        }

        void build_ancestors() {
            for(int node_id=0; node_id<__bt_node_count; node_id++) {
                int dist = 0;
                auto &seps = vecs_depth_seps[node_id];
                auto &vec = vecs[node_id];
                for(int i=0; i<vec.size(); i++) {
                    while(seps[dist] == i) dist++;
                    ancestors[vec[i]].push_back({node_id, dist-1});
                }
            }
        }

        void dump() {
            for(int i=0; i<__bt_node_count; i++) {
                printf("------------------node_%d-------------------\n", i);
                printf("cen: %d, left child: %d\nright child: %d\nparent: %d\n", bt_nodes[i].cen, bt_nodes[i].lid, bt_nodes[i].rid, bt_nodes[i].pid);
                cout << vecs[i] << endl;
                cout << vecs_depth_seps[i] << endl;
            }
        }
    public:
        CentroidDecompositionBinaryTree() {}
        CentroidDecompositionBinaryTree(G &_g): g(_g), n(g.size()) {}

        void build() {
            depth.resize(n);
            sz.resize(n);
            leaves.resize(n);
            used.assign(n, false);
            indexes.assign(n, {});
            ancestors.assign(n, {});
            decompose(0, 0);
            build_indexes();
            build_ancestors();
        }

        /// クエリ用配列の個数
        int get_vec_count() {
            return __bt_node_count;
        }

        /// 頂点vをの値を格納する配列の位置
        vector<Index> get_indexes(int v) {
            assert(0 <= v && v < n);
            return indexes[v];
        }

        /// クエリ用配列vidの頂点列
        vector<int> get_vec(int vid) {
            assert(0 <= vid && vid < __bt_node_count);
            return vecs[vid];
        }

        /// 頂点vからlb以上ub未満離れた頂点列をちょうど一度ずつ格納する配列・区間の列
        vector<QueryRange> get_contour_query_range(int v, int lb, int ub) {
            vector<QueryRange> res;
            int cur = leaves[v];
            int i=0;
            if(lb == 0 && ub > 0) res.push_back({cur, 0, 1});
            while(bt_nodes[cur].pid != -1) {
                auto sid = bt_nodes[cur].sid;
                int d = ancestors[v][i++].dist_to_cen;
                int lp = vecs_depth_seps[sid][min(int(vecs_depth_seps[sid].size())-1, max(0, lb-d))];
                int rp = vecs_depth_seps[sid][min(int(vecs_depth_seps[sid].size())-1, max(0, ub-d))];
                if(lp < rp) res.push_back({sid, lp, rp});
                cur = bt_nodes[cur].pid;
            }

            return res;
        }
};