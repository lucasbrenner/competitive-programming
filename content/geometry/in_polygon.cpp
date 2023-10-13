// https://victorlecomte.com/cp-geo.pdf
#include "./point.cpp"

bool in_polygon(vector<pt> &a, pt p, bool strict = true) {
    int ans = 0, n = a.size();
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        if (onSegment(a[i], a[j], p)) return !strict;
        ans ^= ((p.y < a[i].y) - (p.y < a[j].y)) * p.cross(a[i], a[j]) > 0;
    }
    return ans;
}
