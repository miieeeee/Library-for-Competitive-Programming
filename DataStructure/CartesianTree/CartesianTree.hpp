#pragma once

#include <vector>
#include <stack>

/// @brief 最小値を根とするCartesianTreeを構築する
/// @tparam S 
template<typename S>
struct CartesianTree{
    int n;
    std::vector<S> a;
    std::vector<int> par;
    int root = 0;
    CartesianTree(std::vector<S> &a) : a(a), n(a.size()), par(a.size(), -1){
        build();
    }
    void build(){
        std::stack<S> st;
        for(int i=0; i<n; i++){
            int prev = -1;
            while(!st.empty() && a[st.top()] > a[i]){
                prev = st.top();
                st.pop();
            }
            if(prev != -1) par[prev] = i;
            if(!st.empty()) par[i] = st.top();
            else root = i;
            st.push(i);
        }
    }
};