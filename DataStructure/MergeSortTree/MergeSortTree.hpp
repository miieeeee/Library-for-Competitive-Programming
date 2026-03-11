#pragma once

#include <vector>

struct MergeSortTree{
    std::vector<std::vector<int>> segtree;
    int N;
    MergeSortTree(std::vector<int> vec){
        N = 1;
        while(N < vec.size()) N <<= 1;
        segtree.resize(2*N);
        for(int i=0;i < vec.size();i++) segtree[N+i-1] = {vec[i]};
        build();
    }

    void build(){
        for(int i=N-2;i>=0;i--){
            std::vector<int> l = segtree[i*2+1],r = segtree[i*2+2];
            merge(l.begin(),l.end(),r.begin(),r.end(),back_inserter(segtree[i]));   
        }
    }

    int kth(int l,int r,int k){
        int lo = 0, up = 1001001001;
        while(up - lo > 1){
            int mid = (lo+up)/2;
            if(lower(l,r,mid) >= k) up = mid;
            else lo = mid;
        }
        return up;
    }

    int lower(int l,int r,int x,int idx=0,int i=0,int j=0){
        if(idx == 0) j = N;
        if(l >= j || r <= i) return 0;
        if(l <= i && r >= j) return upper_bound(segtree[idx].begin(),segtree[idx].end(),x) - segtree[idx].begin();
        return lower(l,r,x,2*idx+1,i,(i+j)/2) + lower(l,r,x,2*idx+2,(i+j)/2,j);
    }
};