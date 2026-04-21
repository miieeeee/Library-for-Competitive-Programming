#pragma GCC target("avx2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
#include <atcoder/all> 
using namespace atcoder;

// 数値型
using mint = modint998244353;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
using P = pair<int,int>;
using Pll = pair<ll, ll>;
using Pli = pair<ll, int>;
using Pil = pair<int, ll>;

// vector関連
using vi = vector<int>;
using vvi = vector<vi>;
using vvvi = vector<vvi>;
using vll = vector<ll>;
using vvll = vector<vll>;
using vvvll = vector<vvll>;
template<typename T>
using vc = vector<T>;
template<typename T>
using vvc = vector<vc<T>>;
template<typename T>
using vvvc = vector<vvc<T>>;
template<typename T>
using vvvvc = vector<vvvc<T>>;

// priority_queue
template<typename T>
using pq = priority_queue<T>;
template<typename T>
using pqg = priority_queue<T, vc<T>, greater<T>>;

#define rep(i, n) for(int i = 0; i < (int)(n); i++)
#define FOR(i, a, b) for(int i = a; i < (int)(b); i++)
#define all(a) (a).begin(),(a).end()
#define rall(a) (a).rbegin(),(a).rend()
#define MIN(vec) *min_element(all(vec))
#define MAX(vec) *max_element(all(vec))
#define next_perm(vec) (vec).begin(), (vec).end()
#define UNIQUE(vec) vec.erase(unique(vec.begin(), vec.end()), vec.end())
#define el "\n"
#define Yes cout << "Yes" << el
#define No cout << "No" << el
#define YES cout << "YES" << el
#define NO cout << "NO" << el
#define EPS 1e-8
#define Equal(a, b) (fabs((a)-(b)) < EPS) 
#ifdef ONLINE_JUDGE
#define dbg(x) (void)0
#else
#define dbg(x) cerr << #x << "=" << x << el 
#endif
// 定数
const string abc = "abcdefghijklmnopqrstuvwxyz";
const string ABC = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
constexpr int INF = 1001001001;
constexpr ll LINF = 1001001001001001001ll;
constexpr int DX[] = {1, 0, -1, 0};
constexpr int DY[] = {0, 1, 0, -1};
constexpr int DX8[] = {1, 0, -1, 0, 1, 1, -1, -1};
constexpr int DY8[] = {0, 1, 0, -1, 1, -1, 1, -1};

template<typename T1, typename T2>
ostream &operator<< (ostream &os, pair<T1, T2> p) {
    os << "{" << p.first << "," << p.second << "}";
    return os;
}
template<typename T>
ostream &operator<< (ostream &os, vc<T> &vec) {
    int sz = vec.size();
    rep(i, sz){
        os << vec[i] << (i==sz-1?"":" ");
    }
    return os;
}

ostream &operator<< (ostream &os, mint &a) {
    os << a.val();
    return os;
}

istream &operator>> (istream &is, mint &a) {
    ll x;
    is >> x;
    a = x;
    return is;
}
template<typename T1, typename T2>
istream &operator>> (istream &is, pair<T1, T2> &p) {
    is >> p.first >> p.second;
    return is;
}
template<typename T>
istream &operator>> (istream &is, vc<T> &vec) {
    int sz = vec.size();
    rep(i, sz) { is >> vec[i]; }
    return is;
}
/// @brief aとｂの最大値をaに格納。更新があったかbool値を返す
/// @tparam T1 
/// @tparam T2 
/// @param a 
/// @param b 
/// @return bool
template<typename T1, typename T2>
inline bool chmax(T1 &a, T2 b){
    bool ret = a<b;
    if(ret) a = b;
    return ret;
}

/// @brief aとｂの最小値をaに格納。更新があったかbool値を返す
/// @tparam T1 
/// @tparam T2 
/// @param a 
/// @param b 
/// @return bool
template<typename T1, typename T2>
inline bool chmin(T1 &a, T2 b){
    bool ret = a>b;
    if(ret) {a = b;}
    return ret;
}

inline void YesNo(bool flag){
    if(flag) {Yes;}
    else {No;}
    return;
}

