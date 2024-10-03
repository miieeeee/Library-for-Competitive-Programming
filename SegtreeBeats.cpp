#include<bits/stdc++.h>
using namespace std;
using ll = long long;
template <class S,
          S (*op)(S, S),
          S (*e)(),
          class F,
          S (*mapping)(F, S),
          F (*composition)(F, F),
          F (*id)()>
struct SegtreeBeats {
  public:
    SegtreeBeats() : SegtreeBeats(0) {}
    explicit SegtreeBeats(int n) : SegtreeBeats(std::vector<S>(n, e())) {}
    explicit SegtreeBeats(const std::vector<S>& v) : _n(int(v.size())) {
        log=0;
        while((1<<log)<_n) log++;
        size = 1 << log;
        d = std::vector<S>(2 * size, e());
        lz = std::vector<F>(size, id());
        for (int i = 0; i < _n; i++) d[size + i] = v[i];
        for (int i = size - 1; i >= 1; i--) {
            update(i);
        }
    }

    void set(int p, S x) {
        assert(0 <= p && p < _n);
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        d[p] = x;
        for (int i = 1; i <= log; i++) update(p >> i);
    }

    S get(int p) {
        assert(0 <= p && p < _n);
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        return d[p];
    }

    S prod(int l, int r) {
        assert(0 <= l && l <= r && r <= _n);
        if (l == r) return e();

        l += size;
        r += size;

        for (int i = log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push(r >> i);
        }

        S sml = e(), smr = e();
        while (l < r) {
            if (l & 1) sml = op(sml, d[l++]);
            if (r & 1) smr = op(d[--r], smr);
            l >>= 1;
            r >>= 1;
        }

        return op(sml, smr);
    }

    S all_prod() { return d[1]; }

    void apply(int p, F f) {
        assert(0 <= p && p < _n);
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        d[p] = mapping(f, d[p]);
        for (int i = 1; i <= log; i++) update(p >> i);
    }
    void apply(int l, int r, F f) {
        assert(0 <= l && l <= r && r <= _n);
        if (l == r) return;

        l += size;
        r += size;

        for (int i = log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }

        {
            int l2 = l, r2 = r;
            while (l < r) {
                if (l & 1) all_apply(l++, f);
                if (r & 1) all_apply(--r, f);
                l >>= 1;
                r >>= 1;
            }
            l = l2;
            r = r2;
        }

        for (int i = 1; i <= log; i++) {
            if (((l >> i) << i) != l) update(l >> i);
            if (((r >> i) << i) != r) update((r - 1) >> i);
        }
    }

    template <bool (*g)(S)> int max_right(int l) {
        return max_right(l, [](S x) { return g(x); });
    }
    template <class G> int max_right(int l, G g) {
        assert(0 <= l && l <= _n);
        assert(g(e()));
        if (l == _n) return _n;
        l += size;
        for (int i = log; i >= 1; i--) push(l >> i);
        S sm = e();
        do {
            while (l % 2 == 0) l >>= 1;
            if (!g(op(sm, d[l]))) {
                while (l < size) {
                    push(l);
                    l = (2 * l);
                    if (g(op(sm, d[l]))) {
                        sm = op(sm, d[l]);
                        l++;
                    }
                }
                return l - size;
            }
            sm = op(sm, d[l]);
            l++;
        } while ((l & -l) != l);
        return _n;
    }

    template <bool (*g)(S)> int min_left(int r) {
        return min_left(r, [](S x) { return g(x); });
    }
    template <class G> int min_left(int r, G g) {
        assert(0 <= r && r <= _n);
        assert(g(e()));
        if (r == 0) return 0;
        r += size;
        for (int i = log; i >= 1; i--) push((r - 1) >> i);
        S sm = e();
        do {
            r--;
            while (r > 1 && (r % 2)) r >>= 1;
            if (!g(op(d[r], sm))) {
                while (r < size) {
                    push(r);
                    r = (2 * r + 1);
                    if (g(op(d[r], sm))) {
                        sm = op(d[r], sm);
                        r--;
                    }
                }
                return r + 1 - size;
            }
            sm = op(d[r], sm);
        } while ((r & -r) != r);
        return 0;
    }

