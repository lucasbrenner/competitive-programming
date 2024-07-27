#include "../contest/template.cpp"

template <bool EDGES> struct euler_path {
    vector<vector<int>> adj, anc;
    vector<int> idxs, siz, dep;
    vector<ll> bit, vals;
    int n;
    const int lg = 18;
    euler_path(vector<vector<int>> _adj) {
        adj = _adj;
        n = sz(adj);
        idxs.resize(n);
        siz.resize(n);
        bit.resize(n);
        vals.resize(n);
        anc = vector<vector<int>>(n, vector<int>(lg));
        dep.resize(n);
        dfs(1); //tree root
    }
    int time = 0;
    void dfs(int v, int p = 0) {
        idxs[v] = time++;
        siz[v] = 1;
        anc[v][0] = p;
        dep[v] = dep[p] + 1;
        rep(j, 1, lg) {
            anc[v][j] = anc[anc[v][j - 1]][j - 1];
        }

        for (auto ch: adj[v]) if (ch != p) {
            dfs(ch, v);
            siz[v] += siz[ch];
        }
    }
    int lca(int x,int y) {
        if (dep[x] < dep[y]) swap(x,y);
        for (int i = lg - 1; i >= 0; i--) if (dep[anc[x][i]] >= dep[y]) x = anc[x][i];
        if (x == y) return x;

        for (int i = lg - 1; i >= 0; i--) if (anc[x][i] != anc[y][i]) x = anc[x][i], y = anc[y][i];
        return anc[x][0];
    }
    ll sum(int x) {
        ll s = 0;
        for (int i = x; i >= 0; i = (i & (i + 1)) - 1) s += bit[i];
        return s;
    }
    void add(int x, ll delta) {
        for (int i = x; i < n; i = i | (i + 1)) bit[i] += delta;
    }
    void inc_vertex(int i, ll x) {
        vals[i] += x;
        add(idxs[i], x);
        if(siz[i] + idxs[i] < n) add(idxs[i] + siz[i], -x);
    }
    void update_vertex(int i, ll x) {
        inc_vertex(i, x - vals[i]);
    }
    ll query(int u) {
        return sum(idxs[u]);
    }
    ll query(int u, int v) {
        int lc = lca(u, v);
        return query(u) + query(v) - 2 * query(lc) + vals[lc] * (EDGES == false);
    }
};

