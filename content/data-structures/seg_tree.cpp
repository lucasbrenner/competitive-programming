#include "bits/stdc++.h"
using namespace std;

#define endl '\n'
typedef long long ll;

template<class T> struct seg_tree {
    struct node {
        ll x;
        node() : x(0) {}
        node(T x) : x(x) {}

        node operator + (const node &o) const {
            return node(x + o.x);
        }
    };
    int n;
    vector<node> tree;
    seg_tree(int n_) : n(n_), tree(n * 4) {}

    inline int left(int id) { return (id << 1); }
    inline int right(int id) { return (id << 1) | 1; }

    void update(int id, int l, int r, int pos, T val) {
        if (l == r) tree[id] = node(val);
        else {
            int mid = (l + r) >> 1;
            if (pos <= mid) update(left(id), l, mid, pos, val);
            else update(right(id), mid + 1, r, pos, val);
            tree[id] = tree[left(id)] + tree[right(id)];
        }
    }

    node query(int id, int l, int r, int lq, int rq) {
        if (l > rq || r < lq) return node();
        if (lq <= l && r <= rq) return tree[id];
        int mid = (l + r) >> 1;
        return query(left(id), l, mid, lq, rq) + query(right(id), mid + 1, r, lq, rq);
    }

    void update(int pos, T val) { update(1, 0, n - 1, pos, val); }
    node query(int l, int r) { return query(1, 0, n - 1, l, r); }
};

void solvetask() {
    int n, q; cin >> n >> q;

    seg_tree<ll> s(n);
    for (int i = 0; i < n; i++) {
        ll x; cin >> x;
        s.update(i, x);
    }

    while (q--) {
        int tp; cin >> tp;
        if (tp == 1) {
            int i, v; cin >> i >> v;
            s.update(i, v);
        } else {
            int l, r; cin >> l >> r;
            cout << s.query(l, r - 1).x << endl;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t = 1;
    while(t--) solvetask();
}

