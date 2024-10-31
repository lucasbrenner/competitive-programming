#include <bits/stdc++.h>

using namespace std;
typedef double T;

T EPS = 1e-9;
#define INF T(1e18)

int cmp(T x, T y = 0) { return (x <= y + EPS) ? (x + EPS < y) ? -1 : 0 : 1; }

struct point {
    T x, y;
    int id;
    point(T x_ = 0, T y_ = 0, int id_ = -1): x(x_), y(y_), id(id_) {}
    point operator + (const point& b) const { return point(x + b.x, y + b.y, id); }
    point operator - (const point& b) const { return point(x - b.x, y - b.y, id); }
    point operator * (T c) { return point(x*c, y*c, id); }
    point operator / (T c) { return point(x/c, y/c, id); }
    bool operator < (const point& b) const { return tie(x, y) < tie(b.x, b.y); }
    bool operator == (const point& b) const { return tie(x, y) == tie(b.x, b.y); }
};

typedef pair<point, point> segm;
typedef vector<point> polygon;

inline T abs(point a) { return sqrt(a.x * a.x + a.y * a.y);}
inline T escalar(point a, point b) { return a.x * b.x + a.y * b.y;}
inline T vetorial(point a, point b) { return a.x * b.y - a.y * b.x;}

/** Counter-clockwise (o is the pivot)**/
int ccw(point p, point q, point o) {return cmp(vetorial(p - o, q - o));}

/** o is the pivot **/
T angle(point p, point q, point o) {
	point u = p - o, v = q - o;
	return abs(atan2(vetorial(u, v), escalar(u, v)));
}

/** CCW rotate around origin **/
point rot(point p, double a) {
    return {p.x*cos(a) - p.y*sin(a), p.x*sin(a) + p.y*cos(a)};
}

/** Rotate 90 degrees around the origin, CCW **/
point perp(point p) {return {-p.y, p.x};}

T polygon_area(vector<point> &p) {
    if(p.size() <= 2) return 0;
    T area = vetorial(p.back(), p[0]);
    for(int i = 1; i < (int)p.size(); i++) area += vetorial(p[i-1], p[i]);
    return abs(area) / 2;
}

/** Center of mass of a polygon with uniform mass distribution **/
point polygon_centroid(vector<point> &poly) {
    point ret = (poly.back() + poly[0]) * vetorial(poly.back(), poly[0]);
    for(int i = 1; i < (int)poly.size(); i++)
        ret = ret + (poly[i-1] + poly[i]) * vetorial(poly[i-1], poly[i]);
    ret = ret / (6 * polygon_area(poly));
    return ret;
}

long long areaTriangle(const point &a, const point &b, const point &c) {
  return (a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y));
}

//Check if point is inside of a convex polygon in O(log(n))
bool inConvexPoly(const vector < point > &convPoly, point p) {
  long long start = 1, last = (int) convPoly.size() - 1;

  while (last - start > 1) {
    long long mid = (start + last) / 2;
    if (areaTriangle(convPoly[0], convPoly[mid], p) < 0) last = mid;
    else start = mid;
  }

  long long r0 = abs(areaTriangle(convPoly[0], convPoly[start], convPoly[last]));
  long long r1 = abs(areaTriangle(convPoly[0], convPoly[start], p));
  long long r2 = abs(areaTriangle(convPoly[0], convPoly[last], p));
  long long r3 = abs(areaTriangle(convPoly[start], convPoly[last], p));

  // if you need strictly inside
  long long r4 = areaTriangle(convPoly[0], convPoly[1], p);
  long long r5 = areaTriangle(convPoly[0], convPoly[convPoly.size() - 1], p);

  // if you need strictly inside, add '&& r3 != 0 && r4 != 0 && r5 != 0' to return
  return r0 == (r1 + r2 + r3);
}

