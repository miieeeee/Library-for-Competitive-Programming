#pragma once

#include "Geometry/Common/Point.hpp"
#include "Geometry/Common/Line.hpp"

template <typename S>
struct Segment{
    Point<S> A, B;
    Segment() = default;
    Segment(Point<S> _A, Point<S> _B) : A(_A), B(_B) {} 

    friend bool is_intersection(Segment<S> l1, Segment<S> l2, bool on_segment=false){
        S ccw1 = ccw(l1.A, l1.B, l2.A);
        S ccw2 = ccw(l1.A, l1.B, l2.B);
        S ccw3 = ccw(l2.A, l2.B, l1.A);
        S ccw4 = ccw(l2.A, l2.B, l1.B);
        if(ccw1*ccw2 < 0 && ccw3*ccw4 < 0) return true;
        if(on_segment && ccw1*ccw2*ccw3*ccw4 == 0) return true;
        return false;
    }

    Line<S> to_Line() { return Line(A, B); }
};
