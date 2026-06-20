#pragma once

#include "Geometry/Common/Point.hpp"

template <typename S>
struct Line{
    S a, b, c;
    
    Line() = default;
    Line(S a, S b, S c) : a(a), b(b), c(c) {};
    Line(Point<S> A, Point<S> B) {
        a = A.y - B.y;
        b = -(A.x - B.x);
        c = -a*A.x - b*A.y;
    }

    static Point<S> cross_point(Line<S> l1, Line<S> l2){
        S d = l1.a*l2.b - l2.a*l1.b;
        S x = (l1.b*l2.c - l2.b*l1.c) / d;
        S y = (l1.c*l2.a - l2.c*l1.a) / d;
        return Point(x, y);
    }

    static tuple<bool, S, Point<S>> collision_point(Line<S> l, Point<S> p, Point<S> v1, Point<S> v2) {
        Point<S> v21 = v2 - v1;
        if(v1 == v2) {
            if(l.on_line(p)) return {true, 0, p};
            return {false, -1, Point<S>(-1, -1)};
        }
        Line<S> dl(p, p - v21);
        if(is_parallel(l, dl)) {
            if(l.on_line(p)) return {true, 0, p};
            return {false, -1, Point<S>(-1, -1)};
        }
        if(std::is_floating_point<S>::value) {
            auto ip = Line<S>::cross_point(l, dl);
            S t;
            if(abs(v21.x) >= EPS) t = (ip - p).x / v21.x;
            if(abs(v21.y) >= EPS) t = (ip - p).y / v21.y;
            return {true, t, ip};
        }

        auto ip = Line<S>::cross_point(l, dl);
        S t;
        if(v21.x != 0) t = (ip - p).x / v21.x;
        if(v21.y != 0) t = (ip - p).y / v21.y;
        return {true, t, ip};
    }

    bool on_line(Point<S> p) {
        if(std::is_floating_point<S>::value) {
            return abs(a*p.x + b*p.y + c) <= EPS;
        }
        return a*p.x + b*p.y + c == 0;
    }
    
    static bool is_parallel(Line<S> l1, Line<S> l2){
        if(std::is_floating_point<S>::value){
            return abs(l1.a*l2.b-l1.b*l2.a) < EPS;
        }
        return l1.a*l2.b == l1.b*l2.a;
    }

    friend bool is_orthogonal(Line<S> l1, Line<S> l2){
        if(std::is_floating_point<S>::value){
            return abs(l1.a*l2.b+l1.b*l2.a) < EPS;
        }
        return l1.a*l2.b + l1.b*l2.a == 0;
    }
};
