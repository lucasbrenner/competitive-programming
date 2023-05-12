#include "bits/stdc++.h"
using namespace std;

struct lca {
    vector<vector<int>> adj, anc;
    vector<int> dep;
    int n, lg;

    lca(int n) : n(n) {
        lg = 32 - __builtin_clz(n);
        adj.resize(n + 1);
        anc = vector<vector<int>>(n + 1, vector<int>(lg));
        dep.resize(n + 1);
    }

    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void dfs(int v, int p = -1, int d = 1) {
        dep[v] = d;
        for (int i = 1; i < lg; i++) anc[v][i] = anc[anc[v][i - 1]][i - 1];
        for (int ch : adj[v]) if (ch != p) {
            anc[ch][0] = v;
            dfs(ch, v, d + 1);
        }
    }

    int get_lca(int a, int b) {
        if (dep[a] < dep[b]) swap(a, b);

        for (int i = lg - 1; i >= 0; i--) {
            if (dep[a] - dep[b] >= (1 << i)) a = anc[a][i];
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
        return dep[a] + dep[b] - 2 * dep[get_lca(a, b)];
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

    g.dfs(0);

    while(q--) {
        int a, b; cin >> a >> b;
        cout << g.get_lca(a, b) << '\n';
    }
}