struct line {
    T a, b, c;
    line(T a_, T b_, T c_): a(a_), b(b_), c(c_) {
        T tmp = sqrt(a * a + b * b);
        a /= tmp, b /= tmp, c /= tmp;
    }
    line(point p1, point p2):
        a(p1.y - p2.y),
        b(p2.x - p1.x),
        c(p1.x*p2.y - p2.x*p1.y) {
            T tmp = sqrt(a * a + b * b);
            a /= tmp, b /= tmp, c /= tmp;
        }
};

inline T point_line(point a, point l1, point l2) {
    return abs(vetorial(l2 - l1, a - l1)) / abs(l2 - l1);
}

inline T point_line(point a, line l) {
    return abs(l.a*a.x + l.b*a.y + l.c) / sqrt(l.a*l.a + l.b*l.b);
}

bool parallel(line a, line b) {
    return abs(a.b * b.a - a.a * b.b) < EPS;
}

T distLines(line a, line b) {
    if(!parallel(a, b)) return 0;
    if(cmp(a.a) == 0) return point_line(point(0, -a.c/a.b), b);
    return point_line(point(-a.c/a.a, 0), b);
}

point intersection(line a, line b) {
    point ret;
    ret.x = (b.c * a.b - a.c * b.b) / (b.b * a.a - a.b * b.a);
    ret.y = (a.c * b.a - b.c * a.a) / (b.b * a.a - a.b * b.a);
    return ret;
}

bool equal_lines(line a, line b) {
    if(!parallel(a,b)) return false;
    return abs(distLines(a,b)) < EPS;
}

line perpendicular(line a, point b) {
    T la, lb, lc;
    la = a.b;
    lb = -a.a;
    lc = -la * b.x - lb * b.y;
    return line(la, lb, lc);
}

inline T point_segment(segm s, point a) {
    if(escalar(s.second - s.first, a - s.first) < 0) return abs(a - s.first);
    if(escalar(s.first - s.second, a - s.second) < 0) return abs(a - s.second);
    if(cmp(abs(s.first - s.second))) return point_line(a, s.first, s.second);
    return abs(s.first - a);
}

/** proper intersection of segments (strictly inside) **/
bool properInter(point a, point b, point c, point d, point &out) {
    T oa = ccw(d, a, c), ob = ccw(d, b, c), oc = ccw(b, c, a), od = ccw(b, d, a);
    // Proper intersection exists iff opposite signs
    if (oa*ob < 0 && oc*od < 0) {
        out = intersection({a, b}, {c, d});
        return true;
    }
    return false;
}

bool onSegment(point a, point b, point p) {
    return ccw(b, p, a) == 0 && cmp(escalar(a-p, b-p)) <= 0;
}

set<point> segment_intersection(point a, point b, point c, point d) {
    point out;
    if (properInter(a, b, c, d, out)) return {out};
    set<point> s;
    if (onSegment(c, d, a)) s.insert(a);
    if (onSegment(c, d, b)) s.insert(b);
    if (onSegment(a, b, c)) s.insert(c);
    if (onSegment(a, b, d)) s.insert(d);
    return s;
}

T segSeg(point a, point b, point c, point d) {
    point dummy;
    if (properInter(a, b, c, d, dummy)) return 0;
    return min({point_segment({a, b}, c), point_segment({a, b}, d),
                point_segment({c, d}, a), point_segment({c, d}, b)});
}

struct circle {
    point center; T rad;
    circle(point c, T r): center(c), rad(r) {}
    circle(point p1, point p2) {
        center = (p1 + p2) / 2;
        rad = abs(p2 - p1) / 2;
    }
    circle(point p1, point p2, point p3) {
        line l12 (p1, p2);
        line l23 (p2, p3);
        assert(!equal_lines(l12, l23));
        point p12 = (p1 + p2) / 2;
        point p23 = (p2 + p3) / 2;
        center = intersection(perpendicular(l12, p12), perpendicular(l23, p23));
        rad = abs(center - p1);
    }
    bool circle_intersection(circle c, pair<point, point> &out) {
        double d = abs(c.center-center), co = (d*d+rad*rad-c.rad*c.rad)/(2*d*rad);
        if (abs(co) > 1) return false;
        double alpha = acos(co); point r = (c.center - center) / d * rad;
        out = {center + rot(r, -alpha), center + rot(r, alpha)};
        return true;
    }
};

