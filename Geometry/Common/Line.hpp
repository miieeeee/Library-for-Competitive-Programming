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

    friend Point<S> intersection(Line<S> &l1, Line<S> &l2){
        S x = (l1.b*l2.c - l2.b*l1.c) / (l1.a*l2.b - l2.a*l1.b);
        S y = (l1.c - l1.a*x)/l1.b;
        return Point(x, y);
    }
    
    friend bool is_parallel(Line<S> l1, Line<S> l2){
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
