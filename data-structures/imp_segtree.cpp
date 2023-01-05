#include "bits/stdc++.h"
using namespace std;

#define endl '\n'
typedef long long ll;

struct imp_segtree {
    struct node {
        int x;
        node *l, *r;
        node (int val) : x(val), l(nullptr), r(nullptr) {}
        node (node *a, node *b) : l(a), r(b){
            x = a->x ^ b->x; // merge
        }
    };

    vector<node*> roots;
    int n;

    imp_segtree(vector<int> &a) : n(a.size()) {
        roots.push_back(build(1, n, a));
    }

    node* build(int l, int r, vector<int> &a) {
        if (l == r) return new node(a[l - 1]);
        int mid = (l + r) / 2;
        return new node(build(l, mid, a), build(mid + 1, r, a));
    }

    node* update(node *v, int l, int r, int pos, int val) {
        if (l == r) return new node(val ^ v->x); // merge / set
        int mid = (l + r) / 2;
        if (pos <= mid) return new node(update(v->l, l, mid, pos, val), v->r);
        return new node(v->l, update(v->r, mid + 1, r, pos, val));
    }

    int query(node *v, int l, int r, int lq, int rq) {
        if (lq <= l && r <= rq) return v->x;
        if (l > rq || r < lq) return 0;
        int mid = (l + r) / 2;
        return query(v->l, l, mid, lq, rq) ^ query(v->r, mid + 1, r, lq, rq); // merge
    }

    // first non-zero xor
    int fst(node *vl, node *vr, int l, int r) {
        if (l == r) return l;
        int mid = (l + r) / 2;
        if (vr->l->x ^ vl->l->x) return fst(vl->l, vr->l, l, mid);
        return fst(vl->r, vr->r, mid + 1, r);
    }

    // 1-indexed
    void update(int pos, int val) { roots.push_back(update(roots.back(), 1, n, pos, val)); }
    int query(int version, int l, int r) { return query(roots[version], 1, n, l, r); }
    int fst(int l, int r) {
        l--;
        if ((roots[r]->x ^ roots[l]->x) == 0) return -1;
        return fst(roots[l], roots[r], 1, n);
    }
};

