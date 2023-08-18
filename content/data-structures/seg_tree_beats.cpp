// tested on https://atcoder.jp/contests/abc256/tasks/abc256_h
// O(Q * logN * logA)
#include "bits/stdc++.h"
using namespace std;

#define endl '\n'
#define all(x) (x).begin(), (x).end()
typedef long long ll;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

template<class T> struct seg_tree {
    struct node {
        ll sum, al, eq;
        node() {
            sum = al = 0;
            eq = -1;
        }
        node(ll x) {
            sum = al = x;
            eq = 1;
        }

        node operator + (const node &o) const {
            node ans;
            if (eq == -1) {
                ans.sum = o.sum;
                ans.al = o.al;
                ans.eq = o.eq;
            } else if (o.eq == -1) {
                ans.sum = sum;
                ans.al = al;
                ans.eq = eq;
            } else {
                ans.sum = sum + o.sum;
                ans.al = al;
                ans.eq = eq && o.eq && al == o.al;
            }
            return ans;
        }
    };
    struct lazy_node {
        ll set;
        lazy_node() : set(-1) {}
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
        if (lazy[id].set == -1) return;

        tree[id].sum = (r - l + 1) * lazy[id].set;
        tree[id].al = lazy[id].set;
        if (l != r) {
            lazy[left(id)].set = lazy[id].set;
            lazy[right(id)].set = lazy[id].set;
        }
        lazy[id].set = -1;
    }

    void update(int id, int l, int r, int lq, int rq, T val) {
        push(id, l, r);
        if (l > rq || r < lq) return;
        if (lq <= l && r <= rq) {
            lazy[id].set = val;
            push(id, l, r);
        } else {
            int mid = (l + r) >> 1;
            update(left(id), l, mid, lq, rq, val);
            update(right(id), mid + 1, r, lq, rq, val);
            tree[id] = tree[left(id)] + tree[right(id)];
        }
    }

    void update_div(int id, int l, int r, int lq, int rq, int x) {
        push(id, l, r);
        if (l > rq || r < lq) return;
        if (tree[id].eq && tree[id].al == 0) return;

        if (lq <= l && r <= rq && tree[id].eq) {
            lazy[id].set = tree[id].al / x;
            push(id, l, r);
        } else {
            int mid = (l + r) >> 1;
            update_div(left(id), l, mid, lq, rq, x);
            update_div(right(id), mid + 1, r, lq, rq, x);
            tree[id] = tree[left(id)] + tree[right(id)];
        }
    }

    node query(int id, int l, int r, int lq, int rq) {
        push(id, l, r);
        if (l > rq || r < lq) return node();
        if (lq <= l && r <= rq) return tree[id];
        int mid = (l + r) >> 1;
        auto xx = query(left(id), l, mid, lq, rq) + query(right(id), mid + 1, r, lq, rq);
        return xx;
    }

    // update each a_i in [l, r] to val
    void update(int l, int r, T val) { update(1, 0, n - 1, l, r, val); }
    // update each a_i in [l, r] to floor(a_i / x)
    void update_div(int l, int r, int x) { update_div(1, 0, n - 1, l, r, x); }
    node query(int l, int r) { return query(1, 0, n - 1, l, r); }
};

void solvetask() {
    int n, q; cin >> n >> q;
    vector<ll> a(n);
    for (ll &x : a) cin >> x;

    seg_tree<ll> s(a);

    while (q--) {
        int tp, l, r; cin >> tp >> l >> r;
        l--, r--;
        if (tp == 1) {
            int x; cin >> x;
            s.update_div(l, r, x);
        } else if (tp == 2) {
            int x; cin >> x;
            s.update(l, r, x);
        } else {
            cout << s.query(l, r).sum << endl;
        }
    }
}
 
int main() {
    cin.tie(0)->sync_with_stdio(0);
    int tc = 1;
    while(tc--) solvetask();
}

