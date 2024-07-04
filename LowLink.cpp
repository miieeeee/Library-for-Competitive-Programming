#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
using ll = long long;
using P = pair<int,int>;
using vi = vector<int>;
using vll = vector<ll>;
using vvi = vector<vi>;
using vvll = vector<vll>;
using mint = modint1000000007;
#define rep(i, n) for(int i = 0; i < (int)(n); i++)
#define FOR(i, a, b) for(ll i = a; i < (ll)(b); i++)
#define all(a) (a).begin(),(a).end()
constexpr int INF = 1001001001;
constexpr ll LINF = 1001001001001001001ll;
constexpr int DX[] = {1, 0, -1, 0};
constexpr int DY[] = {0, 1, 0, -1};

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
        used.resize(g.size(),0);
        order.resize(g.size(),0);
        low.resize(g.size(),0);
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
        for(int nv : G[v]){
            if(nv == pv) continue;
            if(used[nv]){
                low[v] = min(low[v],order[nv]);
            }
            else{
                son_count++;
                dfs(nv,v,k);
                low[v] = min(low[v],low[nv]);
                if(pv != -1 && order[v] <= low[nv]){
                    is_art = true;
                }
                if(order[v] < low[nv]){
                    bridge.emplace_back(min(v,nv),max(v,nv));
                }
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
int main(){
    
}