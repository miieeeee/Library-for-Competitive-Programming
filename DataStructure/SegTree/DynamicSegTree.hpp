#pragma once

#include "Concept/Algebra.hpp"
#include <algorithm>
#include <cassert>


/// @brief 疎な列に対するセグ木, 永続化も簡単にできる
/// @tparam MX 
/// @tparam SIZE 
template<my_concept::Monoid MX, int SIZE>
struct DynamicSegTree {
    using X = typename MX::value_type;
    struct Node {
        long long idx;
        Node* lc, * rc;
        X prod, x;
    };

private:
    const long long L0, R0;
    Node* pool;
    int pid;

public:
    DynamicSegTree(long long L0, long long R0) : L0(L0), R0(R0), pid(0) {
        pool = new Node[SIZE];
    }

    /// @brief 新しいセグ木を作成する際に呼ぶ. ここで得たrootを使いまわすイメージ
    /// @return 
    Node* new_root() { return nullptr; }

    Node* new_node(long long idx, const X x) {
        pool[pid].idx = idx;
        pool[pid].lc = pool[pid].rc = nullptr;
        pool[pid].x = pool[pid].prod = x;

        return &(pool[pid++]);
    }

    X prod(Node* root, long long l, long long r) {
        assert(L0 <= l && l <= r && r <= R0);
        X x = MX::id();
        prod_rec(root, L0, R0, l, r, x);
        return x;
    }

    X all_prod(Node* root) { return prod(root, L0, R0); }

    /// @brief set して更新された root を返す.(永続化してない場合は与えたrootをそのまま返り値で更新)
    /// @param root 
    /// @param idx 
    /// @param x 
    /// @return 
    Node* set(Node* root, long long idx, const X& x) {
        assert(L0 <= idx && idx < R0);
        return set_rec(root, L0, R0, idx, x);
    }

private:
    void update(Node *v) {
        v->prod = v->x;
        if (v->lc) v->prod = MX::op(v->lc->prod, v->prod);
        if (v->rc) v->prod = MX::op(v->prod, v->rc->prod);
    }

    // 永続化が必要な場合
    // np copy_node(np c) {
    //     if(!c) return c;
    //     pool[pid] = *c;
    //     return &(pool[pid++]);
    // }

    Node* set_rec(Node* v, long long l, long long r, long long idx, X x) {
        if (!v) {
            v = new_node(idx, x);
            return v;
        }
        // v = copy_node(v);
        if(v->idx == idx) {
            v->x = x;
            update(v);
            return v;
        }

        long long m = (l+r)/2;
        if (idx < m) {
            if (v->idx < idx) std::swap(v->idx, idx), std::swap(v->x, x);
            v->lc = set_rec(v->lc, l, m, idx, x);
        }
        else {
            if (v->idx > idx) std::swap(v->idx, idx), std::swap(v->x, x);
            v->rc = set_rec(v->rc, m, r, idx, x);
        }

        update(v);
        return v;
    }

    void prod_rec(Node *v, long long l, long long r, long long ql, long long qr, X &x) {
        ql = std::max(ql, l);
        qr = std::min(qr, r);

        if (ql >= qr || !v) return;
        if (l == ql && r == qr) {
            x = MX::op(x, v->prod);
            return;
        }

        long long m = (l+r)/2;
        prod_rec(v->lc, l, m, ql, qr, x);
        if (v->idx >= ql && v->idx < qr) x = MX::op(x, v->x);
        prod_rec(v->rc, m, r, ql, qr, x);
    }
};
// cf. https://github.com/yosupo06/library-checker-problems/blob/master/data_structure/point_set_range_frequency/sol/correct.cpp