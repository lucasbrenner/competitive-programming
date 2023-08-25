//https://codeforces.com/blog/entry/58747
#include "./point.cpp"
typedef long long ll;

pair<pt, pt> closest(vector<pt> v) {
    assert(sz(v) > 1);
    set<pt> S; //change LLONG_MAX if is double
    sort(all(v), [](pt a, pt b) { return a.y < b.y; });
    pair<ll, pair<pt, pt>> ret{LLONG_MAX, {pt(), pt()}}; 
    int j = 0;
    for (pt p : v) {
        pt d{1 + (ll)sqrt(ret.first), 0};
        while (v[j].y <= p.y - d.x) S.erase(v[j++]);
        auto lo = S.lower_bound(p - d), hi = S.upper_bound(p + d);
        for (; lo != hi; ++lo)
            ret = min(ret, {(*lo - p).dist2(), {*lo, p}});
        S.insert(p);
    }
    return ret.second;
}
