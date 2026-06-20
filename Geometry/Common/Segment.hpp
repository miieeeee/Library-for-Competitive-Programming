#pragma once

#include "Geometry/Common/Point.hpp"
#include "Geometry/Common/Line.hpp"

template <typename S>
struct Segment{
    Point<S> A, B;
    Segment() = default;
    Segment(Point<S> _A, Point<S> _B) : A(_A), B(_B) {} 

    static bool intersect(Segment<S> l1, Segment<S> l2, bool on_segment=false){
        S ccw1 = ccw(l1.A, l1.B, l2.A);
        S ccw2 = ccw(l1.A, l1.B, l2.B);
        S ccw3 = ccw(l2.A, l2.B, l1.A);
        S ccw4 = ccw(l2.A, l2.B, l1.B);
        if(ccw1*ccw2 < 0 && ccw3*ccw4 < 0) return true;
        if(on_segment && ccw1*ccw2*ccw3*ccw4 == 0) return true;
        return false;
    }

    /// @brief 線分上に点pが存在するか判定
    /// @param p 点
    /// @return <線分上に点pが存在するか>
    bool on_segment(Point<S> p) {
        Point<S> ap = p - A;
        Point<S> ab = B - A;
        if(std::is_floating_point<S>::value) {
            if(std::abs(cross(ab, ap)) > EPS) return false;
            return dot(p - A, p - B) <= EPS;
        }
        if(cross(ab, ap) != 0) return false;
        return dot(p - A, p - B) <= 0;
    }

    /// @brief 動く線分と動く点が衝突する時刻を求める
    /// @param l 線分
    /// @param p 点
    /// @param v1 線分の速度ベクトル
    /// @param v2 点の速度ベクトル
    /// @return <交差するか, 交差時刻, 交差場所>
    static tuple<bool, S, Point<S>> collision_point(Segment<S> l, Point<S> p, Point<S> v1, Point<S> v2) {
        auto [flag, t, cp] = Line<S>::collision_point(l.to_line(), p, v1, v2);
        if(flag && l.on_segment(cp)) return {flag, t, cp};
        return {false, t, cp};
    }

    /// @brief 動く2つの線分が交差する時刻を求める
    /// @param l1 線分1
    /// @param l2 線分2
    /// @param v1 線分1の速度ベクトル 
    /// @param v2 線分2の速度ベクトル
    /// @return <交差するか, 交差開始時刻, 交差終了時刻, 交差開始時の交差位置>
    static tuple<bool, S, S, Point<S>> collision_point(Segment<S> l1, Segment<S> l2, Point<S> v1, Point<S> v2) {
        bool flag = false;
        S s, t;
        Point<S> cp;
        rep(_, 2) {
            auto [flag1, t1, cp1] = collision_point(l1, l2.A, v1, v2);
            auto [flag2, t2, cp2] = collision_point(l1, l2.B, v1, v2);
            if(flag1) {
                if(!flag) {
                    cp = cp1;
                    s = t1;
                    t = t1;
                }
                flag = true;
                if(t1 < s) cp = cp1;
                s = min(s, t1);
                t = max(t, t1);
            }
            if(flag2) {
                if(!flag) {
                    cp = cp2;
                    s = t2;
                    t = t2;
                }
                flag = true;
                if(t2 < s) cp = cp2;
                s = min(s, t2);
                t = max(t, t2);
            }
            swap(l1, l2);
            swap(v1, v2);
        }
        
        return {flag, s, t, cp};
    }

    Line<S> to_line() { return Line(A, B); }
};
