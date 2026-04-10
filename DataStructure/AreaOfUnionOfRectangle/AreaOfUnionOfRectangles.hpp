#pragma once


struct AreaOfUnionOfRectangle{
    struct Rectangle{
        long long l, d, r, u;
    };
    vector<Rectangle> rects;

    void add(long long l, long long d, long long r, long long u){
        rects.push_back(Rectangle{l, d, r, u});
    }

    long long get(){
        if(rects.size() == 0) return 0;
        using P = pair<pair<long long, int>, pair<long long, long long>>;
        priority_queue<P, vector<P>, greater<P>> que;
        vector<long long> compy;
        vector<long long> compx;
        for(auto rect : rects){
            compy.push_back(rect.d);
            compy.push_back(rect.u);
            compx.push_back(rect.l);
            compx.push_back(rect.r);
            que.push({{rect.l, 1}, {rect.d, rect.u}});
            que.push({{rect.r, -1}, {rect.d, rect.u}});
        }

        sort(compx.begin(), compx.end());
        sort(compy.begin(), compy.end());
        compx.erase(unique(compx.begin(), compx.end()), compx.end());
        compy.erase(unique(compy.begin(), compy.end()), compy.end());
        
        unordered_map<long long, int> mpx, mpy;
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