circle mec_solve1(vector<point> &p, int i, int j) {
    circle c(p[i], p[j]);
    for(int k = 0; k < j; k++)
        if(cmp(abs(c.center - p[k]), c.rad) == 1)
            c = circle(p[i], p[j], p[k]);
    return c;
}

circle mec_solve2(vector<point> &p, int i) {
    circle c(p[0], p[i]);
    for(int j = 1; j < i; j++)
        if(cmp(abs(c.center - p[j]), c.rad) == 1)
            c = mec_solve1(p, i, j);
    return c;
}

circle mec_solve3(vector<point> &p) {
    circle c(p[0], p[1]);
    for(int i = 2; i < (int)p.size(); i++)
        if(cmp(abs(c.center - p[i]), c.rad) == 1)
            c = mec_solve2(p, i);
    return c;
}

circle minimum_enclosing_circle(vector<point> p) {
    if(p.size() == 1) return circle{p[0], 0};
    random_shuffle(p.begin(), p.end());
    return mec_solve3(p);
}

circle mec(vector<point> ps) {
	shuffle(ps.begin(), ps.end(), mt19937(chrono::steady_clock::now().time_since_epoch().count()));
	double EPS = 1 + 1e-8;
    circle c(ps[0], 0);
    for (int i = 0; i < (int)ps.size(); i++) if (abs(c.center - ps[i]) > c.rad * EPS) {
        c = circle(ps[i], 0);
        for (int j = 0; j < i; j++) if (abs(c.center - ps[j]) > c.rad * EPS) {
            c = circle(ps[i], ps[j]);
            for (int k = 0; k < j; k++) 
                if (abs(c.center - ps[k]) > c.rad * EPS)
                    c = circle(ps[i], ps[j], ps[k]);
        }
    }
	return c;
}

vector<point> tangents(circle c1, point p2) { // todo: 4 tangentes
    point d = p2 - c1.center;
    double dr = c1.rad, d2 = escalar(d, d), h2 = d2-dr*dr;
    assert(cmp(h2) >= 0 && cmp(d2) != 0);
    vector<point> ret({c1.center + (d*dr + perp(d)*sqrt(h2))/d2*dr});
    if(cmp(h2)) ret.push_back(c1.center + (d*dr - perp(d)*sqrt(h2))/d2*dr);
    return ret;
}

/// distance from a to b avoiding circle c. assume a and b are already outside c
T distAvoidCircle(point a, point b, circle c) {
    if(point_segment({a, b}, c.center) < c.rad) {
        auto tg1 = tangents(c, a), tg2 = tangents(c, b);
        T ret = DBL_MAX;
        for(point ta : tg1) for(point tb : tg2)
            ret = min(ret, abs(ta - a) + abs(angle(ta, c.center, tb))*c.rad + abs(b - tb));
        return ret;
    }
    else return abs(b - a);
}

namespace convex_hull { /// careful equal points. for collinear use > and <.
    pair<vector<int>, vector<int>> ulHull(const vector<point>& P) {
        vector<int> p(P.size()), u, l; iota(p.begin(), p.end(), 0);
        sort(p.begin(), p.end(), [&P](int a, int b) { return P[a] < P[b]; });
        for(int i : p) {
            #define ADDP(C, cmp)\
                while (C.size() > 1 && ccw(P[C.back()], P[i], P[C.end()[-2]]) cmp 0)\
                    C.pop_back();\
                C.push_back(i);
            ADDP(u, >=); ADDP(l, <=);
        }
        return {u,l};
    }
    vector<int> hullInd(const vector<point>& P) {
        vector<int> u, l; tie(u,l) = ulHull(P);
        if (l.size() <= 1) return l;
        if (P[l[0]] == P[l[1]]) return {0};
        l.insert(l.end(), rbegin(u)+1, rend(u)-1);
        return l;
    }
    vector<point> hull(const vector<point>& P) {
        vector<int> v = hullInd(P);
        vector<point> res;
        for(int i : v) res.push_back(P[i]);
        return res;
    }
}

