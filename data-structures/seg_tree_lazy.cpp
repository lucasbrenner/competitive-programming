#include "bits/stdc++.h"
using namespace std;

#define endl '\n'
typedef long long ll;

template<class T>
struct seg_tree {
    struct node {
        ll x;

        node() : x(0) {}
        node(ll x) : x(x) {}

        node operator+(const node &o) const {
            return node(x + o.x);
        }
    };

    struct lazy_node {
        ll x;

        lazy_node() : x(0) {}
    };

    int n;
    vector<node> tree;
    vector<lazy_node> lazy;

    seg_tree(vector<T> a) {
        n = a.size();
        tree.resize(n * 4);
        lazy.resize(n * 4);
        build(1, 0, n - 1, a);
    }

    inline int left(int id) { return (id << 1); }
    inline int right(int id) { return (id << 1) | 1; }

    void build(int id, int l, int r, const vector<T> &a) {
        if (l == r) tree[id] = node(a[l]);
        else {
            int m = (l + r) >> 1;
            build(left(id), l, m, a);
            build(right(id), m + 1, r, a);
            tree[id] = tree[left(id)] + tree[right(id)];
        }
    }

    inline void push(int id, int l, int r) {
        if (!lazy[id].x) return;

        tree[id].x += (r - l + 1ll) * lazy[id].x;

        if (l != r) {
            lazy[left(id)].x += lazy[id].x;
            lazy[right(id)].x += lazy[id].x;
        }
        lazy[id].x = 0;
    }

    void update(int id, int l, int r, int lq, int rq, T val) {
        if (l > rq || r < lq) return;
        if (lq <= l && r <= rq) {
            lazy[id].x += val;
            push(id, l, r);
        } else {
            push(id, l, r);
            int mid = (l + r) >> 1;
            update(left(id), l, mid, lq, rq, val);
            update(right(id), mid + 1, r, lq, rq, val);
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

    void update(int l, int r, T val) { update(1, 0, n - 1, l, r, val); }
    node query(int l, int r) { return query(1, 0, n - 1, l, r); }
};

void solvetask() {
    int n, q; cin >> n >> q;

    seg_tree<ll> s((vector<ll>(n)));

    while (q--) {
        int tp; cin >> tp;
        if (tp == 1) {
            int l, r, v; cin >> l >> r >> v;
            s.update(l, r - 1, v);
        } else {
            int pos; cin >> pos;
            cout << s.query(pos, pos).x << endl;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t = 1;
    while(t--) solvetask();
}
