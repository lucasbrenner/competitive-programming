#include "./point.cpp"
//convexhull sem coolinear
vector<pt> convexHull(vector<pt> pts) {
    if (sz(pts) <= 1) return pts;
    sort(all(pts));
    vector<pt> h(sz(pts)+1); //h(2*sz(pts)+2) pra ter colinear
    int s = 0, t = 0;       
    for (int it = 2; it--; s = --t, reverse(all(pts)))
        for (pt p : pts) {               // troca por > 0,coolinear
            while (t >= s + 2 && h[t-2].cross(h[t-1], p) <= 0) t--; 
            h[t++] = p;
        }
    return {h.begin(), h.begin() + t - (t == 2 && h[0] == h[1])};
}

/*Returns the two points with max distance on a convex hull 
(ccw,no duplicate/collinear points) O(N)*/
array<pt, 2> hullDiameter(vector<pt> S) {
    int n = sz(S), j = n < 2 ? 0 : 1;
    pair<ld, array<pt, 2>> res({0, {S[0], S[0]}});
    rep(i,0,j)
        for (;; j = (j + 1) % n) {
            res = max(res, {(S[i] - S[j]).dist2(), {S[i], S[j]}});
            if ((S[(j + 1) % n] - S[j]).cross(S[i + 1] - S[i]) >= 0)
                break;
        }
    return res.second;
}
