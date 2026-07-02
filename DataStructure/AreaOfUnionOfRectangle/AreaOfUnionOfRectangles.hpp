#pragma once

#include <vector>
#include <queue>
#include <functional>
#include <unordered_map>
#include "atcoder/lazysegtree.hpp"

/// @brief 長方形領域の和の面積. add: O(1). get: O(NlogN)
struct AreaOfUnionOfRectangle{
    struct Rectangle{
        long long l, d, r, u;
    };
    std::vector<Rectangle> rects;

    /// @brief 長方形領域を一つ追加する
    /// @param l 左端のx座標
    /// @param d 下端のy座標
    /// @param r 右端のx座標
    /// @param u 上橋のy座標
    void add(long long l, long long d, long long r, long long u){
        rects.push_back(Rectangle{l, d, r, u});
    }

    /// @brief addで追加した領域の和集合の面積を返す
    /// @return 面積(long long)
    long long get(){
        if(rects.size() == 0) return 0;
        using P = std::pair<std::pair<long long, int>, std::pair<long long, long long>>;
        std::priority_queue<P, std::vector<P>, std::greater<P>> que;
        std::vector<long long> compy;
        std::vector<long long> compx;
        for(auto rect : rects){
            compy.push_back(rect.d);
            compy.push_back(rect.u);
            compx.push_back(rect.l);
            compx.push_back(rect.r);
            que.push({{rect.l, 1}, {rect.d, rect.u}});
            que.push({{rect.r, -1}, {rect.d, rect.u}});
        }

        std::sort(compx.begin(), compx.end());
        std::sort(compy.begin(), compy.end());
        compx.erase(unique(compx.begin(), compx.end()), compx.end());
        compy.erase(unique(compy.begin(), compy.end()), compy.end());
        
        std::unordered_map<long long, int> mpx, mpy;
        for(int i=0; i<compx.size(); i++){
            mpx[compx[i]] = i;
        }
        for(int i=0; i<compy.size(); i++){
            mpy[compy[i]] = i;
        }
        compx.push_back(compx.back()+1);
        compy.push_back(compy.back()+1);
        atcoder::lazy_segtree<S, op, e, int, mapping, composition, id> seg(compy.size());
        for(int i=0; i<compy.size()-1; i++) seg.set(i, S{0, compy[i+1] - compy[i]});
        long long ans = (compx.back() - compx.front())*(compy.back() - compy.front());
        while(!que.empty()){
            long long x = que.top().first.first;
            while(!que.empty() && que.top().first.first == x){
                auto [p, q] = que.top();
                que.pop();
                seg.apply(mpy[q.first], mpy[q.second], p.second);
            }
            S s = seg.all_prod();
            if(s.mi == 0){
                ans -= s.num*(compx[mpx[x]+1] -x);
            }
        }
        return ans;
    }

    private:
    
    struct S{
        long long mi, num;
    };
    static S op(S a, S b){
        if(a.mi < b.mi) return a;
        if(a.mi > b.mi) return b;
        return S{a.mi, a.num + b.num};
    }
    static S e(){
        return S{1<<30, 0};
    }
    static S mapping(int f, S x){
        x.mi += f;
        return x;
    }
    static int composition(int f, int g){
        return f+g;
    }
    static int id(){
        return 0;
    }
};