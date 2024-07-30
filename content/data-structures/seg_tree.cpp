#include "../contest/template.cpp"

template<class T> struct seg_tree {
    struct node {
        T x;
        node() : x(0) {}
        node(T x) : x(x) {}
        node operator + (const node &o) const {
            return node(x + o.x);
        }
    };
    int n;
    vector<node> tree;
    seg_tree(int n) : n(n), tree(n * 4) {}

    inline int left(int id) { return (id << 1); }
    inline int right(int id) { return (id << 1) | 1; }

    void set(int id, int l, int r, int pos, T val) {
        if (l == r) tree[id] = node(val);
        else {
            int mid = (l + r) >> 1;
            if (pos <= mid) set(left(id), l, mid, pos, val);
            else set(right(id), mid + 1, r, pos, val);
            tree[id] = tree[left(id)] + tree[right(id)];
        }
    }

    node query(int id, int l, int r, int lq, int rq) {
        if (l > rq || r < lq) return node();
        if (lq <= l && r <= rq) return tree[id];
        int mid = (l + r) >> 1;
        return query(left(id), l, mid, lq, rq) + query(right(id), mid + 1, r, lq, rq);
    }

    template<typename F>
    bool first_left(int id, int l, int r, int L, F f, node &cur, int &ans) {
        if (r < L) return false;
        int mid = (l + r) / 2;
        if (L <= l) {
            auto new_cur = cur + tree[id];
            if (!f(new_cur)) {
                cur = new_cur;
                return false;
            }
            ans = r;
            if (l != r) {
                new_cur = cur + tree[left(id)];
                if (!f(new_cur)) {
                    cur = new_cur;
                    first_left(right(id), mid + 1, r, L, f, cur, ans);
                } else {
                    first_left(left(id), l, mid, L, f, cur, ans);
                }
            }
            return true;
        } else {
            if (first_left(left(id), l, mid, L, f, cur, ans)) return true;
            return first_left(right(id), mid + 1, r, L, f, cur, ans);
        }
    }
    // first R such that f(a[L] + a[L + 1] + ... + a[R]) is true
    template<typename F>
    int first_left(int L, F f) {
        int ans = -1;
        node aux;
        first_left(1, 0, n - 1, L, f, aux, ans);
        return ans;
    }

    void set(int pos, T val) { set(1, 0, n - 1, pos, val); }
    node query(int l, int r) { return query(1, 0, n - 1, l, r); }
};

