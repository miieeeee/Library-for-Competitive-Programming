#pragma once

#include <vector>
#include <cassert>

/// @brief データは外で持つ. 作用の集約だけする
/// @tparam F 
/// @tparam composition(f, g): f(g) 
/// @tparam id: f(id) = id(f) = f 
template<typename F, auto composition, auto id>
struct DualSegtree {
    int n, siz, log;
    std::vector<F> lazy;

    DualSegtree(int n) : n(n) {
        log = 0; while ((1 << log) < n) log++;
        siz = 1 << log;
        lazy.assign(2 * siz, id());
    }

    // 区間作用
    void apply(int l, int r, F f) {
        assert(l < r);
        l += siz; r += siz;
        propagate(l); propagate(r-1);
        while (l < r) {
            if (l & 1) lazy[l] = composition(f, lazy[l]), l++;
            if (r & 1) --r, lazy[r] = composition(f, lazy[r]);
            l >>= 1; r >>= 1;
        }
    }

    // 一点取得
    F get(int idx) {
        idx += siz;
        propagate(idx);
        return lazy[idx];
    }

private:
    void push(int k) {
        lazy[2 * k] = composition(lazy[k], lazy[2 * k]);
        lazy[2 * k + 1] = composition(lazy[k], lazy[2 * k + 1]);
        lazy[k] = id();
    }

    void propagate(int k) {
        for(int i=log; i>0; i--) push(k >> i);
    }
};