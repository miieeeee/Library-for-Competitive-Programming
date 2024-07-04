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

template <typename G>
struct EulerTour{
    vector<int> in,out;
    vector<int> tree;
    EulerTour(G &g,int root) : in(g.size(),-1),out(g.size()){
        build(g,root);
    } 
    void build(G &g,int root){
        dfs(g,root);
    }
    void dfs(G &g,int v,int pv = -1){
        in[v] = tree.size();
        tree.push_back(v);
        for(auto nv : g[v]){
            if(nv == pv) continue;
            dfs(g,nv,v);
            tree.push_back(v);
        }
        out[v] = tree.size()-1;
    }
    pair<int,int> idx(int v){
        return make_pair(in[v],out[v]);
    }
};
int main(){
    int n;
    cin >> n;
    vvi g(n);
    rep(i,n-1){
        int a,b;
        cin >> a >> b;
        a--;b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    EulerTour euler(g,0);
    rep(i,euler.tree.size()) cout << euler.tree[i] << " ";
    cout << endl;
    rep(i,n) cout << euler.idx(i).first << " " << euler.idx(i).second << endl;
}