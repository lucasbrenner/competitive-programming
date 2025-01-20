#include "../contest/template.cpp"

struct dsu {
    vector<int> p, rnk;
    int comps;
    dsu(int n) : p(n), rnk(n, 1), comps(n) { iota(all(p), 0); }
    int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
    bool join(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (rnk[a] < rnk[b]) swap(a, b);
        p[b] = a;
        rnk[a] += rnk[b];
        comps--;
        return true;
    }
    bool same(int a, int b) { return find(a) == find(b); }
};