///Pick a very tight EPS (like 1e-16, use long double if needed)
vector<vector<point> > voronoi(vector<point> p) {
    int n = (int)p.size();
    vector<vector<point> > diagram, ans(p.size() + 4, vector<point>(2));
    vector<point> inv, hull;
    p.resize(p.size() + 4);
    for(int i = 0; i < n; i++) {
        EPS = 1e-15;
        diagram.push_back(vector<point>());

        p[n].x = 2*(-INF) - p[i].x; p[n].y = p[i].y;
        p[n+1].x = p[i].x; p[n+1].y = 2*INF - p[i].y;
        p[n+2].x = 2*INF - p[i].x; p[n+2].y = p[i].y;
        p[n+3].x = p[i].x; p[n+3].y = 2*(-INF) - p[i].y;

        inv.clear();
        for(int j = 0; j < n + 4; j++) {
            if(j == i) continue;
            T tmp = escalar(p[j] - p[i], p[j] - p[i]);
            inv.push_back(point((p[j].x - p[i].x)/tmp, (p[j].y - p[i].y)/tmp, j));
        }

        hull = convex_hull::hull(inv);
        hull.push_back(hull[0]);
        EPS = 1e-9;

        for(int j = 0; j < (int)hull.size(); j++) {
            assert(hull[j].id != -1);
            ans[j][0].x = (p[i].x + p[hull[j].id].x) / 2;
            ans[j][0].y = (p[i].y + p[hull[j].id].y) / 2;
            ans[j][1].x = ans[j][0].x - (p[hull[j].id].y - p[i].y);
            ans[j][1].y = ans[j][0].y + (p[hull[j].id].x - p[i].x);

            if(j) {
                line r(ans[j-1][0], ans[j-1][1]), s(ans[j][0], ans[j][1]);
                if(parallel(r, s)) continue;
                point b = intersection(r, s);
                diagram[i].push_back(b);
            }
        }
    }

    return diagram;
}

/// 0 - Border / 1 - Outside / -1 - Inside
int point_inside_polygon(point p, vector<point> &poly) {
    int n = (int)poly.size(), windingNumber = 0;
    for(int i = 0; i < n; i++) {
        if(abs(p - poly[i]) < EPS) return 0;
        int j = (i + 1) % n;
        if(cmp(poly[i].y, p.y) == 0 && cmp(poly[j].y, p.y) == 0) {
            if(cmp(min(poly[i].x, poly[j].x), p.x) <= 0 &&
                cmp(p.x, max(poly[i].x, poly[j].x)) <= 0) return 0;
        } else {
            bool below = (cmp(poly[i].y, p.y) == -1);
            if(below !=  (cmp(poly[j].y, p.y) == -1)) {
                int orientation = ccw(p, poly[j], poly[i]);
                if(orientation == 0) return 0;
                if(below == (orientation > 0)) windingNumber += below ? 1 : -1;
            }
        }
    }
    return (windingNumber == 0) ? 1 : -1;
}

