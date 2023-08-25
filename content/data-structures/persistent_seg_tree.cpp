#include "../contest/template.cpp"
// 1-indexed

struct seg_tree {
    struct node {
        int x, l, r;
        node () : l(-1), r(-1), x(0) {}
        node (int val) : l(-1), r(-1), x(val) {}
        node operator + (const node &oth) const {
            return node(x + oth.x);
        }
    };

    vector<node> nodes;
    vector<int> roots;
    int n;

    int create(int val) {
        nodes.push_back(node(val));
        return (int)nodes.size() - 1;
    }
    int create(int l, int r) {
        nodes.push_back(nodes[l] + nodes[r]);
        nodes.back().l = l, nodes.back().r = r;
        return (int)nodes.size() - 1;
    }
    seg_tree(vector<int> a) : n(a.size()) {
        roots.push_back(build(1, n, a));
    }
    int build(int l, int r, vector<int> &a) {
        if (l == r) return create(a[l - 1]);
        int mid = (l + r) / 2;
        return create(build(l, mid, a), build(mid + 1, r, a));
    }
    int update(int l, int r, int pos, int val, int v) {
        if (l == r) return create(val + nodes[v].x); // add / set
        int mid = (l + r) / 2;
        if (pos <= mid) return create(update(l, mid, pos, val, nodes[v].l), nodes[v].r);
        return create(nodes[v].l, update(mid + 1, r, pos, val, nodes[v].r));
    }
    node query(int l, int r, int lq, int rq, int v) {
        if (lq <= l && r <= rq) return nodes[v];
        if (l > rq || r < lq) return node();
        int mid = (l + r) / 2;
        return query(l, mid, lq, rq, nodes[v].l) + query(mid + 1, r, lq, rq, nodes[v].r);
    }
    void update(int pos, int val, int version = -1) {
        version = (version == -1 ? roots.back() : roots[version]);
        roots.push_back(update(1, n, pos, val, version));
    }
    node query(int l, int r, int version) { return query(1, n, l, r, roots[version]); }
};


