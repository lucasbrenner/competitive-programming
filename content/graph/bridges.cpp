#include "../contest/template.cpp"

int n; // number of nodes
vector<vector<int>> adj; // adjacency list of graph

vector<int> tin, low, visited;
int timer;

void dfs(int v, int p = -1) {
    visited[v] = true;
    tin[v] = low[v] = timer++;
    for (int to : adj[v]) {
        if (to == p) continue;
        if (visited[to]) {
            low[v] = min(low[v], tin[to]);
        } else {
            dfs(to, v);
            low[v] = min(low[v], low[to]);
            if (low[to] > tin[v]) {
                // (v, to) eh uma ponte
            }
        }
    }
}

void find_bridges() {
    timer = 0;
    visited.assign(n, false);
    tin.assign(n, -1);
    low.assign(n, -1);
    rep(i, 0, n) if (!visited[i]) dfs(i);
}

