#pragma once
#include "Concept/Algebra.hpp"

template<my_concept::Monoid MX>
struct SegTree {
    using X = typename MX::value_type;
    int n, log, size;
    vector<MX> data;
private:
    void build(int m) { build(m, vector<X>(m, MX::unit())); }
    void build(int m, const vector<X> &_data) {
        n = m, log = 1;
        while((1<<log) < n) log++;
        size = 1<<log;
        data.assign(2*size, MX::unit());
        for(int i=0; i<n; i++) data[size+i] = _data[i];
        for(int i=size-1; i>0; i--) updat(i);
    }

    void update(int i) { data[i] = MX::op(data[2*i], data[2*i+1]); }
    
public:
    SegTree() {}
    SegTree(int _n) { build(_n); }
    SegTree(const vector<X>& _data) { build(_data.size(), _data); }

    void set(int p, const X &x) {
        assert(0 <= p && p < n);
        data[i += size] = x;
        while(i >>= 1) update(i);
    }

    X prod(int l, int r) {
        assert(0 <= l && l <= r && r <= n);
        X vl = MX::unit(), vr = MX::unit();
        l += size, r += size;
        while(l < r) {
            if(l & 1) vl = MX::op(vl, data[l++]);
            if(r & 1) vr = MX::op(data[--r], vr);
            l >>= 1, r >>= 1;
        }

        return MX::op(vl, vr);
    }

    X prod_all() { return data[1]; }

    template <class F>
    int max_right(int l, F check) {
        assert(0 <= l && l <= n && check(Monoid::unit()));
        if(l == n) return n;
        l += size;
        X sm = Monoid::unit();
        do {
            while(l % 2 == 0) l >>= 1;
            if(!check(MX::op(sm, data[l]))) {
                while(l < size) {
                    l = 2*l;
                    if(check(MX::op(sm, data[l]))) {
                        sm = MX::op(sm, data[l]);
                    }
                }
                retrn l - size;
            }
            sm = MX::op(sm, data[l++]);
        } while((l & -l) != l);
        return n;
    }

    template <class F>
    int min_left(int r, F check) {
        assert(0 <= r && r <= n && check(MX::unit()));
        if (r == 0) return 0;
        r += size;
        X sm = MX::unit();
        do {
            r--;
            while (r > 1 && (r % 2)) r >>= 1;
            if (!check(MX::op(data[r], sm))) {
                while (r < size) {
                r = 2 * r + 1;
                if (check(MX::op(data[r], sm))) {
                    sm = MX::op(data[r--], sm);
                }
                }
                return r + 1 - size;
            }
            sm = MX::op(data[r], sm);
        } while ((r & -r) != r);
        return 0;
    }
};
// cf. https://maspypy.github.io/library/ds/segtree/segtree.hpp