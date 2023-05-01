#include "bits/stdc++.h"
using namespace std;

#define endl '\n'
typedef long long ll;

struct aho_corasick {
    enum { N = (int)5e5 + 10, K = 26, first = 'a' };
    struct node {
        int ch[K], cnt, link, p;
        vector<int> id;
        node() {
            memset(ch, -1, sizeof ch);
            cnt = link = p = 0;
        }
    } a[N];
    vector<int> adj[N];
    int pt = 0, ans[N];
    void insert(const string &s, int id) {
        int cur = 0;
        for (char c : s) {
            int x = c - first;
            if (a[cur].ch[x] == -1) {
                pt++;
                a[pt].p = cur;
                a[cur].ch[x] = pt;
            }
            cur = a[cur].ch[x];
        }
        a[cur].id.push_back(id);
    }
    void build() {
        queue<pair<int, int>> q;
        for (q.emplace(0, 0); !q.empty(); q.pop()) {
            auto [v, c] = q.front();
            if (a[v].p) {
                int &link = a[v].link;

                link = a[a[v].p].link;
                while (link && a[link].ch[c] == -1) {
                    link = a[link].link;
                }
                if (a[link].ch[c] != -1) link = a[link].ch[c];
            }
            if (v) adj[a[v].link].push_back(v);

            for (int i = 0; i < K; i++) if (a[v].ch[i] != -1) {
                q.push({a[v].ch[i], i});
            }
        }
    }

    void solve(const string &s) {
        memset(ans, 0, sizeof ans);
        int cur = 0;
        for (char c : s) {
            int x = c - first;
            while (cur && a[cur].ch[x] == -1) {
                cur = a[cur].link;
            }
            if (a[cur].ch[x] != -1) {
                cur = a[cur].ch[x];
            }
            a[cur].cnt++;
        }
        dfs(0);
    }

    int dfs(int v) {
        for (int ch : adj[v]) a[v].cnt += dfs(ch);
        for (int id : a[v].id) ans[id] = a[v].cnt;
        return a[v].cnt;
    }
};

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    aho_corasick aho;
    string s; cin >> s;
    int q; cin >> q;
    for (int i = 1; i <= q; i++) {
        string t; cin >> t;
        aho.insert(t, i);
    }
    aho.build();
    aho.solve(s);
    for (int i = 1; i <= q; i++) cout << (aho.ans[i] ? "YES" : "NO") << endl;
}

