#include <complex>
using namespace std;

typedef complex<double> P;

// 許容する誤差ε
#define EPS (1e-10)
// 2つのスカラーが等しいかどうか
#define EQ(a,b) (abs((a)-(b)) < EPS)
// 2つのベクトルが等しいかどうか
#define EQV(a,b) ( EQ((a).real(), (b).real()) && EQ((a).imag(), (b).imag()) )

// ベクトルaの絶対値を求める
double length = abs(a);

// 2点a,b間の距離を求める
double distance = abs(a-b);

// ベクトルaの単位ベクトルを求める
P b = a / abs(a);

// ベクトルaの法線ベクトルn1,n2を求める
P n1 = a * P(0, 1);
P n2 = a * P(0, -1);

// ベクトルaの単位法線ベクトルun1,un2を求める
P un1 = (a * P(0, +1)) / abs(a);
P un2 = (a * P(0, -1)) / abs(a);

// 内積 (dot product) : a・b = |a||b|cosΘ
double dot(P a, P b) {
  return (a.real() * b.real() + a.imag() * b.imag());
}

// 外積 (cross product) : a×b = |a||b|sinΘ
double cross(P a, P b) {
  return (a.real() * b.imag() - a.imag() * b.real());
}

// 2直線の直交判定 : a⊥b <=> dot(a, b) = 0
int is_orthogonal(P a1, P a2, P b1, P b2) {
  return EQ( dot(a1-a2, b1-b2), 0.0 );
}

// 2直線の平行判定 : a//b <=> cross(a, b) = 0
int is_parallel(P a1, P a2, P b1, P b2) {
  return EQ( cross(a1-a2, b1-b2), 0.0 );
}

// 点cが直線a,b上にあるかないか
int is_point_on_line(P a, P b, P c) {
  return EQ( cross(b-a, c-a), 0.0 );
}

// 点cが線分a,b上にあるかないか(1)
int is_point_on_line(P a, P b, P c) {
  return EQ( cross(b-a, c-a), 0.0 ) &&
         (dot(b-a, c-a) > -EPS) &&
         (dot(a-b, c-b) > -EPS);
}

// 点cが線分a,b上にあるかないか(2)
int is_point_on_line(P a, P b, P c) {
  // |a-c| + |c-b| <= |a-b| なら線分上
  return (abs(a-c) + abs(c-b) < abs(a-b) + EPS);
}

// 点a,bを通る直線と点cとの距離
double distance_l_p(P a, P b, P c) {
  return abs(cross(b-a, c-a)) / abs(b-a);
}

// 点a,bを端点とする線分と点cとの距離
double distance_ls_p(P a, P b, P c) {
  if ( dot(b-a, c-a) < EPS ) return abs(c-a);
  if ( dot(a-b, c-b) < EPS ) return abs(c-b);
  return abs(cross(b-a, c-a)) / abs(b-a);
}

// a1,a2を端点とする線分とb1,b2を端点とする線分の交差判定
int is_intersected_ls(P a1, P a2, P b1, P b2) {
  return ( cross(a2-a1, b1-a1) * cross(a2-a1, b2-a1) < EPS ) &&
         ( cross(b2-b1, a1-b1) * cross(b2-b1, a2-b1) < EPS );
}

// a1,a2を端点とする線分とb1,b2を端点とする線分の交点計算
P intersection_ls(P a1, P a2, P b1, P b2) {
  P b = b2-b1;
  double d1 = abs(cross(b, a1-b1));
  double d2 = abs(cross(b, a2-b1));
  double t = d1 / (d1 + d2);

  return a1 + (a2-a1) * t;
}

// a1,a2を通る直線とb1,b2を通る直線の交差判定
int is_intersected_l(P a1, P a2, P b1, P b2) {
  return !EQ( cross(a1-a2, b1-b2), 0.0 );
}

// a1,a2を通る直線とb1,b2を通る直線の交点計算
P intersection_l(P a1, P a2, P b1, P b2) {
  P a = a2 - a1; P b = b2 - b1;
  return a1 + a * cross(b, b1-a1) / cross(b, a);
}