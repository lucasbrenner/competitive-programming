#include "../data-structures/rmq.cpp"

struct suffix_array {
    string s;
    int n;
    rmq<int> RMQ;
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

