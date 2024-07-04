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

struct RollbackUnionFind{
    vector<int> par;
    stack<P> history;
    int inner_snap;
    RollbackUnionFind(int sz) : inner_snap(0) {par.assign(sz,-1);}

    bool unite(int x,int y){
        x = find(x),y = find(y);
        history.emplace(x,par[x]);
        history.emplace(y,par[y]);
        if(x==y) return false;
        if(par[x] > par[y]) swap(x,y);
        par[x] += par[y];
        par[y] = x;
    }

    int find(int k){
        if(par[k] < 0) return k;
        return find(par[k]);
    }

    int issame(int x,int y){
        return find(x) == find(y);
    }

    int size(int k){
        return (-par[find(k)]);
    }

    void undo(){
        par[history.top().first] = history.top().second;
        history.pop();
        par[history.top().first] = history.top().second;
        history.pop();
    }

    void snapshot(){
        inner_snap = int(history.size() >> 1);
    }

    int get_state(){
        return int(history.size() >> 1);
    }

    void rollback(int state = -1){
        if(state == -1) state = inner_snap;
        state <<= 1;
        assert(state <= (int)history.size());
        while(state < (int)history.size()) undo();
    }

};

int main(){
    
}