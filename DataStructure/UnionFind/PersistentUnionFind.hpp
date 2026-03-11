#pragma once

#include "DataStructure/Array/PersistentArray.hpp"

struct PersistentUnionFind {
    using PA = PersistentArray<int, 3>;
    using np = PA::np;
    PA par;
    PersistentUnionFind() : par(){
    }

    np build(int n) {
        np res = par.root;
        for(int i=0; i<n; i++) par.destructive_set(res, i, -1);
        return res;
    }


    int leader(np t, int x) {
        int xx = par.get(t, x);
        if(xx < 0) return x;
        return leader(t, xx);
    }

    std::pair<bool, np> merge(np t, int x, int y) {
        x = leader(t, x), y = leader(t, y);
        if(x == y) return {false, t};
        int par_x = par.get(t, x), par_y = par.get(t, y);
        if(par_x > par_y) {
            std::swap(x, y);
            std::swap(par_x, par_y);
        }
        np res = par.set(t, x, par_x + par_y);
        res = par.set(res, y, x);

        return {true, res};
    }

    bool same(np t, int x, int y) { return leader(t, x) == leader(t, y); }
    int size(np t, int x) { return -par.get(t, leader(t, x)); }
};