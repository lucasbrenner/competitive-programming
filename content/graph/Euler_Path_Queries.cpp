#include "../contest/template.cpp"

template <bool EDGES> struct Euler_Path{
    vector<vector<int>> adj;
    vector<int> idxs;
    vector<int> siz;
    vector<ll> bit;
    vector<int> vals;
    vector<int> dep;
    vector<vector<int>> anc;
    int n;
    int lg = 15;
    Euler_Path(vector<vector<int>> _adj){
        adj = _adj;
        n = sz(adj);
        idxs.resize(n);
        siz.resize(n);
        bit.resize(n);
        vals.resize(n);
        anc = vector<vector<int>>(n, vector<int>(lg));
        dep.resize(n);
        dfs(0); //tree root       
    }
 
    int time = 0;
    void dfs(int i, int p = 0){
        idxs[i] = time++;
        siz[i] = 1;
        anc[i][0] = p;
        dep[i] = dep[p] + 1;
        for(int j = 1; j < lg; j++){
            anc[i][j] = anc[anc[i][j - 1]][j - 1];
        }

        for(auto c: adj[i]){
            if(c == p) continue;
            dfs(c, i);
            siz[i] += siz[c];
        }
    }

    int lca(int x,int y){
        if(dep[x] < dep[y]) swap(x,y);
        for(int i = lg - 1; i >= 0; i--) if(dep[anc[x][i]] >= dep[y]) x = anc[x][i];
        if(x == y) return x;

        for(int i = lg - 1; i >= 0; i--) if(anc[x][i] != anc[y][i]) x = anc[x][i], y = anc[y][i];
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
 
    void inc_vertex(int i, ll x){
        vals[i] += x;
        add(idxs[i], x);
        if(siz[i] + idxs[i] < n) add(idxs[i] + siz[i], -x);
    }
 
    void update_vertex(int i, ll x){
        inc_vertex(i, x - vals[i]);
    }
 
    ll query(int u){
        return sum(idxs[u]);
    }

    ll query(int u, int v){
        int lc = lca(u, v);
        return query(u) + query(v) - 2 * query(lc) + vals[lc] * (EDGES == false);
    }
};
