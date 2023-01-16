#include "bits/stdc++.h"
using namespace std;

#define endl '\n'
typedef long long ll;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

template<typename T> struct treap {
    struct node {
        int p, rev, cnt;
        int val;
        node *l, *r;
        node(T val_) : p(rng()), rev(0), cnt(1), l(nullptr), r(nullptr) {
            val = val_;
        }
    };
    typedef node* pnode;
    pnode root = nullptr;

    int cnt(pnode t) {
        return t ? t->cnt : 0;
    }
    void recalc(pnode t) {
        if (t) {
            t->cnt = 1 + cnt(t->l) + cnt(t->r);
        }
    }
    void push(pnode t) {
        if (t && t->rev) {
            t->rev = 0;
            swap(t->l, t->r);
            if (t->l) t->l->rev ^= 1;
            if (t->r) t->r->rev ^= 1;
        }
    }

    void split(pnode t, pnode &l, pnode &r, int pos) {
        if (!t) return void(l = r = nullptr);
        push(t);
        if (cnt(t->l) < pos) split(t->r, t->r, r, pos - cnt(t->l) - 1), l = t;
        else split(t->l, l, t->l, pos), r = t;
        recalc(t);
    }

    void merge(pnode &t, pnode a, pnode b) {
        push(a), push(b);
        if (!a || !b) return void(t = a ? a : b);
        if (a->p > b->p) merge(a->r, a->r, b), t = a;
        else merge(b->l, a, b->l), t = b;
        recalc(t);
    }

    void insert(T val, int pos) {
        pnode a, b;
        split(root, a, b, pos);
        merge(a, a, new node(val));
        merge(root, a, b);
    }

    void erase(pnode &t, int pos) {
        if (cnt(t->l) == pos) {
            pnode tmp = t;
            merge(t, t->l, t->r);
            delete tmp;
        }
        else if (cnt(t->l) < pos) erase(t->r, pos - cnt(t->l) - 1);
        else erase(t->l, pos);
        recalc(t);
    }
    void erase(int pos) { erase(root, pos); }

    void reverse(pnode &t, int l, int r) {
        if (l >= r) return;
        pnode a, b, c;
        split(root, a, b, l);
        split(b, b, c, r - l + 1);
        b->rev ^= 1;
        merge(root, a, b);
        merge(root, root, c);
    }
    void reverse(int l, int r) { reverse(root, l, r); }

    void swap_ranges(int l1, int r1, int l2, int r2) {
        pnode a, b, c, d, e;
        split(root, a, b, l1);
        split(b, b, c, r1 - l1 + 1);
        split(c, c, d, l2 - r1 - 1);
        split(d, d, e, r2 - l2 + 1);
        merge(root, a, d);
        merge(root, root, c);
        merge(root, root, b);
        merge(root, root, e);
    }

    int get(int l, int r) {
        pnode a, b, c;
        split(root, a, b, l);
        split(b, b, c, r - l + 1);
        int ans = b->val;
        merge(root, a, b);
        merge(root, root, c);
        return ans;
    }

    treap() {}
    treap(vector<T> &a) {
        root = nullptr;
        for (int i = 0; i < a.size(); i++) {
            insert(a[i], i);
        }
    }

    void print(pnode t) {
        if (!t) return;
        push(t);
        print(t->l);
        cout << t->val << " ";
        print(t->r);
    }
    void print() { print(root); cout << endl; }
};

