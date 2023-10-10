#include "../contest/template.cpp"

mt19937 rng((int) chrono::steady_clock::now().time_since_epoch().count());
struct bip_match {
    int n, m;
    vector<vector<int>> g;
    // ma[i] = quem eh o match de i (-1 se nao tem)
    vector<int> dist, nxt, ma, mb;

    bip_match(int n_, int m_) : n(n_), m(m_), g(n),
        dist(n), nxt(n), ma(n, -1), mb(m, -1) {}

    // 0 indexado
    void add(int a, int b) { g[a].push_back(b); }

    bool dfs(int i) {
        for (int &id = nxt[i]; id < g[i].size(); id++) {
            int j = g[i][id];
            if (mb[j] == -1 or (dist[mb[j]] == dist[i] + 1 and dfs(mb[j]))) {
                ma[i] = j, mb[j] = i;
                return true;
            }
        }
        return false;
    }
    bool bfs() {
        for (int i = 0; i < n; i++) dist[i] = n;
        queue<int> q;
        for (int i = 0; i < n; i++) if (ma[i] == -1) {
            dist[i] = 0;
            q.push(i);
        }
        bool rep = 0;
        while (q.size()) {
            int i = q.front(); q.pop();
            for (int j : g[i]) {
                if (mb[j] == -1) rep = 1;
                else if (dist[mb[j]] > dist[i] + 1) {
                    dist[mb[j]] = dist[i] + 1;
                    q.push(mb[j]);
                }
            }
        }
        return rep;
    }
    int solve() {
        int ret = 0;
        for (auto& i : g) shuffle(i.begin(), i.end(), rng);
        while (bfs()) {
            for (int i = 0; i < n; i++) nxt[i] = 0;
            for (int i = 0; i < n; i++)
                if (ma[i] == -1 and dfs(i)) ret++;
        }
        return ret;
    }
};

