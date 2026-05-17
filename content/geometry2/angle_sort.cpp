#include "point.cpp"

typedef Point<ll> P;
int half(P p) {
    return p.y > 0 || (p.y == 0 && p.x >= 0);
}

bool cmp(P a, P b) {
    int ha = half(a), hb = half(b);
    if(ha != hb) return ha > hb;

    ll cr = a.cross(b);
    if(cr != 0) return cr > 0;

    return a.dist2() < b.dist2();
}