// https://www.dropbox.com/sh/mkyxabccsf6k80u/AABYol6e4tgbrmnUNnqhf6DRa/Geometria?dl=0&subfolder_nav_tracking=1
namespace halfplane {
    pair<bool, point> has_intersection(vector<pair<point, point>> v){
        random_shuffle(v.begin(), v.end());
        point p;
        for(int i = 0; i < (int)v.size(); i++) if(ccw(v[i].second, p, v[i].first) != 1) {
            point dir = (v[i].second - v[i].first)/abs(v[i].second - v[i].first);
            point l = v[i].first - dir*1e15;
            point r = v[i].first + dir*1e15;
            if(r < l) swap(l, r);
            for(int j = 0; j < i; j++) {
                if(ccw(v[i].first - v[i].second, v[j].first - v[j].second, point())==0){
                    if(ccw(v[j].second, p, v[j].first) == 1)
                        continue;
                    return {false, point()};
                }
                if(ccw(v[j].second, l, v[j].first) != 1)
                    l = max(l, intersection({v[i].first, v[i].second}, {v[j].first, v[j].second}));
                if(ccw(v[j].second, r, v[j].first) != 1)
                    r = min(r, intersection({v[i].first, v[i].second}, {v[j].first, v[j].second}));
                if(!(l < r)) return {false, point()};
            }
            p = r;
        }
        return {true, p};
    }
    int halfplane(line l) {
		return cmp(l.b) > 0 || (cmp(l.b) == 0 && cmp(l.a) > 0);
	}
	bool cmpL(line& l1, line& l2) {
	    if(halfplane(l1) != halfplane(l2))
            return halfplane(l1) < halfplane(l2);
        point n1(l1.a, l1.b), n2(l2.a, l2.b);
        if(cmp(vetorial(n1, n2))) return cmp(vetorial(n1, n2)) < 0;
        return cmp(l1.c, l2.c) < 0;
	}
	bool strict(point p, line& l) {
        T val = l.a * p.x + l.b * p.y + l.c;
        return cmp(val) > 0;
    }
    vector<point> intersect(vector<line> v) {
        v.push_back({1, 0, INF});   v.push_back({0, 1, INF});
        v.push_back({-1, 0, INF});  v.push_back({0, -1, INF});
        sort(v.begin(), v.end(), cmpL);
        deque<line> d;
        int s = 0;
        for (int i = 0; i < (int)v.size(); ++i) {
            if (i && cmp(v[i].a, v[i-1].a) == 0 && cmp(v[i].b, v[i-1].b) == 0) {
                continue;
            }
            while (s >= 2 && !strict(intersection(d[s-1], d[s-2]), v[i])) {
                d.pop_back();
                --s;
            }
            while (s >= 2 && !strict(intersection(d[0], d[1]), v[i])) {
                d.pop_front();
                --s;
            }
            if (s < 2 || strict(intersection(v[i], d[s - 1]), d[0])) {
                d.push_back(v[i]);
                ++s;
            }
            if (s >= 2) {
                point n1 = {d[s-2].a, d[s-2].b};
                point n2 = {d[s-1].a, d[s-1].b};
                if (cmp(vetorial(n1, n2)) > 0) return {};
            }
        }
        if (s <= 2) return {};
        vector<point> ret;
        for (int i = 0, n = (int)d.size(); i < n; ++i)
            ret.push_back(intersection(d[i], d[(i+1)%n]));
        return ret;
    }
}

