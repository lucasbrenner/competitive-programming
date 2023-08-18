// https://codeforces.com/blog/entry/58747
#include "bits/stdc++.h"
using namespace std;

#include "./point.cpp"
typedef long long ll;

typedef pt<ll> P;
pair<P, P> closest_pair(vector<P> a) {
    pair<ll, pair<P, P>> ans = { (ll)8e18, {P(), P()} };
    sort(a.begin(), a.end(), [](auto &x, auto &y) { return x.y < y.y; });
    set<P> s;
    for (int i = 0, j = 0; i < (int)a.size(); i++) {
        P d(1 + sqrt(ans.first), 0);
        while (a[i].y - a[j].y >= d.x) s.erase(a[j++]);
        auto l = s.lower_bound(a[i] - d), r = s.upper_bound(a[i] + d);
        for (auto it = l; it != r; it++) {
            ans = min(ans, {(*it - a[i]).dist(), { *it, a[i] }});
        }
        s.insert(a[i]);
    }
    return ans.second;
}

