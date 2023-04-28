#include "bits/stdc++.h"
using namespace std;

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

