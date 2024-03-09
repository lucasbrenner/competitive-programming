#include "../contest/template.cpp"
#include "fft.cpp"

// res[i] = somatorio a[j] * b[(i - j + n) % n]
void circularConv(vector<double> &a, vector<double> &b, vector<double> &res) {
    assert(sz(a) == sz(b));
    int n = a.size();
    res = conv(a, b);
    rep(i, n, sz(res)) res[i%n] = (res[i%n]+res[i]);
    res.resize(n);
}

