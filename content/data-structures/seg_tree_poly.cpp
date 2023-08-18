#include "../contest/template.cpp"

const ll mod = 1e9 + 7;

// polynomial's degree + 1
const int K = 3;

// f[i](x) = 0^i + 1^i + ... + x^i
function<ll(ll)> f[] = {
    [](ll x){ return x + 1; },
    [](ll x){ return (x * (x + 1) / 2) % mod; },
    [](ll x){ return (x * (x + 1) * (2 * x + 1) / 6) % mod; }
};

// updates polynomial's coefficients from f(x) to f(x + h)
array<ll, K> shift_idx(array<ll, K> a, ll h) {
    array<ll, K> ans = {
        (((a[2] * h % mod) * h % mod + a[1] * h + a[0]) % mod + mod) % mod,
        ((a[2] * 2 * h + a[1]) % mod + mod) % mod,
        a[2]
    };
    return ans;
}

void norm(ll &x) {
    x %= mod;
    if (x < 0) x += mod;
}

struct seg_tree {
    struct node {
        ll sum;
        node() : sum(0) {}
        node(ll x) : sum(x) {}
        node operator + (const node &o) const {
            return node((sum + o.sum) % mod);
        }
    };

    int n;
    vector<node> tree;
    vector<array<ll, K>> lazy;

    seg_tree(vector<ll> a) {
        n = a.size();
        tree.resize(n * 4);
        lazy.resize(n * 4);
        build(1, 0, n - 1, a);
    }

    inline int left(int id) { return (id << 1); }
    inline int right(int id) { return (id << 1) | 1; }

    void build(int id, int l, int r, const vector<ll> &a) {
        if (l == r) tree[id] = node(a[l]);
        else {
            int m = (l + r) >> 1;
            build(left(id), l, m, a);
            build(right(id), m + 1, r, a);
            tree[id] = tree[left(id)] + tree[right(id)];
        }
    }

    inline void push(int id, int l, int r) {
        if (lazy[id] == array<ll, K>{}) return;
        for (int i = 0; i < K; i++) norm(tree[id].sum += f[i](r - l) * lazy[id][i]);

        if (l != r) {
            int mid = (l + r) / 2;
            for (int i = 0; i < K; i++) norm(lazy[left(id)][i] += lazy[id][i]);
            auto nxt = shift_idx(lazy[id], mid - l + 1);
            for (int i = 0; i < K; i++) norm(lazy[right(id)][i] += nxt[i]);
        }
        for (int i = 0; i < K; i++) lazy[id][i] = 0;
    }

    // add f(i - l) to each i in [l, r]
    void update(int id, int l, int r, int lq, int rq, array<ll, K> val) {
        push(id, l, r);
        if (l > rq || r < lq) return;
        if (lq <= l && r <= rq) {
            for (int i = 0; i < K; i++) norm(lazy[id][i] += val[i]);
            push(id, l, r);
        } else {
            int mid = (l + r) >> 1;
            update(left(id), l, mid, lq, rq, val);
            auto nxt = shift_idx(val, max(0ll, mid - max(l, lq) + 1ll));
            update(right(id), mid + 1, r, lq, rq, nxt);
            tree[id] = tree[left(id)] + tree[right(id)];
        }
    }

    node query(int id, int l, int r, int lq, int rq) {
        push(id, l, r);
        if (l > rq || r < lq) return node();
        if (lq <= l && r <= rq) return tree[id];
        int mid = (l + r) >> 1;
        return query(left(id), l, mid, lq, rq) + query(right(id), mid + 1, r, lq, rq);
    }

    void update(int l, int r, array<ll, K> val) { update(1, 0, n - 1, l, r, val); }
    node query(int l, int r) { return query(1, 0, n - 1, l, r); }
};