namespace delaunay { // use T as long long
    typedef struct Quad* Q;
    typedef long long ll;
    typedef __int128_t lll; // (can be ll if coords are < 2e4)
    point arb(INF, INF); // not equal to any other point
    struct Quad {
        bool mark;
        Q o, rot;
        point p;
        point F() { return r()->p; }
        Q r() { return rot->rot; }
        Q prev() { return rot->o->rot; }
        Q next() { return r()->prev(); }
    };
    // test if p is in the circumcircle
    bool circ(point p, point a, point b, point c) {
        ll ar = vetorial(b-a, c-a);
        assert(ar);
        if (ar < 0) swap(a, b);
        lll p2 = escalar(p, p), A = escalar(a, a) - p2,
        B = escalar(b, b) - p2, C = escalar(c, c) - p2;
        return vetorial(a-p, b-p) * C + vetorial(b-p, c-p) * A + vetorial(c-p, a-p) * B > 0;
    }
    Q makeEdge(point orig, point dest) {
        Q q[] = {new Quad{0, nullptr, nullptr, orig}, new Quad{0, nullptr, nullptr, arb},
                new Quad{0, nullptr, nullptr, dest}, new Quad{0, nullptr, nullptr, arb}};
        for (int i = 0; i < 4; ++i) q[i]->o = q[-i & 3], q[i]->rot = q[(i + 1) & 3];
        return *q;
    }
    void splice(Q a, Q b) {
        swap(a->o->rot->o, b->o->rot->o);
        swap(a->o, b->o);
    }
    Q connect(Q a, Q b) {
        Q q = makeEdge(a->F(), b->p);
        splice(q, a->next());
        splice(q->r(), b);
        return q;
    }
    pair<Q, Q> rec(const vector<point>& s) {
        if (s.size() <= 3) {
            Q a = makeEdge(s[0], s[1]), b = makeEdge(s[1], s.back());
            if (s.size() == 2) return {a, a->r()};
            splice(a->r(), b);
            auto side = vetorial(s[1]-s[0], s[2]-s[0]);
            Q c = side ? connect(b, a) : 0;
            return {side < 0 ? c -> r() : a, side < 0 ? c : b -> r()};
        }
        #define H(e) e->F(), e->p
        #define valid(e)(vetorial((base->F())-(e->F()), (base->p)-(e->F())) > 0)
        Q A, B, ra, rb;
        int half = (int)s.size() / 2;
        tie(ra, A) = rec({s.begin(), s.end() - half});
        tie(B, rb) = rec({s.size() - half + s.begin(), s.end()});
        while ((vetorial((A->F())-(B->p), (A->p)-(B->p)) < 0 && (A = A->next())) ||
            (vetorial((B->F())-(A->p), (B->p)-(A->p)) > 0 && (B = B->r()->o)));
        Q base = connect(B->r(), A);
        if (A->p == ra->p) ra = base->r();
        if (B->p == rb->p) rb = base;
        #define DEL(e, init, dir)\
        Q e = init->dir; if (valid(e))\
        while (circ(e->dir->F(), H(base), e->F())) {\
            Q t = e->dir;\
            splice(e, e->prev());\
            splice(e->r(), e->r()->prev());\
            e = t;\
        }
        for (;;) {
            DEL(LC, base->r(), o);
            DEL(RC, base, prev());
            if (!valid(LC) && !valid(RC)) break;
            if (!valid(LC) || (valid(RC) && circ(H(RC), H(LC))))
              base = connect(RC, base->r());
            else base = connect(base->r(), LC->r());
        }
        return {ra, rb};
    }
    vector<array<point, 3>> triangulate(vector<point> pts) {
        sort(pts.begin(), pts.end());
        assert(unique(pts.begin(), pts.end()) == pts.end());
        if (pts.size() < 2) return {};
        Q e = rec(pts).first;
        vector<Q> q = {e};
        int qi = 0;
        while (vetorial((e->F())-(e->o->F()), (e->p)-(e->o->F())) < 0) e = e->o;
        #define ADD {\
            Q c = e;\
            do {\
              c->mark = 1;\
              pts.push_back(c->p);\
              q.push_back(c->r());\
              c = c->next();\
            } while (c != e);\
        }
        ADD;
        pts.clear();
        while (qi < q.size()) if (!(e = q[qi++])->mark) ADD;
        vector<array<point, 3>> ret;
        for (int i = 0; i < (int)pts.size() / 3; ++i)
            ret.push_back({pts[3*i], pts[3*i+1], pts[3*i+2]});
        return ret;
    }
}

pair<point, point> closest_pair_of_points(vector<point> v) {
    pair<T, pair<point, point>> bes; bes.first = INF;
    set<point> S; int ind = 0;
    sort(v.begin(), v.end());
    for(int i = 0; i < (int)v.size(); i++) {
        if (i && v[i] == v[i-1]) return {v[i], v[i]};
        for (; v[i].x - v[ind].x >= bes.first; ++ind)
            S.erase({v[ind].y, v[ind].x});
        for (auto it = S.upper_bound({v[i].y-bes.first, INF}); it != S.end() && it->x < v[i].y+bes.first; ++it) {
            point t = {it->y, it->x};
            bes = min(bes, {abs(t-v[i]), {t, v[i]}});
        }
        S.insert(point{v[i].y, v[i].x});
    }
    return bes.second;
}

