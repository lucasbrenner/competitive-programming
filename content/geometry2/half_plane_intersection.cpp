#include "point.cpp"

using pt = Point<double>;
const double EPS = 1e-9;

pt lineIntersectSeg(pt p, pt q, pt A, pt B) {
    double c = (A-B).cross(p-q);
    double a = A.cross(B);
    double b = p.cross(q);
    return ((p-q)*(a/c)) - ((A-B)*(b/c));
}

bool parallel(pt a, pt b) {
    return fabs(a.cross(b)) < EPS;
}

struct line {
    pt a, b;
};

pt dir(line h) {
    return h.b - h.a;
}
bool belongs(line h, pt a) {
    return dir(h).cross(a - h.a) > EPS;
}

vector<pt> intersect(vector<line> H, double W) {
    vector<pt> pts = { {-W, -W}, {W, -W}, {W, W}, {-W, W} };
    rep(i, 0, 4) H.push_back({pts[i], pts[(i+1)%4]});
    sort(all(H), [](const line &ha, const line &hb) {
        pt a = dir(ha), b = dir(hb);
        if (parallel(a, b) && a.dot(b) > EPS)
            return b.cross(ha.a - hb.a) < -EPS;
        if (b.y*a.y > EPS) return a.cross(b) > EPS;
        if (fabs(b.y) < EPS && b.x > EPS) return false;
        if (fabs(a.y) < EPS && a.x > EPS) return true;
        return b.y < a.y;
    });
    int i = 0;
    while(parallel(dir(H[0]), dir(H[i]))) i++;
    deque<pt> P;
    deque<line> S = { H[i - 1] };
    for (; i < sz(H); i++) {
        while(sz(P) && !belongs(H[i], P.back()))
            P.pop_back(), S.pop_back();
        pt df = dir(S.front()), di = dir(H[i]);
        if (P.empty() && df.cross(di) < EPS)
            return vector<pt>();
        P.push_back(lineIntersectSeg(H[i].a, H[i].b,
            S.back().a, S.back().b));
        S.push_back(H[i]);
    }
    #define EXIST (sz(P) && sz(S))

    while(EXIST && (!belongs(S.back(), P.front()) ||
        !belongs(S.front(), P.back()))) {
        while(EXIST && !belongs(S.back(), P.front()))
            P.pop_front(), S.pop_front();
        while(EXIST && !belongs(S.front(), P.back()))
            P.pop_back(), S.pop_back();
    }

    if(sz(S)) P.push_back(lineIntersectSeg(S.front().a,
        S.front().b, S.back().a, S.back().b));
    return vector<pt>(all(P));
}

