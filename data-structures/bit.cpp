#include "bits/stdc++.h"
using namespace std;

template<typename T>
struct bit {
    int n;
    vector<T> a;

    bit(int _n) {
        a.resize(_n + 1);
        n = _n;
    }

    void add(int pos, T x) {
        for (; pos <= n; pos += (pos & -pos)) a[pos] += x;
    }

    T query(int pos) {
        T ans = 0;
        for (; pos > 0; pos -= (pos & -pos)) ans += a[pos];
        return ans;
    }

    T query(int l, int r) {
        return query(r) - query(l - 1);
    }
};

