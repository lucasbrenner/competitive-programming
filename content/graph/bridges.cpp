#include "../contest/template.cpp"

const int N = 3e5 + 10;
int n, m, tin[N], low[N], e[N][2], is_bridge[N];
vector<int> adj[N];

int timer;
void dfs(int v, int p = -1) {
    tin[v] = low[v] = timer++;
    for (int i : adj[v]) {
        int to = e[i][0] ^ e[i][1] ^ v;
        if (to == p) continue;
        if (tin[to]) {
            low[v] = min(low[v], tin[to]);
        } else {
            dfs(to, v);
            low[v] = min(low[v], low[to]);
            if (low[to] > tin[v]) {
                is_bridge[i] = 1;
            }
        }
    }
}

void find_bridges() {
    timer = 1;
    rep(i, 0, n) {
        tin[i] = low[i] = 0;
    }
    rep(i, 0, n) if (!tin[i]) dfs(i);
}

