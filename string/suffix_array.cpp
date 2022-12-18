#include"bits/stdc++.h"
using namespace std;

const int ALP = 256;

vector<int> suffix_array(const string &s) {
    int n = s.length(), cl = 1;
    vector<int> c(n), p(n), cn(n), pn(n), cnt(max(n, ALP), 0);
    for (int i = 0; i < n; i++) cnt[s[i]]++;
    for (int i = 1; i < ALP; i++) cnt[i] += cnt[i - 1];
    for (int i = 0; i < n; i++) p[--cnt[s[i]]] = i;
    c[p[0]] = 0;
    for (int i = 1; i < n; i++) {
        if(s[p[i]] != s[p[i - 1]]) cl++;
        c[p[i]] = cl - 1;
    }
    for (int h = 0; (1 << h) < n; h++) {
        for (int i = 0; i < n; i++) {
            pn[i] = p[i] - (1 << h);
            if (pn[i] < 0) pn[i] += n;
        }
        fill(cnt.begin(), cnt.end(), 0);
        for (int i = 0; i < n; i++) cnt[c[pn[i]]]++;
        for (int i = 1; i < cl; i++) cnt[i] += cnt[i - 1];
        for (int i = n - 1; i >= 0; i--) {
            p[--cnt[c[pn[i]]]] = pn[i];
        }
        cl = 1;
        cn[p[0]] = 0;
        for (int i = 1; i < n; i++) {
            pair<int, int> cur = {c[p[i]], c[(p[i] + (1 << h)) % n]};
            pair<int, int> prv = {c[p[i - 1]], c[(p[i - 1] + (1 << h)) % n]};
            if(cur != prv) cl++;
            cn[p[i]] = cl - 1;
        }
        cn.swap(c);
    }
    return p;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    string s; cin >> s;
    s += '$';
    auto sa = suffix_array(s);
    for (int x : sa) cout << x << " ";
    cout << endl;
}

