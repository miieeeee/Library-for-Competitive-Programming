#include<bits/stdc++.h>
using namespace std;

template<typename S>
struct CartesianTree{
    int n;
    vector<S> a;
    vector<int> par;
    int root = 0;
    CartesianTree(vector<S> &a) : a(a), n(a.size()), par(a.size(), -1){
        build();
    }
    void build(){
        stack<S> st;
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