#include "../contest/template.cpp"

template<class T> struct seg_tree {
    struct node {
        T x = LLONG_MAX;
        const node operator + (const node& o) const {
            node ans;
            ans.x = min(o.x, x);
            return ans;
        }
    };
    int n;
    vector<node> tree;
    seg_tree(int n) : n(n), tree(n * 2) {}
    void update(int i, int f) {
        i += n;
        tree[i].x = f;
        for (i >>= 1; i >= 1; i >>= 1) tree[i] = tree[i * 2] + tree[i * 2 + 1];
    }
    T query(int a, int b) {
        node esq;
        node dir;
        for (a += n, b += n; a <= b; a >>= 1, b >>= 1) {
            if (a % 2) esq = esq + tree[a++];
            if (b % 2 == 0) dir = tree[b--] + dir;
        }
        return (esq + dir).x;
    }
};

