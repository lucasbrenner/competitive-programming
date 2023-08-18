// https://cses.fi/problemset/task/1691/
#include "../contest/template.cpp"

#define endl '\n'

void solve() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int n, m; cin >> n >> m;
    vector<vector<int>> adj(n + 1);
    vector<array<int, 2>> e(m);
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(i);
        adj[v].push_back(i);
        e[i] = { u, v };
    }
    for (int i = 1; i <= n; i++) {
        if (adj[i].size() % 2 == 1) {
            cout << "IMPOSSIBLE" << endl;
            return;
        }
    }
    vector<int> ans, vis(m);
    auto dfs = [&](auto self, int v) -> void {
        while (adj[v].size() > 0) {
            int i = adj[v].back();
            adj[v].pop_back();
            if (!vis[i]) {
                vis[i] = 1;
                self(self, e[i][e[i][0] == v]);
            }
        }
        ans.push_back(v);
    };
    dfs(dfs, 1);
    if (ans.size() != m + 1) cout << "IMPOSSIBLE" << endl;
    else {
        for (int x : ans) cout << x << " ";
        cout << endl;
    }
}

