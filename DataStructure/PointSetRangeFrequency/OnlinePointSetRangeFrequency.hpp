#pragma once
#include "DataStructure/SegTree/DynamicSegTree.hpp"
#include "DataStructure/HashMap/CustomHashMap.hpp"



template <my_concept::Hashable T, int SIZE>
struct OnlinePointSetRangeFrequency
{
    struct Monoid {
        using value_type = int;
        static int op(int a, int b) { return a+b; }
        static int id() { return 0; }
    };
private:
    DynamicSegTree<Monoid, SIZE> seg;
    using np = decltype(seg)::Node*;
    CustomHashMap<T, np> root;
    vector<T> a;
    int n;
public:
    OnlinePointSetRangeFrequency(vector<T> &a) : n(a.size()), seg(0, a.size()), a(a), root(SIZE){
        for(int i=0; i<n; i++) {
            if (!root.get(a[i], nullptr)) {
                root[a[i]] = seg.new_root();
            }
            root[a[i]] = seg.set(root[a[i]], i, 1);
        }
    }

    void set(int idx, T x) {
        assert(idx >= 0 && idx < n);
        root[a[idx]] = seg.set(root[a[idx]], idx, 0);
        if (!root.get(x, nullptr)) {
            root[x] = seg.new_root();
        }
        root[x] = seg.set(root[x], idx, 1);
        a[idx] = x;
    }

    int query(long long l, long long r, T x) {
        assert(l >= 0 && l <= r && r <= n);
        if(!root.get(x, nullptr)) { return 0; }
        return seg.prod(root[x], l, r);
    }
};
