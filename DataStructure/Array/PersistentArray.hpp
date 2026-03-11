#pragma once

#include <vector>

template <typename T, int LOG>
struct PersistentArray {
    struct Node {
        T val;
        Node* ch[1<<LOG] = {};
    };
    using np = Node*;

public:
    np root;

    PersistentArray() : root(nullptr) {}

    T get(np t, int p) {
        assert(t);
        if(p == 0) {
            return t->val;
        }
        return get(t->ch[p & ((1<<LOG)-1)], p>>LOG);
    }

    T get(int p) {
        return get(root, p);
    }

    np set(np t, int p, T val) {
        np res = new Node();

        if(t) {
            std::memcpy(res->ch, t->ch, sizeof(t->ch));
            res->val = t->val;
        }
        if(p == 0) {
            res->val = val;
        }
        else {
            res->ch[p & ((1<<LOG)-1)] = set(res->ch[p & ((1<<LOG)-1)], p>>LOG, val);
        }
        return res;
    }

    void destructive_set(np &t, int p, T val) {
        if(!t) t = new Node();
        if(p == 0) {
            t->val = val;
        }
        else {
            destructive_set(t->ch[p & ((1<<LOG)-1)], p>>LOG, val);
        }
    }
};