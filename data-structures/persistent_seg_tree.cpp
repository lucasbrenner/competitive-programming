#include "bits/stdc++.h"
using namespace std;

#define endl '\n'
typedef long long ll;

struct persistent_seg_tree {
    struct node {
        int x;
        int l, r;
        node () : x(0), l(-1), r(-1) {}
        node (int val) : x(val), l(-1), r(-1) {}
    };

    vector<node> nodes;
    int create(int val) {
        nodes.push_back(node(val));
        return (int)nodes.size() - 1;
    }
    int create(int l, int r) {
        nodes.push_back(node());
        nodes.back().l = l, nodes.back().r = r;
        nodes.back().x = nodes[l].x ^ nodes[r].x; // merge
        return (int)nodes.size() - 1;
    }

    vector<int> roots;
    int n;

    persistent_seg_tree(vector<int> &a) : n(a.size()) {
        roots.push_back(build(1, n, a));
    }

    int build(int l, int r, vector<int> &a) {
        if (l == r) return create(a[l - 1]);
        int mid = (l + r) / 2;
        return create(build(l, mid, a), build(mid + 1, r, a));
    }

    int update(int v, int l, int r, int pos, int val) {
        if (l == r) return create(val ^ nodes[v].x); // merge / set
        int mid = (l + r) / 2;
        if (pos <= mid) return create(update(nodes[v].l, l, mid, pos, val), nodes[v].r);
        return create(nodes[v].l, update(nodes[v].r, mid + 1, r, pos, val));
    }

    int query(int v, int l, int r, int lq, int rq) {
        if (lq <= l && r <= rq) return nodes[v].x;
        if (l > rq || r < lq) return 0;
        int mid = (l + r) / 2;
        return query(nodes[v].l, l, mid, lq, rq) ^ query(nodes[v].r, mid + 1, r, lq, rq); // merge
    }

    int fst(int vl, int vr, int l, int r) {
        if (l == r) return l;
        int mid = (l + r) / 2;
        if (nodes[nodes[vr].l].x ^ nodes[nodes[vl].l].x) return fst(nodes[vl].l, nodes[vr].l, l, mid);
        return fst(nodes[vl].r, nodes[vr].r, mid + 1, r);
    }

    // 1-indexed
    void update(int pos, int val) { roots.push_back(update(roots.back(), 1, n, pos, val)); }
    int query(int version, int l, int r) { return query(roots[version], 1, n, l, r); }
    int fst(int l, int r) {
        l--;
        if ((nodes[roots[r]].x ^ nodes[roots[l]].x) == 0) return -1;
        return fst(roots[l], roots[r], 1, n);
    }
};

