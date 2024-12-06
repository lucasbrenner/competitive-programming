#include "../contest/template.cpp"

template<typename T> struct bit {
    int n;
    vector<T> a;
    bit(int n) : n(n), a(n + 1) {}
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
    // min R such that a[1] + a[2] + ... + a[R] >= x, -1 if there's no valid R
    int min_right(T x) {
        int ans = -1, i = 31 - __builtin_clz(n), ac = 0;
        for (T cur = 0; i >= 0; i--) if (ac + (1 << i) <= n) {
            if (cur + a[(1 << i) + ac] >= x) ans = (1 << i) + ac;
            else ac += (1 << i), cur += a[ac];
        }
        return ans;
    }
    // max R such that a[1] + a[2] + ... + a[R] <= x. -1 if there's no valid R
    int max_right(T x) {
        int i = 31 - __builtin_clz(n), ac = 0;
        for (T cur = 0; i >= 0; i--) {
            if (ac + (1 << i) <= n && cur + a[(1 << i) + ac] <= x)
                ac += (1 << i), cur += a[ac];
        }
        return ac - (ac == 0);
    }
};

