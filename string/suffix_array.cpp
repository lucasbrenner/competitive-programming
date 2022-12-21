#include"bits/stdc++.h"
using namespace std;

struct rmq {
    vector<vector<int>> t;

    rmq() {}
    rmq(const vector<int> &a) {
        int n = a.size(), lg = __builtin_clz(1) - __builtin_clz(n);
        t = vector<vector<int>>(lg + 1, vector<int>(n));
        for (int i = 0; i < n; i++) t[0][i] = a[i];
        for (int i = 1; (1 << i) <= n; i++) for (int j = 0; j + (1 << i) <= n; j++)
            t[i][j] = min(t[i - 1][j], t[i - 1][j + (1 << (i - 1))]);
    }

    int query(int l, int r) {
        if (l > r) swap(l, r);
        int lg = __builtin_clz(1) - __builtin_clz(r - l + 1);
        return min(t[lg][l], t[lg][r - (1 << lg) + 1]);
    }
};

struct suffix_array {
    string s;
    int n;
    rmq RMQ;
    vector<int> p, rnk, lcp;
    const int ALP = 256;

    suffix_array(const string &s_) : s(s_) {
        s += (char)0;
        n = s.length();
        p.resize(n), rnk.resize(n), lcp.resize(n);
        int cl = 1;
        vector<int> cn(n), pn(n), cnt(max(n, ALP), 0);
        for (int i = 0; i < n; i++) cnt[s[i]]++;
        for (int i = 1; i < ALP; i++) cnt[i] += cnt[i - 1];
        for (int i = 0; i < n; i++) p[--cnt[s[i]]] = i;
        rnk[p[0]] = 0;
        for (int i = 1; i < n; i++) {
            if(s[p[i]] != s[p[i - 1]]) cl++;
            rnk[p[i]] = cl - 1;
        }
        for (int h = 0; (1 << h) < n; h++) {
            for (int i = 0; i < n; i++) {
                pn[i] = p[i] - (1 << h);
                if (pn[i] < 0) pn[i] += n;
            }
            fill(cnt.begin(), cnt.end(), 0);
            for (int i = 0; i < n; i++) cnt[rnk[pn[i]]]++;
            for (int i = 1; i < cl; i++) cnt[i] += cnt[i - 1];
            for (int i = n - 1; i >= 0; i--) {
                p[--cnt[rnk[pn[i]]]] = pn[i];
            }
            cl = 1;
            cn[p[0]] = 0;
            for (int i = 1; i < n; i++) {
                pair<int, int> cur = {rnk[p[i]], rnk[(p[i] + (1 << h)) % n]};
                pair<int, int> prv = {rnk[p[i - 1]], rnk[(p[i - 1] + (1 << h)) % n]};
                if(cur != prv) cl++;
                cn[p[i]] = cl - 1;
            }
            cn.swap(rnk);
        }

        for (int i = 0, k = 0; i < n - 1; i++) {
            int prv = p[rnk[i] - 1];
            while (s[i + k] == s[prv + k]) k++;
            lcp[rnk[i]] = k;
            k = max(0, k - 1);
        }
        
        RMQ = rmq(lcp);
    }

    int query(int l, int r) {
        if (l == r) return n - l;
        return RMQ.query(min(l, r) + 1, max(l, r));
    }
};

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    string s; cin >> s;
    suffix_array sa(s);
    for (int x : sa.p) cout << x << " ";
    cout << endl;
}

