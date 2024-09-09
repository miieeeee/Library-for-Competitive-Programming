#include<bits/stdc++.h>
using namespace std;
constexpr int INF = 1001001001; 
struct kDTree{
    using Point = pair<int, int>;
    using Iter = vector<Point>::iterator;
    kDTree *left = nullptr, *right = nullptr;
    int xmin = INF, xmax = -INF, ymin = INF, ymax = -INF, sz = 0;
    kDTree(Iter begin, Iter end, bool divide=true){
        for(auto itr=begin; itr!=end; itr++){
            auto [x, y] = *itr;
            xmin = min(xmin, x);
            xmax = max(xmax, x);
            ymin = min(ymin, y);
            ymax = min(ymax, y);
        }
        sz = int(end-begin);
        if(sz <= 1) return;
        auto cen = begin+sz/2;
        if(divide){
            nth_element(begin, cen, end, [](Point a, Point b){ return a.first < b.first; });
        }
        else{
            nth_element(begin, cen, end, [](Point a, Point b){ return a.second < b.second; });
        }
        l = kDTree(begin, cen, !divide);
        r = kDTree(cen, end, !divide);
    }
    int count(int x1, int x2, int y1, int y2){
        if(x2 < xmin || x1 > xmax || y2 < ymin || y1 > ymax) return 0;
        if(x1 >= xmin && x2 <= xmax && y1 >= ymin && y2 <= ymax) return sz;
        return l->count(x1, x2, y1, y2)+r->count(x1, x2, y1, y2);
    }
};
int main(){
    
}