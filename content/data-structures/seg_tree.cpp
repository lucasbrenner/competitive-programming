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

    // min R such that f(a[L] + a[L + 1] + ... + a[R]) is true
    template<typename F>
    int min_right(int L, F f) {
        int ans = -1;
        node cur;
        auto go = [&](auto &&self, int id, int l, int r, int L) -> bool {
            if (r < L) return false;
            int mid = (l + r) / 2;
            if (L <= l) {
                auto new_cur = cur + tree[id];
                if (!f(new_cur)) return (cur = new_cur), false;
                ans = r;
                if (l != r) {
                    new_cur = cur + tree[left(id)];
                    if (!f(new_cur)) cur = new_cur, self(self, right(id), mid + 1, r, L);
                    else self(self, left(id), l, mid, L);
                }
                return true;
            }
            if (self(self, left(id), l, mid, L)) return true;
            return self(self, right(id), mid + 1, r, L);
        };
        go(go, 1, 0, n - 1, L);
        return ans;
    }

    // max L such that f(a[L] + a[L + 1] + ... + a[R]) is true
    template<typename F>
    int max_left(int R, F f) {
        int ans = -1;
        node cur;
        auto go = [&](auto &&self, int id, int l, int r, int R) -> bool {
            if (l > R) return false;
            int mid = (l + r) / 2;
            if (r <= R) {
                auto new_cur = tree[id] + cur;
                if (!f(new_cur)) return (cur = new_cur), false;
                ans = l;
                if (l != r) {
                    new_cur = tree[right(id)] + cur;
                    if (!f(new_cur)) cur = new_cur, self(self, left(id), l, mid, R);
                    else self(self, right(id), mid + 1, r, R);
                }
                return true;
            }
            if (self(self, right(id), mid + 1, r, R)) return true;
            return self(self, left(id), l, mid, R);
        };
        go(go, 1, 0, n - 1, R);
        return ans;
    }

    void set(int pos, T val) { set(1, 0, n - 1, pos, val); }
    node query(int l, int r) { return query(1, 0, n - 1, l, r); }
};

