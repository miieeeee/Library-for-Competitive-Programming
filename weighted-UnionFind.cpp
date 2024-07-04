#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using P = pair<int,int>;
using VI = vector<int>;
using Graph = vector<vector<int>>;
#define rep(i, n) for(int i = 0; i < (int)(n); i++)
#define FOR(i, a, b) for(ll i = a; i < (ll)(b); i++)
#define ALL(a) (a).begin(),(a).end()

struct WeightedUnionFind{
    VI par;
    VI rank;
    VI diff_weight;

    WeightedUnionFind(ll sz){
        init(sz);
    }

    void init(ll sz){
        par.resize(sz);
        rank.resize(sz);
        diff_weight.resize(sz);
        FOR(i, 0, sz){
            par[i] = i;
            rank[i] = 0;
            diff_weight[i] = 0;
        }
    }

    int root(ll x) {
        if (par[x] == x) {
            return x;
        }
        else {
            ll r = root(par[x]);
            diff_weight[x] += diff_weight[par[x]];
            return par[x] = r;
        }
    }

    ll weight(ll x) {
        root(x);
        return diff_weight[x];
    }

    bool is_same(ll x, ll y) {
        return root(x) == root(y);
    }

    // weight(y) - weight(x) = w となるように merge する
    bool merge(ll x, ll y, ll w) {
        w += weight(x); w -= weight(y);
        x = root(x); y = root(y);
        if (x == y) return false;
        if (rank[x] < rank[y]) swap(x, y), w = -w;
        if (rank[x] == rank[y]) ++rank[x];
        par[y] = x;
        diff_weight[y] = w;
        return true;
    }

    ll diff(int x, int y) {
        return weight(y) - weight(x);
    }
};