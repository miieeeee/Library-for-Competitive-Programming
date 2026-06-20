#pragma once
#ifndef EPS
    #define EPS 1e-8
#endif

template <typename S>
struct Point {
    S x, y;
    Point() : x(0), y(0) {}
    Point(S _x, S _y) : x(_x), y(_y) {}

    Point operator+(const Point &a) const {
        return Point(x + a.x, y + a.y);
    }
    Point operator-(const Point &a) const {
        return Point(x - a.x, y - a.y);
    }
    Point operator*(const S &k) const {
        return Point(x*k, y*k);
    }
    Point operator/(const S &k) const {
        return Point(x/k, y/k);
    }

    Point& operator+=(const Point &a) {
        return (*this) = (*this) + a;
    }
    Point& operator-=(const Point &a) {
        return (*this) = (*this) - a;
    }
    Point& operator*=(const S &k) {
        return (*this) = (*this)*k;
    }
    Point& operator/=(const S &k) {
        return (*this) = (*this)/k;
    }

    bool operator==(const Point<S> &a) const {
        if(std::is_floating_point<S>::value) {
            return std::abs(this->x - a.x) < EPS && std::abs(this->y - a.y) < EPS;
        }
        return this->x == a.x && this->y == a.y;
    }
    bool operator!=(const Point &a) const {
        return !((*this) == a);
    }
};

template <typename S>
S dot(const Point<S> &a, const Point<S> &b){
    return a.x*b.x + a.y*b.y;
}

template <typename S>
S cross(const Point<S> &a, const Point<S> &b){
    return a.x*b.y - a.y*b.x;
}

template <typename S>
S sqnorm(const Point<S> &a){
    return a.x*a.x+a.y*a.y;
}

template <typename S>
S abs(const Point<S> &a){
    return sqrt(sqnorm(a));
}


// 3点 p0, p1, p2 の位置関係
static const int COUNTER_CLOCKWISE = 1;
static const int CLOCKWISE = -1;
static const int ONLINE = 0;     // p0 -- p2 -- p1

template <typename S>
int ccw(const Point<S>& p0, const Point<S>& p1, const Point<S>& p2) {
    Point<S> v1 = p1 - p0;
    Point<S> v2 = p2 - p0;
    S cr = cross(v1, v2);

    // 浮動小数点数の場合は誤差を考慮
    if (std::is_floating_point<S>::value) {
        if (cr > EPS) return COUNTER_CLOCKWISE;
        if (cr < -EPS) return CLOCKWISE;
        return ONLINE;
    }

    // otherwise 厳密に比較
    if (cr > 0) return COUNTER_CLOCKWISE;
    if (cr < 0) return CLOCKWISE;
    return ONLINE;
}