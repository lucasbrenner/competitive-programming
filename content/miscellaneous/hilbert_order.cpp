#include "../contest/template.cpp"

const int rot_delta[4] = { 3, 0, 0, 1 };
inline ll hilbert_order(int x, int y, int bit, int rot) {
    if (bit == 0) return 0;
    int hbit = 1 << (bit - 1);
    int seg = (x < hbit) ? ((y < hbit) ? 0 : 3) : ((y < hbit) ? 1 : 2);
    seg = (seg + rot) & 3;
    int nx = x & (x ^ hbit), ny = y & (y ^ hbit);
    int nrot = (rot+ rot_delta[seg]) & 3;
    ll ssize = 1LL << (2 * bit - 2);
    ll ans = seg * ssize;
    ll add = hilbert_order(nx, ny, bit - 1, nrot);
    ans += (seg == 1 || seg == 2) ? add : (ssize - add - 1);
    return ans;
}

struct query {
    int l, r, idx;
    ll ord;
    void init() {
        ord = hilbert_order(l, r, 21, 0);
    }
    bool operator < (const query &other) const {
        return ord < other.ord;
    }
};

