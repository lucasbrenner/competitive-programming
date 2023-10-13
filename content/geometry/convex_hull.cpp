#include "./point.cpp"

template<class T> vector<T> convex_hull(vector<T> a, bool ic) {
    if (a.size() <= 1) return a;
    sort(a.begin(), a.end());
    vector<T> ans((int)a.size() + 1);
    int s = 0, t = 0, it = 2;
    for (; it--; s = --t, reverse(a.begin(), a.end())) {
        for (T p : a) {
            while (t - 2 >= s && ans[t - 2].ori(ans[t - 1], p) + ic <= 0) t--;
            ans[t++] = p;
        }
        if (ic && t == (int)a.size()) return a;
    }
    ans.resize(t - (t == 2 && ans[0] == ans[1]));
    return ans;
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