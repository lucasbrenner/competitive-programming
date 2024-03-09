#include "../contest/template.cpp"

vector<int> kmp(const string &s) {
    int n = s.size();
    vector<int> p(n);
    rep(i, 1, n) {
        int j = p[i - 1];
        while (j > 0 && s[i] != s[j]) j = p[j - 1];
        if (s[i] == s[j]) j++;
        p[i] = j;
    }
    return p;
}

