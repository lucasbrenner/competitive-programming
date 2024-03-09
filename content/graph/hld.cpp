#include "../contest/template.cpp"

template<class T> struct seg_tree {
    struct node {
        T x = 0;
        const node operator + (const node& o) const {
            node ans;
            ans.x = max(o.x, x);
            return ans;
        }
    };

    int n;
    vector<node> tree;
    seg_tree(int n) : n(n), tree(n * 2) {}
    void update(ll i, T f){
        i += n;
        tree[i].x = f;
        for(i >>= 1; i >= 1; i >>= 1) tree[i] = tree[i * 2] + tree[i * 2 + 1];
    }
    T query(ll a, ll b){
        node esq, dir;
        for(a += n, b += n; a <= b; a >>= 1, b >>= 1){
            if(a % 2) esq = esq + tree[a++];
            if(b % 2 == 0) dir = tree[b--] + dir;
        }
        return (esq + dir).x;
    }
};

template<bool EDGES> struct hld {
    int n, cnt = 0;
    vector<vector<int>> adj;
    vector<int> pr, siz, dep, tp, idx;
    seg_tree<int> tree;
    hld(vector<vector<int>> adj)
        : n(sz(adj)), adj(adj), pr(n, -1), siz(n, 1), dep(n),
        tp(n), idx(n), tree(n) {
        dfs_sz(0);
        dfs(0);
    }
    void dfs_sz(int v) {
        if (pr[v] != -1) adj[v].erase(find(all(adj[v]), pr[v]));
        for (int &ch : adj[v]) {
            pr[ch] = v, dep[ch] = dep[v] + 1;
            dfs_sz(ch);
            siz[v] += siz[ch];
            if (siz[ch] > siz[adj[v][0]]) swap(ch, adj[v][0]);
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
    /* requires lazy segment tree
    void update_path(int u, int v, int val) {
        process(u, v, [&](int l, int r) { tree.update(l, r, val); });
    }
    */
    void update_vertex(int v, int val) {
        tree.update(idx[v], val);
    }
    int query(int u, int v) {
        int ans = 0;
        process(u, v, [&](int l, int r) { ans = max(ans, tree.query(l, r)); });
        return ans;
    }
    int query_subtree(int v) {
        return tree.query(idx[v] + EDGES, idx[v] + siz[v] - 1);
    }
};
