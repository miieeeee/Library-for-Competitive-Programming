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


using ull = unsigned long long;
template< ull mod >
class RollingHash{
    vector<ull> power,hash;
    inline ull mul(ull a, ull b) const {
        ull  x = (ull ) a * b;
        ull xh = (ull) (x >> 32), xl = (ull) x, d, m;
        // asm("divl %4; \n\t" : "=a" (d), "=d" (m) : "d" (xh), "a" (xl), "r" (mod));
        m = x%mod;
        return m;
    }
    public:
    RollingHash(string s, ull base){
        int sz = s.size();
        power.resize(sz+1,1);
        hash.resize(sz+1,0);
        rep(i,sz){
            power[i+1] = mul(power[i],base);
            hash[i+1] = mul(hash[i],base) + s[i];
            if(hash[i+1] >= mod) hash[i+1] -= mod; 
        }
    }
    ull get(int l,int r){
        ull ret = hash[r] + mod - mul(hash[l],power[r-l]);
        if(ret >= mod) ret -= mod;
        return ret;
    }
};

using RH1000000007 = RollingHash<(ull)1000000007>;
int main(){
    string s;
    cin >> s;
    RH1000000007 rh(s,10007);
    if(rh.get(0,s.size()) == RH1000000007("aaa",10007).get(0,3)) cout << "aaa" << endl;
    if(rh.get(1,s.size()-1) == RH1000000007("aab",10007).get(0,3)) cout << "aab" << endl;
}