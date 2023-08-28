#include "../contest/template.cpp"

inline ll hilbert_order(int x, int y) {
    int bit = 20;
    ll res = 0;
    for (int n = 1 << bit, s = n >> 1; s; s >>= 1) {
        int rotate_x = (x & s) ? 1 : 0;
        int rotate_y = (y & s) ? 1 : 0;
        res += ((rotate_x) ^ (rotate_y * 3LL)) * s * s;
        if (rotate_x) continue;
        if (rotate_y) {
            x = n - 1 - x;
            y = n - 1 - y;
        }
        swap(x, y);
    }
    return res;
}

struct query {
    int l, r, idx;
    ll ord;
    void init() {
        ord = hilbert_order(l, r);
    }
    bool operator < (const query &other) const {
        return ord < other.ord;
    }
};

