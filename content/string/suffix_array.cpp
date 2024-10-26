#include "../data-structures/rmq.cpp"

struct suffix_array {
    // lcp[i] = lcp(sa[i], sa[i - 1])
    vector<int> sa, lcp, rnk;
    rmq<int> RMQ;
    //Se usar basic_string<int>, não colocar algum valor = 0
    suffix_array(string& s, int lim=256) { // or basic_string<int>
        int n = sz(s) + 1, k = 0, a, b;
        vector<int> x(all(s)+1), y(n), ws(max(n, lim));
        rnk.resize(n);
        sa = lcp = y, iota(all(sa), 0);
        for (int j = 0, p = 0; p < n; j = max(1, j * 2), lim = p) {
            p = j, iota(all(y), n - j);
            rep(i,0,n) if (sa[i] >= j) y[p++] = sa[i] - j;
            fill(all(ws), 0);
            rep(i,0,n) ws[x[i]]++;
            rep(i,1,lim) ws[i] += ws[i - 1];
            for (int i = n; i--;) sa[--ws[x[y[i]]]] = y[i];
            swap(x, y), p = 1, x[sa[0]] = 0;
            rep(i,1,n) a = sa[i - 1], b = sa[i], x[b] =
                (y[a] == y[b] && y[a + j] == y[b + j]) ? p - 1 : p++;
        }
        rep(i,1,n) rnk[sa[i]] = i;
        for (int i = 0, j; i < n - 1; lcp[rnk[i++]] = k)
            for (k && k--, j = sa[rnk[i] - 1]; s[i + k] == s[j + k]; k++);
        RMQ = rmq<int>(lcp);
    }
    // l e r sao posicoes no suffix array
    int query(int l, int r) {
        if (l == r) return sz(sa) - sa[l] - 1;
        return RMQ.query(min(l, r) + 1, max(l, r));
    }
    int compare(int l1, int r1, int l2, int r2) {
        int len1 = r1 - l1 + 1, len2 = r2 - l2 + 1;
        int len = min({query(rnk[l1], rnk[l2]), len1, len2});
        if (len1 == len2 && len == len1) return 0;
        if (len == len1) return -1;
        if (len == len2) return 1;
        return rnk[l1] < rnk[l2] ? -1 : 1;
    }
};

