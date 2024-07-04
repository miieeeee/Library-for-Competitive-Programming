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

struct SCC{
    int N;
    vector<vector<int>> G,rG;
    vector<int> vs;
    vector<bool> used;
    vector<int> cmp;
    vector<vector<int>> groups;
    SCC(int n) : N(n),G(n),rG(n),used(n,false),cmp(n){}
    
    void add_edge(int from,int to){
        assert(0 <= from && from <  N);
        assert(0 <= to && to < N);
        G[from].push_back(to);
        rG[to].push_back(from);
    }

    vector<vector<int>> scc(){
        rep(i,N){
            if(used[i]) continue;
            dfs(i);
        }
        rep(i,N) used[i] = false;
        int k = 0;
        for(int i=N-1;i >= 0;i--){
            if(used[vs[i]]) continue;
            rdfs(vs[i],k++);
        }
        groups.resize(k);
        rep(i,N){
            groups[cmp[i]].push_back(i);
        }
        return groups;
    }

    void dfs(int v){
        used[v] = true;
        for(int nv : G[v]){
            if(used[nv]) continue;
            dfs(nv);
        }
        vs.push_back(v);
    }
    void rdfs(int v,int k){
        used[v] = true;
        cmp[v] = k;
        for(int nv : rG[v]){
            if(used[nv]) continue;
            rdfs(nv,k);
        }
    }

};
int main(){
    int n,m;
    cin >> n >> m;
    SCC g(n);
    rep(i,m){
        int u,v;
        cin >> u >> v;
        u--;v--;
        g.add_edge(u,v);
    }
    vector<vector<int>> scc = g.scc();
    ll ans = 0;
    for(vector<int> vec : scc){
        ans += (ll)vec.size() * (vec.size() - 1)/2;
    }
    cout << ans << endl;
}