#include "../contest/template.cpp"

const ll inf = 1e18;
template<class T> struct seg_tree {
    struct node {
        T x;
        node() : x(-inf) {}
        node(T x) : x(x) {}
        node operator+(const node &o) const {
            return node(max(x, o.x));
        }
    };
    int n;
    vector<node> tree;
    vector<T> lazy;
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
        if (lazy[id]) {
            tree[id].x += lazy[id];
            if (l != r) {
                lazy[left(id)] += lazy[id];
                lazy[right(id)] += lazy[id];
            }
            lazy[id] = 0;
        }
    }
    void update(int id, int l, int r, int lq, int rq, T val) {
        push(id, l, r);
        if (l > rq || r < lq) return;
        if (lq <= l && r <= rq) {
            lazy[id] += val;
            push(id, l, r);
        } else {
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