/// convex polygon
T maxDist2(const vector<point>& poly) {
  int n = poly.size();
  T res = 0;
  for (int i = 0, j = n < 2 ? 0 : 1; i < j; ++i)
    for (;; j = (j+1)%n) {
      res = max(res, escalar(poly[i] - poly[j], poly[i] - poly[j]));
      if (ccw(poly[i+1] - poly[i], poly[(j+1)%n] - poly[j], point()) <= 0) break;
    }
  return res;
}

point pivot;
bool comp(point a, point b){ // radial sort
    a = a - pivot; b = b - pivot;
	if((a.x > 0 || (a.x==0 && a.y>0) ) && (b.x < 0 || (b.x==0 && b.y<0))) return 1;
	if((b.x > 0 || (b.x==0 && b.y>0) ) && (a.x < 0 || (a.x==0 && a.y<0))) return 0;
	T R = vetorial(a, b);
	if(R) return R > 0;
	return escalar(a, a) < escalar(b, b);
}

polygon minkowski_sum(polygon a, polygon b){
	if(a.empty() || b.empty()) return polygon(0);
	// SORT
	for(auto& v : {&a, &b}) {
        pivot = *min_element(v->begin(), v->end());
        sort(v->begin(), v->end(), comp);
        v->resize(unique(v->begin(), v->end()) - v->begin());
	}
	pivot = {0, 0};

    int pa = 0, pb = 0, sa = (int)a.size(), sb = (int)b.size();
	if(min(sa, sb) < 2) {
		polygon ret(0);
		for(int i = 0; i < sa; i++)
            for(int j = 0; j < sb; j++)
                ret.push_back(a[i] + b[j]);
        return ret;
	}
	polygon ret;
	ret.push_back(a[0]+b[0]);
	while(pa < sa || pb < sb){
		point p = ret.back();
		if(pb == sb || (pa < sa && comp(a[(pa+1)%sa]-a[pa],b[(pb+1)%sb]-b[pb])))
			p = p + (a[(pa+1)%sa]-a[pa]), pa++;
		else p = p + (b[(pb+1)%sb]-b[pb]), pb++;
		while(ret.size() > 1 && !ccw(ret[ret.size()-1], p, ret[ret.size()-2]))
			ret.pop_back();
		ret.push_back(p);
	}
	ret.pop_back();
	return ret;
}

/// be careful 3+ collinear points
void radial_sweep_180_line(vector<point> p, int idx) {
    swap(p[idx], p[0]); point piv = p[0]; for(point &pp : p) pp = pp - piv;

    sort(p.begin() + 1, p.end(), [&](point &a, point &b) {
        int ua = (a.x > 0 or (a.x == 0 and a.y >= 0)), ub = (b.x > 0 or (b.x == 0 and b.y >= 0));
        if(ua != ub) return ua < ub;
        T R = vetorial(a, b);
        return R ? R > 0 : escalar(a, a) < escalar(b, b);
    });

    auto tmp = p;
    p.insert(p.end(), tmp.begin() + 1, tmp.end());

    // center is p[0]
    for(int i = (int)tmp.size(), j = 1; i < (int)p.size(); i++) {
        while(j < i && ccw(p[i], p[j], p[0]) >= 0) j++;
        /// [j, i) clockwise
    }
}

ld circle_intersection_area(ld x1, ld y1, ld r1, ld x2, ld y2, ld r2) {
    ld d = sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));

    if(d >= r1+r2) return 0;
    if (d+r1 <= r2) return pi*r1*r1;
    if(d+r2 <= r1) return pi*r2*r2;

    ld ang1 = 2*acos( (r2*r2 - r1*r1 - d*d)/(-2*r1*d) );
    ld ang2 = 2*acos( (r1*r1 - r2*r2 - d*d)/(-2*r2*d) );

    ld areaarco1 = ang1*r1*r1/2.0;
    ld areatri1 = r1*r1*sin(ang1)/2.0;

    ld areaarco2 = ang2*r2*r2/2.0;
    ld areatri2 = r2*r2*sin(ang2)/2.0;

    return areaarco1 - areatri1 + areaarco2 - areatri2;
}


int main() {
}
