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

struct MergeSortTree{
    vector<vector<int>> segtree;
    int N;
    MergeSortTree(vector<int> vec){
        N = 1;
        while(N < vec.size()) N <<= 1;
        segtree.resize(2*N);
        for(int i=0;i < vec.size();i++) segtree[N+i-1] = {vec[i]};
        build();
    }
    void build(){
        for(int i=N-2;i>=0;i--){
            vector<int> l = segtree[i*2+1],r = segtree[i*2+2];
            merge(l.begin(),l.end(),r.begin(),r.end(),back_inserter(segtree[i]));   
        }
    }
    int kth(int l,int r,int k){
        int lo = 0,up = INF;
        while(up - lo > 1){
            int mid = (lo+up)/2;
            if(lower(l,r,mid) >= k) up = mid;
            else lo = mid;
        }
        return up;
    }
    int lower(int l,int r,int x,int idx=0,int i=0,int j=0){
        if(idx == 0) j = N;
        if(l >= j || r <= i) return 0;
        if(l <= i && r >= j) return upper_bound(segtree[idx].begin(),segtree[idx].end(),x) - segtree[idx].begin();
        return lower(l,r,x,2*idx+1,i,(i+j)/2) + lower(l,r,x,2*idx+2,(i+j)/2,j);
    }
};
int main(){
    int n,m;
    cin >> n >> m;
    vi a(n);
    rep(i,n) cin >> a[i];
    MergeSortTree seg(a);
    while(m--){
        int i,j,k;
        cin >> i >> j >> k;
        i--;
        cout << seg.kth(i,j,k) << endl;
    }
}