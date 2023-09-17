#include "../contest/template.cpp"
using namespace std;

const int N = 5e5 + 10, K = 26, first = 'a';
struct node {
    int link = -1, len = 0, to[K];
    node() {
        memset(to, -1, sizeof to);
    }
} st[2 * N];

struct suffix_automaton {
    int pt = 1, last = 0;
    suffix_automaton() {}
    suffix_automaton(const string &s) {
        for (auto c : s) add(c - first);
    }
    void add(int c) {
        int cur = pt++;
        st[cur].len = st[last].len + 1;
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
    bool contains(const string &s) {
        int v = 0;
        for (char c : s) {
            int x = c - first;
            if (st[v].to[x] == -1) return false;
            v = st[v].to[x];
        }
        return true;
    }
    ll unique_substrs() {
        ll ans = 0;
        rep(i, 1, pt) ans += st[i].len - st[st[i].link].len;
        return ans;
    }
};

