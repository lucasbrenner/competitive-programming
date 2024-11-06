#include "point.cpp"

typedef Point<double> P;
const double EPS = 1e-9;

P lineIntersectSeg(P p, P q, P A, P B) {
    double c = (A-B).cross(p-q);
    double a = A.cross(B);
    double b = p.cross(q);
    return ((p-q)*(a/c)) - ((A-B)*(b/c));
}

bool parallel(P a, P b) {
    return fabs(a.cross(b)) < EPS;
}

struct line {
    P a, b;
};

P dir(line h) {
    return h.b - h.a;
}
bool belongs(line h, P a) {
    return dir(h).cross(a - h.a) > -EPS;
}

vector<P> intersect(vector<line> H, double W) {
    vector<P> box = { {-W, -W}, {W, -W}, {W, W}, {-W, W} };
    rep(i, 0, 4) H.push_back({box[i], box[(i+1)%4]});
    sort(all(H), [](const line &ha, const line &hb) {
        P a = dir(ha), b = dir(hb);
        if (parallel(a, b) && a.dot(b) > EPS)
            return b.cross(ha.a - hb.a) < -EPS;
        if (b.y*a.y > EPS) return a.cross(b) > EPS;
        if (fabs(b.y) < EPS && b.x > EPS) return false;
        if (fabs(a.y) < EPS && a.x > EPS) return true;
        return b.y < a.y;
    });
    int i = 0;
    while(parallel(dir(H[0]), dir(H[i]))) i++;
    deque<P> pts;
    deque<line> S = { H[i - 1] };
    for (; i < sz(H); i++) {
        while(sz(pts) && !belongs(H[i], pts.back()))
            pts.pop_back(), S.pop_back();
        P df = dir(S.front()), di = dir(H[i]);
        if (pts.empty() && df.cross(di) < EPS)
            return vector<P>();
        pts.push_back(lineIntersectSeg(H[i].a, H[i].b,
            S.back().a, S.back().b));
        S.push_back(H[i]);
    }
    #define EXIST (sz(pts) && sz(S))

    while(EXIST && (!belongs(S.back(), pts.front()) ||
        !belongs(S.front(), pts.back()))) {
        while(EXIST && !belongs(S.back(), pts.front()))
            pts.pop_front(), S.pop_front();
        while(EXIST && !belongs(S.front(), pts.back()))
            pts.pop_back(), S.pop_back();
    }

    if(sz(S)) pts.push_back(lineIntersectSeg(S.front().a,
        S.front().b, S.back().a, S.back().b));
    return vector<P>(all(pts));
}

