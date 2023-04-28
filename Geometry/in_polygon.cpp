#include "bits/stdc++.h"
using namespace std;

#include "./point.cpp"
typedef long long ll;

template<class T> bool in_polygon(vector<T> &a, T p, bool strict = true) {
    int ans = 0, n = a.size();
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        if (on_segment(a[i], a[j], p)) return !strict;
        ans ^= ((p.y < a[i].y) - (p.y < a[j].y)) * p.cross(a[i], a[j]) > 0;
    }
    return ans;
}

