#pragma once

#include <vector>
#include <stack>
#include <algorithm>

struct EulerianTrail {
    struct Edge {
        int to, eid;
    };

    struct PathEdge {
        int from, to, eid;
    };

    struct Result {
        bool success;
        std::vector<int> nodes;
        std::vector<PathEdge> edges; // 辺のIDも含む詳細な通過履歴
    };

    struct EdgeDef {
        int u, v;
    };

    int n;
    bool is_directed;
    std::vector<std::vector<Edge>> adj;
    std::vector<EdgeDef> edge_defs;
    std::vector<int> in_deg, out_deg;
    int edge_cnt;

    EulerianTrail(int n, bool is_directed) 
        : n(n), is_directed(is_directed), adj(n), in_deg(n, 0), out_deg(n, 0), edge_cnt(0) {}

    void add_edge(int u, int v) {
        adj[u].push_back({v, edge_cnt});
        if (!is_directed) {
            adj[v].push_back({u, edge_cnt});
        }
        edge_defs.push_back({u, v});
        out_deg[u]++;
        in_deg[v]++;
        edge_cnt++;
    }

    int find_start_node(bool cycle) {
        int start = -1, end = -1;
        int s_nodes = 0, e_nodes = 0;

        for (int i = 0; i < n; i++) {
            if (is_directed) {
                if (out_deg[i] - in_deg[i] == 1) { s_nodes++; start = i; }
                else if (in_deg[i] - out_deg[i] == 1) { e_nodes++; end = i; }
                else if (in_deg[i] != out_deg[i]) return -1;
            } else {
                if ((out_deg[i] + in_deg[i]) % 2 != 0) {
                    if (s_nodes == 0) start = i;
                    s_nodes++;
                }
            }
        }

        if (cycle) return (s_nodes == 0) ? 0 : -1;
        if (s_nodes == 0) return 0;
        if (s_nodes == 2) return start;
        return -1;
    }

    Result get_eulerian_trail(bool cycle) {
        int s = find_start_node(cycle);
        if (s == -1) return {false, {}, {}};

        std::vector<int> trail_nodes;
        std::vector<PathEdge> trail_edges;
        std::vector<int> ptr(n, 0);
        std::vector<bool> used(edge_cnt, false);
        
        // {現在の頂点, 直前に通った辺のID}
        std::stack<std::pair<int, int>> st;
        st.push({s, -1});

        while (!st.empty()) {
            int v = st.top().first;
            bool found = false;
            while (ptr[v] < (int)adj[v].size()) {
                auto& e = adj[v][ptr[v]++];
                if (!used[e.eid]) {
                    used[e.eid] = true;
                    st.push({e.to, e.eid});
                    found = true;
                    break;
                }
            }
            if (!found) {
                if (st.top().second != -1) {
                    int eid = st.top().second;
                    int to = st.top().first;
                    st.pop();
                    int from = st.top().first;
                    trail_edges.push_back({from, to, eid});
                } else {
                    trail_nodes.push_back(v);
                    st.pop();
                }
            }
        }

        if ((int)trail_edges.size() != edge_cnt) return {false, {}, {}};

        std::reverse(trail_nodes.begin(), trail_nodes.end());
        std::reverse(trail_edges.begin(), trail_edges.end());
        return {true, trail_nodes, trail_edges};
    }
};