#include "../contest/template.cpp"

struct lca {
    vector<vector<int>> adj, anc;
    vector<int> dep, in, out;
    int n, lg, t;
    lca(int n) : n(n), adj(n + 1), dep(n + 1), in(n + 1), out(n + 1) {
        lg = 32 - __builtin_clz(n);
        anc = vector<vector<int>>(n + 1, vector<int>(lg));
    }
    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void dfs(int v, int p = -1, int d = 1) {
        dep[v] = d;
        in[v] = t++;
        for (int i = 1; i < lg; i++) anc[v][i] = anc[anc[v][i - 1]][i - 1];
        for (int ch : adj[v]) if (ch != p) {
            anc[ch][0] = v;
            dfs(ch, v, d + 1);
        }
        out[v] = t++;
    }
    bool is_anc(int a, int b){
        return (in[a] <= in[b]) && (out[a] >= out[b]);
    }
    int get_lca(int a, int b) {
        if(is_anc(a, b)) return a;
        if(is_anc(b, a)) return b;
        for (int i = lg - 1; i >= 0; i--) {
            if (!is_anc(anc[a][i], b) /*&& *anc[a][i]*/){ //descomentar se for 1 indexado
                a = anc[a][i];
            }
        }
        return anc[a][0];
    }
    int dist(int a, int b) {
        return dep[a] + dep[b] - 2 * dep[get_lca(a, b)];
    }
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
