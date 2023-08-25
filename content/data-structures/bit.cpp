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
};

