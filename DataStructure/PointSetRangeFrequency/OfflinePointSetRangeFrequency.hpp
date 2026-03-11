#pragma onece
#include "DataStructure/FenwickTree/FenwickTree.hpp"
#include "DataStructure/HashMap/HashMap.hpp"

<template typename T>
struct PointSetRangeFrequency {
    vector<T> _a;
    vector<pair<int, pair<int, T>>> updates;
    vector<pair<pair<int, int>, pair<int, T>>> qs;
    int sz;
    PointSetRangeFrequency(int n, int q, vector<T> a) : _a(a), mp(n+q){

    }   

    void set(int t, int p, T x) {
       updates.push_back({t, {p, x}}); 
    }

    void query(int t, int l, int r, T x) {
        qs.push_back({{l, r}, {t, x}});
    }

    void solve() {
        HashMap<T> mp(n+q);
        vector<int> comp;
        for(auto x : a) {
            T val = mp.get(x, -1);
            if(val == -1) {
                mp[x] = comp.size();
                comp.push_back(x);
            }
        }
        for(auto [_, px] : updates) {
            T x = px.first;
            T val = mp.get(x, -1);
            if(val == -1) {
                mp[x] = comp.size();
                comp.push_back(x);
            }
        }

        vector<vector<pair<int, pair<pair<int, int>, T>>>> dat(comp.size());
        for(auto x : mp[x]) {
            
        }
    }
};