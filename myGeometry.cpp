#include<bits/stdc++.h>
using namespace std;

const double EPS = 1e-10;
struct Point {
    double x, y;
    Point(){}
    Point(double _x, double _y) : x(_x), y(_y) {}
};

int sgn(const double &x) { return (x<-EPS ? -1 : (x>EPS ? 1 : 0)); }
inline bool eq(const double &x, const double &y) { return abs(x-y) < EPS; }

/// @brief aとbを結ぶ直線を表す
struct Line {
    Point a, b;
    Line(){}
    Line(Point _a, Point _b) : a(_a), b(_b) {}
    /// @brief Ax + by = Cを満たす直線
    Line(double A, double B, double C) {
        if (eq(A, 0)) { a = Point(0, C/B), b = Point(1, C/B); }
        else if (eq(B, 0)) { a = Point(C/A, 0), b = Point(C/A, 1); }
        else { a = Point(0, C/B), b = Point(C/A, 0); }
    }
};


inline Point operator + (const Point &a, const Point &b) { return Point(a.x+b.x, a.y+b.y); }
inline Point operator - (const Point &a, const Point &b) { return Point(a.x-b.x, a.y-b.y); }
inline Point operator * (const Point &a, const double &b) { return Point(a.x*b, a.y*b); }
inline Point operator * (const double &b, const Point &a) { return Point(b*a.x, b*a.y); }
inline Point operator / (const Point &a, const double &b) { return Point(a.x/b, a.y/b); }

inline double cross(const Point &a, const Point &b) { return a.x*b.y - a.y*b.x; }
inline double dot(const Point &a, const Point &b) { return a.x*b.x + a.y*b.y; }
inline double sqnorm(const Point &x) { return dot(x, x); }
inline double abs(const Point &x) { return sqrt(sqnorm(x)); }
inline Point unit(const Point &a) { return a/abs(a); }
/// @brief aをdeg[radian]だけ反時計回りに回転
inline Point rot(const Point &a, const double &deg) { return Point(a.x*cos(deg)-a.y*sin(deg), a.x*sin(deg)+a.y*cos(deg)); }
inline Point rot90(const Point &a) { return Point(-a.y, a.x); }
inline bool eq(const Point &a, const Point &b) { return abs(a-b) < EPS; }
inline double arg(const Point &a) { double res=atan2(a.y, a.x); return (res<0 ? res+2*M_PI : res); }
/// @brief pからlへの射影（垂線の足）
/// @param l 
/// @param p 
/// @return 
inline Point proj(const Line &l, const Point &p) { return l.a + dot(l.b-l.a, p-l.a)/sqnorm(l.b-l.a)*(l.b-l.a); }
inline Point reflection(const Line &l, const Point &p) { return p + 2*(proj(l, p) - p); }
inline Line normal(const Line &l, const Point &p) { Point dir = rot90(l.a-l.b);  return Line(p, p+dir); }

inline bool is_orthogonal(const Point &a, const Point &b) { return abs(dot(a, b)) < EPS; }
inline bool is_orthogonal(const Line &l1, const Line &l2) { return is_orthogonal(l1.a-l1.b, l2.a-l2.b); }
inline bool is_parallel(const Point &a, const Point &b) { return abs(cross(a, b)) < EPS; }
inline bool is_parallel(const Line &l1, const Line &l2) { return is_parallel(l1.a-l1.b, l2.a-l2.b); }
inline Point intersection(const Line &l1, const Line &l2) {
    double d1 = abs(cross(l1.a-l1.b, l2.a-l1.a));
    double d2 = abs(cross(l1.a-l1.b, l2.b-l1.a));
    double t = d1 / (d1+d2);
    return l2.a + (l2.b - l2.a) * t;
}

struct Circle {
    double r;
    Point p;
    Circle(){}
    Circle(double _r, Point _p) : r(_r), p(_p) {}
};

// 2つの円の交差判定
// 返り値は共通接線の数
int isIntersect(const Circle &c1, const Circle &c2) {
    double d = abs(c1.p - c2.p);
    // 2つの円が離れている場合
    if(d > c1.r + c2.r + EPS) {
        return 4;
    }
    // 外接している場合
    if(eq(d, c1.r + c2.r)) {
        return 3;
    }
    // 内接している場合
    if(eq(d, abs(c1.r - c2.r))) {
        return 1;
    }
    // 内包している場合
    if(d < abs(c1.r - c2.r) - EPS) {
        return 0;
    }
    return 2;
}

// 2つの円の交点
vector<Point> crossPoint(const Circle &c1, const Circle &c2) {
    vector<Point> res;
    int mode = isIntersect(c1, c2);
    // 2つの中心の距離
    double d = abs(c1.p - c2.p);
    // 2円が離れている場合
    if(mode == 4) {
        return res;
    }
    // 1つの円がもう1つの円に内包されている場合
    if(mode == 0) {
        return res;
    }
    // 2円が外接する場合
    if(mode == 3) {
        double t = c1.r / (c1.r + c2.r);
        res.emplace_back(c1.p + (c2.p - c1.p) * t);
        return res;
    }
    // 内接している場合
    if(mode == 1) {
        if(c2.r < c1.r - EPS) {
            res.emplace_back(c1.p + (c2.p - c1.p) * (c1.r / d));
        } else {
            res.emplace_back(c2.p + (c1.p - c2.p) * (c2.r / d));
        }
        return res;
    }
    // 2円が重なる場合
    double rc1 = (c1.r * c1.r + d * d - c2.r * c2.r) / (2 * d);
    double rs1 = sqrt(c1.r * c1.r - rc1 * rc1);
    if(c1.r - abs(rc1) < EPS) {
        rs1 = 0;
    }
    Point e12 = (c2.p - c1.p) / abs(c2.p - c1.p);
    Point norm = rot90(e12);
    res.emplace_back(c1.p + rc1 * e12 + rs1 * norm);
    res.emplace_back(c1.p + rc1 * e12 + rs1 * (-1*norm));
    return res;
}