// https://github.com/kth-competitive-programming/kactl/tree/main/content/geometry
// https://victorlecomte.com/cp-geo.pdf
#include "bits/stdc++.h"
using namespace std;

template<class T> struct pt {
    T x, y;
    pt(T x = 0, T y = 0) : x(x), y(y) {}
    bool operator < (pt p) const { return tie(x, y) < tie(p.x, p.y); }
    bool operator == (pt p) const { return tie(x, y) == tie(p.x, p.y); }
    pt operator + (pt p) const { return pt(x + p.x, y + p.y); }
    pt operator - (pt p) const { return pt(x - p.x, y - p.y); }
    pt operator * (T f) const { return pt(x * f, y * f); }
    pt operator / (T f) const { return pt(x / f, y / f); }
    T dot(pt p) const { return x * p.x + y * p.y; }
    T cross(pt p) const { return x * p.y - y * p.x; }
    T cross(pt a, pt b) const { return (a - *this).cross(b - *this); }
    T ori(pt a, pt b) const { T f = cross(a, b); return (f < 0 ? -1 : (f > 0 ? 1 : 0)); }
    T dist() const { return x * x + y * y; }
    double distsq() const { return sqrt(double(dist())); }
    pt rotate(double a) const { return pt(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a)); }
    friend ostream& operator << (ostream &os, pt p) {
        return os << "(" << p.x << ", " << p.y << ")";
    }
};
template<typename U, typename T>
U& operator >> (U& is, pt<T> &p) {
    T x, y; is >> x >> y;
    p = pt(x, y);
    return is;
}
template<class T> int sgn(T x) { return (x > 0) - (x < 0); }

template<class T> bool on_segment(T a, T b, T p) {
    return p.cross(a, b) == 0 && (a - p).dot(b - p) <= 0;
}

template<class T> vector<T> seg_int(T a, T b, T c, T d) {
    auto oa = c.cross(d, a), ob = c.cross(d, b),
         oc = a.cross(b, c), od = a.cross(b, d);
    if (sgn(oa) * sgn(ob) < 0 && sgn(oc) * sgn(od) < 0)
        return {(a * ob - b * oa) / (ob - oa)};
    set<T> s;
    if (on_segment(c, d, a)) s.insert(a);
    if (on_segment(c, d, b)) s.insert(b);
    if (on_segment(a, b, c)) s.insert(c);
    if (on_segment(a, b, d)) s.insert(d);
    return {s.begin(), s.end()};
}

