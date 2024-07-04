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

struct PartiallyPersistentUnionFind{
    // parは自分が根の時部分木のサイズを、そうでないとき親のノードを持つ
    vector<int> par;
    vector<int> ts;
    vector<vector<pair<int,int>>> size;
    int n;
    int now = 0;
    PartiallyPersistentUnionFind(int _n):n(_n){
        par.resize(n, 1);
        ts.resize(n, -1);
        size.resize(n, {make_pair(0, 1)});
    }

    int root(int v, int t){
        if(ts[v] > t) return v;
        return root(par[v], t);
    }

    int size(int v, int t){
        int v = root(v, t);
        int idx = upper_bound(size[v].begin(), size[v].end(), make_pair(t, -1)) - size[v].begin() - 1;
        return size[v][idx].second;
    }

    int unite(int u, int v){
        now++;
        int u = root(u, now), v = root(v, now);
        if(u == v) return now;
        if(par[u] < par[v]) swap(u, v);
        par[u] += par[v];
        par[v] = u;
        ts[v] = now;
        size[u].push_back(make_pair(now, par[u]));
        return now;
    }


};
int main(){
    
}