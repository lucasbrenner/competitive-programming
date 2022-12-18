#include <bits/stdc++.h>
using namespace std;

struct sptable {
    vector<vector<int>> t;

    sptable(const vector<int> &a) {
        int n = a.size(), lg = __builtin_clz(1) - __builtin_clz(n);
        t = vector<vector<int>>(lg + 1, vector<int>(n));
        for (int i = 0; i < n; i++) t[0][i] = a[i];
        for (int i = 1; (1 << i) <= n; i++) for (int j = 0; j + (1 << i) <= n; j++)
            t[i][j] = min(t[i - 1][j], t[i - 1][j + (1 << (i - 1))]);
    }

    int query(int l, int r) {
        if (l > r) swap(l, r);
        int lg = __builtin_clz(1) - __builtin_clz(r - l + 1);
        return min(t[lg][l], t[lg][r - (1 << lg) + 1]);
    }
};

