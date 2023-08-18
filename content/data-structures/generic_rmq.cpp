#include "bits/stdc++.h"
using namespace std;

template<typename T, auto op> struct rmq {
    vector<vector<T>> t;

    rmq(const vector<T> &a) {
        int n = a.size(), lg = 31 - __builtin_clz(n);
        t = vector<vector<T>>(lg + 1, vector<T>(n));
        for (int i = 0; i < n; i++) t[0][i] = a[i];
        for (int i = 1; (1 << i) <= n; i++) {
            for (int j = 0; j + (1 << i) <= n; j++) {
                t[i][j] = op(t[i - 1][j], t[i - 1][j + (1 << (i - 1))]);
            }
        }
    }

    T query(int l, int r) {
        if (l > r) swap(l, r);
        int lg = 31 - __builtin_clz(r - l + 1);
        return op(t[lg][l], t[lg][r - (1 << lg) + 1]);
    }
};

int main() {
    rmq<int, [](int x, int y) { return min(x, y); }> a({4, 7, 9});
    cout << a.query(1, 2) << endl; // 7
}

