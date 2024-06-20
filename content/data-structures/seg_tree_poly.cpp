#include "../primitives/mint.cpp"

// polynomial's degree + 1
const int K = 4;
Int d2 = Int(1) / 2, d4 = Int(1) / 4, d6 = Int(1) / 6;

// f[i](x) = 0^i + 1^i + ... + x^i
function<Int(ll)> f[] = {
    [](ll x){ return Int(x) + 1; },
    [](ll x){ return Int(x) * (x + 1) * d2; },
    [](ll x){ return Int(x) * (x + 1) * (2 * x + 1) * d6; },
    [](ll x){ return Int(x) * x * (x + 1) * (x + 1) * d4; }
};

using T = array<Int, K>;
// updates polynomial's coefficients from f(x) to f(x + h)
T shift_idx(T a, ll h) {
    Int h2 = Int(h)*h, h3 = h2*h;
    return {
        a[0] + a[1]*h + a[2]*h2 + a[3] * h3,
        a[1] + a[2]*2*h + a[3]*3*h2,
        a[2] + a[3]*3*h,
        a[3]
    };
}

struct seg_tree {
    int n;
    vector<Int> tree;
    vector<T> lazy;

    seg_tree(vector<ll> a) {
        n = a.size();
        tree.resize(n * 4);
        lazy.resize(n * 4);
        build(1, 0, n - 1, a);
    }

    inline int left(int id) { return (id << 1); }
    inline int right(int id) { return (id << 1) | 1; }

    void build(int id, int l, int r, const vector<ll> &a) {
        if (l == r) tree[id] = a[l];
        else {
            int m = (l + r) >> 1;
            build(left(id), l, m, a);
            build(right(id), m + 1, r, a);
            tree[id] = tree[left(id)] + tree[right(id)];
        }
    }

    inline void push(int id, int l, int r) {
        if (lazy[id] == T{}) return;
        rep(i, 0, K) tree[id] += f[i](r - l) * lazy[id][i];

        if (l != r) {
            int mid = (l + r) / 2;
            rep(i, 0, K) lazy[left(id)][i] += lazy[id][i];
            auto nxt = shift_idx(lazy[id], mid - l + 1);
            rep(i, 0, K) lazy[right(id)][i] += nxt[i];
        }
        rep(i, 0, K) lazy[id][i] = 0;
    }

    // add f(i - l) to each i in [l, r]
    void update(int id, int l, int r, int lq, int rq, T val) {
        push(id, l, r);
        if (l > rq || r < lq) return;
        if (lq <= l && r <= rq) {
            rep(i, 0, K) lazy[id][i] += val[i];
            push(id, l, r);
        } else {
            int mid = (l + r) >> 1;
            update(left(id), l, mid, lq, rq, val);
            auto nxt = shift_idx(val, max(0ll, mid - max(l, lq) + 1ll));
            update(right(id), mid + 1, r, lq, rq, nxt);
            tree[id] = tree[left(id)] + tree[right(id)];
        }
    }

    Int query(int id, int l, int r, int lq, int rq) {
        push(id, l, r);
        if (l > rq || r < lq) return 0;
        if (lq <= l && r <= rq) return tree[id];
        int mid = (l + r) >> 1;
        return query(left(id), l, mid, lq, rq) + query(right(id), mid + 1, r, lq, rq);
    }

    void update(int l, int r, T val) { update(1, 0, n - 1, l, r, val); }
    Int query(int l, int r) { return query(1, 0, n - 1, l, r); }
};