inline void YESNO(bool flag){
    if(flag) {YES;}
    else {NO;}
    return;
}

inline bool outof(ll x, ll xlim){
    return (x<0 || x>=xlim);
}

template<typename T>
inline T sqnorm(T x, T y){
    return x*x+y*y;
}

/// @brief char->int
/// @param c 
/// @return int
inline int ctoi(char c){
    return c-'0';
}

/// @brief xを素因数分解
/// @param x 
/// @return vector<Pli>, 素因数の昇順に {p, cnt}
vector<Pli> prime_fact(ll x){
    vector<Pli> ret;
    for(ll i=2; i*i<=x; i++){
        if(x%i == 0){
            ret.emplace_back(i, 0);
            while(x%i == 0){
                ret.back().second++;
                x /= i;
            }
        }
    }
    if(x != 1) ret.emplace_back(x, 1);
    return ret;
}

/// @brief xの約数列挙
/// @param x 
/// @return vll, 約数の昇順
vll divisor_enum(ll x){
    vector<ll> ret;
    for(ll i=1; i*i<=x; i++){
        if(x%i == 0){
            ret.push_back(x/i);
            ret.push_back(i);
        }
    }
    sort(all(ret));
    UNIQUE(ret);
    return ret;
}

/// @brief 繰り返し二乗法。
/// @tparam T 
/// @param x 
/// @param k 
/// @param op 
/// @param e 
/// @return 
template<typename T>
T pow_t(T x, ll k, T (*op)(T, T), T (*e)()){
    T ret = e();
    while(k){
        if(k&1) ret = op(ret, x);
        x = op(x, x);
        k >>= 1;
    }
    return ret;
}

ll powll(ll x, ll k){
    return pow_t<ll>(x, k, [](ll a, ll b) -> ll{return a*b;}, []() -> ll{return 1;});
}

inline int pop_cnt(ll x) { return __builtin_popcountll(x); }
inline int top_bit(ll x) { return (x==0?-1:63-__builtin_clzll(x));}

void main2();

int main(){
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    main2();
}

#include "Tree/DsuOnTree/DsuOnTree.hpp"

void main2(){
    int n, seed, m, f;
    cin >> n >> seed >> m >> f;
    vi q(m);
    vi d(m);
    rep(i, m-1) cin >> q[i+1];
    cin >> d;
    vi c(n), p(n);
    ll state = seed;
    for(int i=2; i<=n; i++) {
        if(i <= m) {
            p[i-1] = q[i-1]-1;
        }
        else {
            p[i-1] = (state % (i-1));
            state = (state * 1103515245 + 12345) % (1<<31);
        }
    }
    for(int i=1; i<=n; i++) {
        if (i <= m) {
            c[i-1] = d[i-1];
        }
        else {
            c[i-1] = (state % f) + 1;
            state = (state * 1103515245 + 12345) % (1<<31);
        }
    }

    vvi g(n);
    rep(i, n) {
        if(i == 0) continue;
        g[p[i]].push_back(i);
        g[i].push_back(p[i]);
    }

    DsuOnTree<vvi> dot(g, 0);
    vi cnt(n, 0);
    vi cnt2(n+1, 0);
    cnt2[0] = n;
    vc<P> ans(n);
    int ma = 0;
    auto add = [&](int v) -> void {
      cnt2[cnt[c[v]]]--;
      cnt[c[v]]++;
      cnt2[cnt[c[v]]]++;
      chmax(ma, cnt[c[v]]);
    };
    auto del = [&](int v) -> void {
      cnt2[cnt[c[v]]]--;
      if(cnt2[cnt[c[v]]] == 0 && ma == cnt[c[v]]) ma--;
      cnt[c[v]]--;
      cnt2[cnt[c[v]]]++;
    };
    auto query = [&](int v) -> void {
      ans[v] = {ma, cnt2[ma]};
    };
    dot.run(add, del, query);

    mint score = 0;
    rep(i, n) score += mint(ans[i].first^(i+1))*mint(ans[i].second^(i+1));
    cout << score.val() << el;
}
