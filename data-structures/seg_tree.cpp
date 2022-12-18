#include <bits/stdc++.h>
using namespace std;

struct node {
    long long val;
    node() {
        val = 0;
    }
    node(long long x) {
        val = x;
    }
    node operator+(const node &o) const {
        node ans;
        ans.val = val + o.val;
        return ans;
    }
};
 
template<class i_t, class e_t>
struct seg_tree{
    int n;
    vector<i_t> tree;

    seg_tree(const vector<e_t> &a) {
        n = a.size();
        tree.resize(n * 4);
        build(1, 1, n, a);
    }

    void build(int id, int l, int r, const vector<e_t> &a) {
        if (l == r) tree[id] = i_t(a[l - 1]);
        else {
            int m = (l + r)>>1;
            build(id<<1, l, m, a);
            build(id<<1|1, m + 1, r, a);
            tree[id] = tree[id<<1] + tree[id<<1|1];
        }
    }

    void update(int id, int l, int r, int pos, e_t val) {
        if (l == r) tree[id] = i_t(val) + tree[id]; // merge / set
        else{
            int m = (l + r)>>1;
            if (pos <= m) update(id<<1, l, m, pos, val);
            else update(id<<1|1, m + 1, r, pos, val);
            tree[id] = tree[id<<1] + tree[id<<1|1];
        }
    }

    i_t query(int id, int l, int r, int lq, int rq) {
        if (l > rq || r < lq) return i_t();
        else if (lq <= l && r <= rq) return tree[id];
        else{
            int m = (l + r)>>1;
            return query(id<<1, l, m, lq, rq) + query(id<<1|1, m + 1, r, lq, rq);
        }
    }
    void update(int pos, e_t val) { update(1, 1, n, pos, val); }
    i_t query(int l, int r) { return query(1, 1, n, l, r); }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, q; cin >> n >> q;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    seg_tree<node, long long> stree(a);

    while(q--){
        long long tp, x, y; cin >> tp >> x >> y;
        if (tp == 0) stree.update(1, 1, n, x + 1, y);
        else cout << stree.query(1, 1, n, x + 1, y).val << '\n';
    }
}
