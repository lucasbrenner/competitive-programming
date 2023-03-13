#include "bits/stdc++.h"
using namespace std;

vector<int> centroid_dec(vector<vector<int>> &adj) {
    int n = adj.size();
    vector<int> p(n), vis(n), sz(n);

    auto build_sz = [&](auto self, int v, int pr) -> int {
        sz[v] = 1;
        for (int ch : adj[v]) {
            if (!vis[ch] && ch != pr) sz[v] += self(self, ch, v);
        }
        return sz[v];
    };

    auto find_cent = [&](auto self, int v, int pr, int size) -> int {
        for (int ch : adj[v]) {
            if (!vis[ch] && ch != pr && sz[ch] > size / 2)
                return self(self, ch, v, size);
        }
        return v;
    };

    auto build_cent = [&](auto self, int v, int pr) -> void {
        build_sz(build_sz, v, -1);
        int c = find_cent(find_cent, v, -1, sz[v]);
        p[c] = pr;
        vis[c] = true;
        for (int ch : adj[c]) {
            if (!vis[ch]) self(self, ch, c);
        }
    };

    build_cent(build_cent, n - 1, -1);

    return p;
}

