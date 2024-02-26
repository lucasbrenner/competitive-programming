#include "../contest/template.cpp"

vector<vector<int>> block_cut(vector<vector<int>> g, vector<int> &is_cut, vector<int> &at) {
    int n = sz(g);
    is_cut.resize(n);

    vector<int> st, tin(n), low(n);
    vector<vector<int>> comps;

    int t = 0;
    auto dfs = [&](auto &self, int v, int p) -> void {
        tin[v] = low[v] = ++t;
        st.push_back(v);
        for (int ch : g[v]) if (ch != p) {
            if (tin[ch]) {
                low[v] = min(low[v], tin[ch]);
            } else {
                self(self, ch, v);
                low[v] = min(low[v], low[ch]);
                if (low[ch] >= tin[v]) {
                    is_cut[v] |= tin[v] > 1 || tin[ch] > 2;
                    comps.push_back({v});
                    while (comps.back().back() != ch) {
                        comps.back().push_back(st.back());
                        st.pop_back();
                    }
                }
            }
        }
    };
    dfs(dfs, 0, -1);

    at.resize(n);
    vector<vector<int>> adj;
    rep(v, 0, n) if (is_cut[v]) {
        at[v] = sz(adj);
        adj.push_back({});
    }
    for (auto comp : comps) {
        int id = sz(adj);
        adj.push_back({});
        for (int v : comp) {
            if (!is_cut[v]) at[v] = id;
            else {
                adj[at[v]].push_back(id);
                adj[id].push_back(at[v]);
            }
        }
    }
    if (!sz(adj)) adj.push_back({});
    return adj;
}

