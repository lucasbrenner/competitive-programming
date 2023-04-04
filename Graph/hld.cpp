// tested at https://cses.fi/problemset/task/2134/
// based on https://github.com/kth-competitive-programming/kactl/blob/main/content/graph/HLD.h
#include "bits/stdc++.h"
using namespace std;

#define endl '\n'
typedef long long ll;
mt19937 rng((int) chrono::steady_clock::now().time_since_epoch().count());

template<class T> struct seg_tree {
    struct node {
        int x;
        node() : x(0) {}
        node(ll x) : x(x) {}

        node operator + (const node &o) const {
            return node(max(x, o.x));
        }
    };
    int n;
    vector<node> tree;
    seg_tree(int n_) : n(n_), tree(n * 4) {}

    inline int left(int id) { return (id << 1); }
    inline int right(int id) { return (id << 1) | 1; }

    void update(int id, int l, int r, int pos, T val) {
        if (l == r) tree[id] = node(val);
        else {
            int mid = (l + r) >> 1;
            if (pos <= mid) update(left(id), l, mid, pos, val);
            else update(right(id), mid + 1, r, pos, val);
            tree[id] = tree[left(id)] + tree[right(id)];
        }
    }

    node query(int id, int l, int r, int lq, int rq) {
        if (l > rq || r < lq) return node();
        if (lq <= l && r <= rq) return tree[id];
        int mid = (l + r) >> 1;
        return query(left(id), l, mid, lq, rq) + query(right(id), mid + 1, r, lq, rq);
    }

    void update(int pos, T val) { update(1, 0, n - 1, pos, val); }
    node query(int l, int r) { return query(1, 0, n - 1, l, r); }
};

template<bool EDGES> struct hld {
    int n, cnt = 0;
    vector<vector<int>> adj;
    vector<int> pr, sz, dep, tp, idx;
    seg_tree<int> tree;
    hld(vector<vector<int>> adj_)
        : adj(adj_), n(adj_.size()), pr(n, -1), sz(n, 1), dep(n),
        tp(n), idx(n), tree(n) {
        dfs_sz(0);
        dfs(0);
    }
    void dfs_sz(int v) {
        if (pr[v] != -1) adj[v].erase(find(adj[v].begin(), adj[v].end(), pr[v]));
        for (int &ch : adj[v]) {
            pr[ch] = v, dep[ch] = dep[v] + 1;
            dfs_sz(ch);
            sz[v] += sz[ch];
            if (sz[ch] > sz[adj[v][0]]) swap(ch, adj[v][0]);
        }
    }
    void dfs(int v) {
        idx[v] = cnt++;
        for (int ch : adj[v]) {
            tp[ch] = (ch == adj[v][0] ? tp[v] : ch);
            dfs(ch);
        }
    }
    template<class B> void process(int u, int v, B op) {
        for (; tp[u] != tp[v]; v = pr[tp[v]]) {
            if (dep[tp[u]] > dep[tp[v]]) swap(u, v);
            op(idx[tp[v]], idx[v]);
        }
        if (dep[u] > dep[v]) swap(u, v);
        op(idx[u] + EDGES, idx[v]);
    }
    // requires lazy segment tree
    void update_path(int u, int v, int val) { 
        // process(u, v, [&](int l, int r) { tree.update(l, r, val); });
    }
    void update_vertex(int v, int val) {
        tree.update(idx[v], val);
    }
    int query(int u, int v) {
        int ans = 0;
        process(u, v, [&](int l, int r) { ans = max(ans, tree.query(l, r).x); });
        return ans;
    }
    int query_subtree(int v) {
        return tree.query(idx[v] + EDGES, idx[v] + sz[v] - 1).x;
    }
};

void solvetask() {
    int n, q; cin >> n >> q;
    vector<vector<int>> adj(n);
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    hld<false> g(adj);
    for (int i = 0; i < n; i++) g.update_vertex(i, a[i]);

    while (q--) {
        int tp; cin >> tp;
        if (tp == 1) {
            int v, x; cin >> v >> x;
            v--;
            g.update_vertex(v, x);
        } else {
            int u, v; cin >> u >> v;
            u--, v--;
            cout << g.query(u, v) << " ";
        }
    }
    cout << endl;
}
 
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t = 1;
    while(t--) solvetask();
}

