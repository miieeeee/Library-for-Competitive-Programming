#pragma once

/// @brief 区間をsetで管理するやつ。
/// @tparam T 
template<typename T>
struct RangeSet {
    private:
    bool m_open;
    set<pair<T, T>> st;
    public:
    RangeSet(bool open):m_open(open){}
    void add(T l, T r) {
        assert(l <= r-m_open);
        auto it = st.lower_bound({l+1, l+1});
        if(it != st.begin() && prev(it)->second-m_open >= l){
            l = prev(it)->first;
            if(r < prev(it)->second) r = prev(it)->second;
            it = st.erase(prev(it));
        }
        while(it != st.end() && it->first+m_open <= r){
            if(r < it->second) r = it->second;
            it = st.erase(it);
        }
        st.insert({l, r});
    }
    void add(T x) { add(x, x+m_open); }
    void del(T l, T r) {
        int nl=l+1, nr = r-1;
        assert(l <= r-m_open);
        auto it = st.lower_bound({l, l});
        if(it != st.begin() && prev(it)->second > l+m_open) it--;
        while(it != st.end() && it->first < r+m_open){
            if(nr < it->second) nr = it->second;
            if(nl > it->first) nl = it->first;
            it = st.erase(it);
        }
        if(r <= nr) st.insert({r-m_open, nr});
        if(nl+m_open <= l) st.insert({nl, l});
    }
    void del(T x) { del(x, x+m_open); }
    bool covered(T l, T r) {
        assert(l<=r);
        auto it = st.lower_bound({l+1, l+1});
        return it != st.begin() && prev(it)->second >= r; 
    }
    bool covered(T x) { return covered(x, x+m_open); }
    int size(T x) {
        auto it = st.lower_bound({x+1, x+1});
        if(it == st.begin() || prev(it)->second+m_open < x) return 0;
        return prev(it)->second-prev(it)->first+1-m_open;
    }
    int size() { return st.size(); }
    T mex(T base=T(0)) {
        auto it = st.lower_bound({base+1, base+1});
        if(it == st.begin() || prev(it)->second < base+m_open) return base;
        return prev(it)->second+1-m_open; 
    }
};
