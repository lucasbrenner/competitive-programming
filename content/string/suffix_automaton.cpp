#include "../contest/template.cpp"
using namespace std;

struct suffix_automaton {
    enum { N = (int)5e5 + 10, K = 26, first = 'a' };
    struct node {
        int link = -1, len = 0, to[K];
        node() {
            memset(to, -1, sizeof to);
        }
    };
    int pt = 1, last = 0;
    node st[2 * N];

    int cnt[2 * N], d[2 * N]; // only necessary to count occurrences
    ll paths[2 * N]; // only necessary for kth

    void build(const string &s) {
        for (auto c : s) add(c - first);
        memset(paths, -1, sizeof paths);
    }
    void add(int c) {
        int cur = pt++;
        st[cur].len = st[last].len + 1;
        cnt[cur] = 1;
        int p = last;
        while (p != -1 && st[p].to[c] == -1) {
            st[p].to[c] = cur;
            p = st[p].link;
        }
        if (p == -1) {
            st[cur].link = 0;
        } else {
            int q = st[p].to[c];
            if (st[p].len + 1 == st[q].len) {
                st[cur].link = q;
            } else {
                int clone = pt++;
                cnt[clone] = 0;
                rep(i, 0, K) st[clone].to[i] = st[q].to[i];
                st[clone].link = st[q].link;
                st[clone].len = st[p].len + 1;
                while (p != -1 && st[p].to[c] == q) {
                    st[p].to[c] = clone;
                    p = st[p].link;
                }
                st[q].link = st[cur].link = clone;
            }
        }
        last = cur;
    }
    int get(const string &s) {
        int v = 0;
        for (char c : s) {
            int x = c - first;
            if (st[v].to[x] == -1) return -1;
            v = st[v].to[x];
        }
        return v;
    }
    ll unique_substrs() {
        ll ans = 0;
        rep(i, 1, pt) ans += st[i].len - st[st[i].link].len;
        return ans;
    }
    ll dfs(int v) {
        if (paths[v] != -1) return paths[v];
        paths[v] = 1;
        rep(i, 0, K) if (st[v].to[i] != -1) {
            paths[v] += dfs(st[v].to[i]);
        }
        return paths[v];
    }
    string kth(ll k) {
        dfs(0);
        int v = 0, prv = -1;
        string ans = "";
        while (k > 0) {
            assert(v != prv);
            prv = v;
            rep(i, 0, K) if (st[v].to[i] != -1) {
                if (paths[st[v].to[i]] < k) {
                    k -= paths[st[v].to[i]];
                } else {
                    k--;
                    ans += i + first;
                    v = st[v].to[i];
                    break;
                }
            }
        }
        return ans;
    }
    void precnt() {
        memset(d, 0, sizeof d);
        rep(i, 1, pt) d[st[i].link]++;
        queue<int> q;
        rep(i, 1, pt) if (d[i] == 0) {
            q.push(i);
        }
        while (!q.empty()) {
            int v = q.front(); q.pop();
            if (v == 0) continue;
            cnt[st[v].link] += cnt[v];
            if (d[st[v].link]-- == 1) q.push(st[v].link);
        }
    }
} sa;


