#include <bits/stdc++.h>
using namespace std;

struct LowLink{
    int sz;
    vector<vector<int>> G;
    vector<pair<int,int>> bridge;
    vector<int> articulation_points;
    vector<int> order,low;
    vector<bool> used;
    
    LowLink(int n) : sz(n){
        G.resize(sz);
        used.resize(sz,false);
        order.resize(sz);
        low.resize(sz);
    }
    LowLink(vector<vector<int>> &g){
        G = g;
        sz = G.size();
        used.resize(g.size(), 0);
        order.resize(g.size(), 0);
        low.resize(g.size(), 0);
        build();
    }
    void add_edge(int u,int v){
        G[u].push_back(v);
        G[v].push_back(u);
    }
    void build(){
        int k = 0;
        for(int i=0;i<sz;i++){
            if(!used[i]) k = dfs(i,-1,k);
        }
    }

    int dfs(int v,int pv,int k){
        used[v] = true;
        low[v] = order[v] = k++;
        int son_count = 0;
        bool is_art = false;
        int pvcnt = 0;
        for(int nv : G[v]){
            if(nv == pv && pvcnt == 0){
                pvcnt++;
                continue;
            }
            if(!used[nv]){
                son_count++;
                k = dfs(nv , v, k);
                low[v] = min(low[v],low[nv]);
                if(~pv && order[v] <= low[nv]){
                    is_art = true;
                }
                if(order[v] < low[nv]){
                    bridge.emplace_back(min(v,nv),max(v,nv));
                }
            }
            else{
                low[v] = min(low[v],order[nv]);
            }
        }
        if(pv == -1 && son_count >= 2){
            is_art = true;
        }
        if(is_art){
            articulation_points.push_back(v);
        }
        return k;
    }
};