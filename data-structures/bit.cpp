#include <bits/stdc++.h>
using namespace std;

struct bit {
    int n;
    vector<int> a;

    bit(int _n) {
        a.resize(_n + 1);
        n = _n;
    }

    void add(int pos, int x) {
        for (; pos <= n; pos += (pos & -pos)) a[pos] += x;
    }

    int query(int pos) {
        int ans = 0;
        for (; pos > 0; pos -= (pos & -pos)) ans += a[pos];
        return ans;
    }

    int query(int l, int r) {
        return query(r) - query(l - 1);
    }
};

