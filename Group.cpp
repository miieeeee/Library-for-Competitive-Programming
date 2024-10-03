#include<bits/stdc++.h>
using namespace std;
/*
  群（結合則・逆元・単位元）
  T : 集合
  add(a, b) : 結合則の成り立つ二項演算a°b
  inv(x) : 逆元
  e() : 単位元
*/
template<typename T, auto add, auto inv, auto e>
struct Group:T{
    Group(T v=e()):T(v){}
    Group operator-()const{
        return Group(inv(*this));
    }
    Group &operator+=(const Group &x){
        return *this = add(*this, x);
    }
    Group &operator-=(const Group &x){
        return *this = add(*this, inv(x));
    }
    Group operator+(const Group &x){
        return Group(*this) += x; 
    }
    Group operator-(const Group &x){
        return Group(*this) -= x; 
    }
    bool operator==(const Group &x){
        return T(*this) == T(x);
    }
    bool operator!=(const Group &x){
        return T(*this) != T(x);
    }
};
