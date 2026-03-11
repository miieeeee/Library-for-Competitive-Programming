#include<bits/stdc++.h>
using namespace std;

struct Point{
    int x, y;
    Point(){}
    Point(int _x, int _y):x(_x), y(_y){}
};
void arg_sort(vector<Point> &vec){
    auto sign = [&](Point a) -> int{
        if(a.x == 0 && a.y == 0) return 0;
        if(a.y > 0) return 1;
        if(a.y == 0 && a.x > 0) return 1;
        return -1;
    };
    auto comp = [&](Point a, Point b) -> bool{
        int sa = sign(a), sb = sign(b);
        if(sa != sb) return sa<sb;
        return a.x*b.y - a.y*b.x > 0;
    };
    sort(vec.begin(), vec.end(), comp);
}