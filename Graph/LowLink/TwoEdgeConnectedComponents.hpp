#include "LowLink.hpp"

struct TwoEdgeConnectedComponents: LowLink{
    vector<int> components;
    vector<vector<int>> groups;
    TwoEdgeConnectedComponents(vector<vector<int>> &g): LowLink(g){}

    int operator[](const int &k){
        return components[k];
    }

    void dfs(int idx, int par, int &k) {
        if(~par && this->order[par] >= this->low[idx]){
          components[idx] = components[par];
          groups[components[par]].push_back(idx);
        }
        else{
          components[idx] = k++;
          groups.push_back({idx});
        }
        for(auto &to : this->G[idx]) {
            if(components[to] == -1) dfs(to, idx, k);
        }
    }

    /// @brief 橋（その辺を削除すると連結性がなくなるような辺）を切る
    /// @param t 分解されたそれぞれの連結成分を一つの頂点として、橋でそれらをむすんだグラフを格納
    void build(vector<vector<int>> &t) {
        LowLink::build();
        components.assign(this->G.size(), -1);
        int k = 0;
        for(int i = 0; i < components.size(); i++) {
            if(components[i] == -1) dfs(i, -1, k);
        }
        t.resize(k);
        for(auto &e : this->bridge) {
        int x = components[e.first], y = components[e.second];
        t[x].push_back(y);
        t[y].push_back(x);
        }
    }
};