#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
using ll = long long;
using P = pair<ll,ll>;
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

bool is_rect(pair<ll,P> v1, pair<ll,P> v2){
    return (v1.first*v2.first + v1.second.first*v2.second.first + v1.second.second*v2.second.second == 0);
}
pair<ll,P> last_one(pair<ll,P> m, pair<ll,P> v1, pair<ll,P> v2){
    return make_pair(v1.first+v2.first-m.first, make_pair(v1.second.first+v2.second.first-m.second.first, v1.second.second+v2.second.second-m.second.second));
}
int main(){
    while(true){
    int n;
    cin >> n;
    if(n == 0) break;
    set<pair<ll,P>> st;
    vector<pair<ll,P>> vec(n);
    rep(i,n){
        int x,y,z;
        scanf("%d %d %d", &x, &y, &z);
        st.insert(make_pair(x,make_pair(y,z)));
        vec[i] = make_pair(x,make_pair(y,z));
    }
    long ans = 0;
    rep(i,n){
        rep(j,i){
            rep(k,j){
                pair<ll,P> v1 = make_pair(vec[i].first-vec[j].first,make_pair(vec[i].second.first-vec[j].second.first, vec[i].second.second - vec[j].second.second));
                pair<ll,P> v2 = make_pair(vec[i].first-vec[k].first,make_pair(vec[i].second.first-vec[k].second.first, vec[i].second.second - vec[k].second.second));
                // i
                if(is_rect(v1, v2)){
                    if(st.count(last_one(vec[i], vec[j], vec[k]))){
                        ans++;
                    }
                    continue;
                }
                v1 = make_pair(vec[i].first-vec[j].first,make_pair(vec[i].second.first-vec[j].second.first, vec[i].second.second - vec[j].second.second));
                v2 = make_pair(vec[k].first-vec[j].first,make_pair(vec[k].second.first-vec[j].second.first, vec[k].second.second - vec[j].second.second));
                // j
                if(is_rect(v1,v2)){
                    if(st.count(last_one(vec[j], vec[i], vec[k]))){
                        ans++;
                    }
                    continue;
                }
                v1 = make_pair(vec[i].first-vec[k].first,make_pair(vec[i].second.first-vec[k].second.first, vec[i].second.second - vec[k].second.second));
                v2 = make_pair(vec[k].first-vec[j].first,make_pair(vec[k].second.first-vec[j].second.first, vec[k].second.second - vec[j].second.second));
                // k
                if(is_rect(v1,v2)){
                    if(st.count(last_one(vec[k], vec[i], vec[j]))){
                        ans++;
                    }         
                    continue;           
                }
            }
        }
    }
    cout << ans/4 << endl;
    }
}