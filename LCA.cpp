#include<bits/stdc++.h>
using namespace std;

struct LCA{
    int n;
    int MAX_LOG_V;
    vector<vector<int>> par;
    vector<int> depth;
    vector<vector<int>> g;
    LCA(int n):n(n){
        int power = 1;
        MAX_LOG_V = 1;
        while(power < n){
            power *= 2;
            MAX_LOG_V++;
        }
        g.resize(n);
        par.resize(n, vector<int>(MAX_LOG_V));
        depth.resize(n);
    }
    LCA(vector<vector<int>> g):g(g){
        n = g.size();
        int power = 1;
        MAX_LOG_V = 1;
        while(power < n){
            power *= 2;
            MAX_LOG_V++;
        }
        par.resize(n, vector<int>(MAX_LOG_V));
        depth.resize(n);
    }
    void build(int root){
        dfs(root, -1, 0);
        for(int i=1; i < MAX_LOG_V; i++){
            for(int v=0; v < n; v++){
                if(par[v][i-1] == -1) par[v][i] = -1;
                else par[v][i] = par[par[v][i-1]][i-1];
            }
        }
    }
    int get(int u, int v){
        if(depth[u] > depth[v]) swap(u,v);
        for(int i=0; i<MAX_LOG_V; i++){
            if((depth[v]-depth[u])>>i & 1){
                v = par[v][i];
            }
        }
        if(u == v) return u;
        for(int i=MAX_LOG_V-1; i>=0; i--){
            if(par[u][i] != par[v][i]){
                u = par[u][i];
                v = par[v][i];
            }
        }
        return par[u][0];
    }
    private : 
    void dfs(int v, int pv, int k){
        depth[v] = k;
        par[v][0] = pv;
        for(int nv : g[v]){
            if(nv != pv) dfs(nv, v, k+1);
        }
    }
};
int main(){
    int n, q;
    cin >> n >> q;
    vector<vector<int>> g(n);
    for(int i=0;i<n-1;i++){
        int p;
        cin >> p;
        g[i+1].push_back(p);
        g[p].push_back(i+1);
    }
    LCA lca(g);
    lca.build(0);
    while(q--){
        int u,v;
        cin >> u >> v;
        cout << lca.get(u, v) << endl;
    }
}