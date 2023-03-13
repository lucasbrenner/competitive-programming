#include "bits/stdc++.h"
using namespace std;

struct lca {
    vector<vector<int>> adj, anc;
    vector<int> depth;
    int n, lg;

    lca(int n) : n(n) {
        lg = 33 - __builtin_clz(n);
        adj.resize(n + 1);
        anc = vector<vector<int>>(n + 1, vector<int>(lg));
        depth.resize(n + 1);
    }

    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void dfs(int v, int p, int d) {
        depth[v] = d;
        for (int c : adj[v]) {
            if (c == p) continue;
            anc[c][0] = v;
            dfs(c, v, d + 1);
        }
    }

    void build(int root) {
        dfs(root, -1, 1);
        for (int i = 1; i < lg; i++) {
            for (int v = 1; v <= n; v++) {
                if (depth[v] - (1 << i) >= 1) {
                    anc[v][i] = anc[anc[v][i - 1]][i - 1];
                }
            }
        }
    }

    int get_lca(int a, int b) {
        if (depth[a] < depth[b]) swap(a, b);

        for (int i = lg - 1; i >= 0; i--) {
            if (depth[a] - depth[b] >= (1 << i)) a = anc[a][i];
        }
        if (a == b) return a;

        for (int i = lg - 1; i >= 0; i--) {
            if (anc[a][i] != anc[b][i]){
                a = anc[a][i];
                b = anc[b][i];
            }
        }
        return anc[a][0];
    }

    int dist(int a, int b) {
        return depth[a] + depth[b] - 2 * depth[get_lca(a, b)];
    }

    // k-th ancestor of v
    int jump(int v, int k) {
        for (int i = lg - 1; i >= 0; i--) {
            if ((1 << i) <= k) {
                v = anc[v][i];
                k -= (1 << i);
            }
        }
        return v;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, q; cin >> n >> q;
    lca g(n);

    for (int i = 1; i < n; i++) {
        int p; cin >> p;
        g.add_edge(p, i);
    }

    g.build(0);

    while(q--) {
        int a, b; cin >> a >> b;
        cout << g.get_lca(a, b) << '\n';
    }
}

