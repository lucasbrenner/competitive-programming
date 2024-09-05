#include "../contest/template.cpp"

vector<vector<int>> rotate_ccw(const vector<vector<int>> &a) {
    int n = sz(a), m = sz(a[0]);
    vector b(m, vector<int>(n));
    rep(i, 0, n) rep(j, 0, m) {
        b[m - j - 1][i] = a[i][j];
    }
    return b;
}

vector<vector<int>> rotate_cw(const vector<vector<int>> &a) {
    int n = sz(a), m = sz(a[0]);
    vector b(m, vector<int>(n));
    rep(i, 0, n) rep(j, 0, m) {
        b[j][n - i - 1] = a[i][j];
    }
    return b;
}

