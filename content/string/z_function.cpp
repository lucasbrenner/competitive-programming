#include "../contest/template.cpp"

vector<int> z_function(string s) {
    int n = sz(s);
    vector<int> z(n);
    int x = 0, y = 0;
    rep(i, 1, n) {
        z[i] = max(0,min(z[i-x],y-i+1));
        while (i+z[i] < n && s[z[i]] == s[i+z[i]]) {
            x = i; y = i+z[i]; z[i]++;
        }
    }
    return z;
}