  private:
    int _n, size, log;
    std::vector<S> d;
    std::vector<F> lz;

    void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
    void all_apply(int k, F f) {
        d[k] = mapping(f, d[k]);
        if (k < size){
            lz[k] = composition(f, lz[k]);
            if(d[k].fail) push(k), update(k);
        }
    }
    void push(int k) {
        all_apply(2 * k, lz[k]);
        all_apply(2 * k + 1, lz[k]);
        lz[k] = id();
    }
};
ll LINF = 1001001001001001001ll;
struct S{
    ll m1,m2,M1,M2,sum;
    int mincnt, maxcnt;
    int len;
    bool fail;
    S():m1(LINF),m2(LINF),M1(-LINF),M2(-LINF),sum(0),mincnt(0),maxcnt(0),len(0),fail(false){}
    S(ll x, int len=1):len(len){
        m1 = M1 = x;
        m2 = LINF;
        M2 = -LINF;
        sum = x*len;
        mincnt = maxcnt = len;
        fail=false;
    }
};

struct F{
    ll lb, ub, add;
    F(ll _chmax=-LINF, ll _chmin=LINF, ll add=0):lb(_chmax),ub(_chmin),add(add){}
};
S op(S a, S b){    
    S ret;
    ret.m1 = min(a.m1, b.m1);
    ret.M1 = max(a.M1, b.M1);
    ret.m2 = (a.m1==b.m1?min(a.m2, b.m2):(a.m1<b.m1?min(a.m2, b.m1):min(a.m1, b.m2)));
    ret.M2 = (a.M1==b.M1?max(a.M2, b.M2):(a.M1<b.M1?max(a.M2, b.M1):max(a.M1, b.M2)));
    ret.len = a.len+b.len;
    ret.mincnt = a.mincnt*(a.m1 == ret.m1)+b.mincnt*(b.m1 == ret.m1);
    ret.maxcnt = a.maxcnt*(a.M1 == ret.M1)+b.maxcnt*(b.M1 == ret.M1);
    ret.sum = a.sum+b.sum;
    return ret;
}
S e(){
    return S();
}
S mapping(F f, S a){
    a.fail=false;
    if(a.len == 0) return e();
    else if(a.m1==a.M1 || f.lb==f.ub || f.lb>=a.M1 || f.ub<=a.m1){
        return S(min(max(a.m1, f.lb), f.ub)+f.add, a.len);
    }
    else if(a.m2 == a.M1){
        a.m1 = a.M2 = max(a.m1, f.lb)+f.add;
        a.m2 = a.M1 = min(a.M1, f.ub)+f.add;
        a.sum = a.m1*a.mincnt+a.M1*a.maxcnt;
        return a;
    }
    else if(f.lb < a.m2 && f.ub > a.M2){
        a.sum -= a.m1*a.mincnt+a.M1*a.maxcnt;
        a.m1 = max(f.lb, a.m1)+f.add;
        a.M1 = min(f.ub, a.M1)+f.add;
        a.m2 += f.add;
        a.M2 += f.add;
        a.sum += a.m1*a.mincnt+a.M1*a.maxcnt+f.add*(a.len-a.mincnt-a.maxcnt);
        return a;
    }
    a.fail = true;
    return a;
}
F composition(F f, F g){
    F ret;
    ret.lb = max(f.lb, min(g.lb+g.add, f.ub))-g.add;
    ret.ub = min(f.ub, max(f.lb, g.ub+g.add))-g.add;
    ret.add = f.add+g.add;
    return ret;
}
F id(){
    return F();
}

int main(){
    int n, q;
    cin >> n >> q;
    SegtreeBeats<S, op, e, F, mapping, composition, id> seg(n);
    for(int i=0; i<n; i++){
        ll a;
        cin >> a;
        seg.set(i, S(a));
    }
    while(q--){
        int t, l, r;
        cin >> t >> l >> r;
        if(t == 3){
            cout << seg.prod(l, r).sum << endl;
        }
        else{
            ll b;
            cin >> b;
            if(t==0) seg.apply(l, r, F(-LINF, b, 0));
            if(t==1) seg.apply(l, r, F(b, LINF, 0));
            if(t==2) seg.apply(l, r, F(-LINF, LINF, b));
        }
    }
}