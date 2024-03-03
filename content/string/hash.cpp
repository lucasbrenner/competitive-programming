#include "../contest/template.cpp"

mt19937 rng((int) chrono::steady_clock::now().time_since_epoch().count());
const int K = 2, P = uniform_int_distribution<int>(256, (int)1e9)(rng); // l > |sigma|, r < min(mod)
const ll MOD[] = { (int)1e9 + 7, (int)1e9 + 9 };
ll ph[1000100][K], IT;

struct hsh {
    vector<array<ll, K>> h;
    hsh() {}
    hsh(const string &s) {
        h.resize(sz(s));
        while (IT < sz(s)) {
            rep(j, 0, K) ph[IT][j] = IT ? ph[IT - 1][j] * P % MOD[j] : 1;
            IT++;
        }
        rep(i, 0, sz(s)) rep(j, 0, K) {
            h[i][j] = ((i > 0 ? h[i - 1][j] * P : 0) + s[i]) % MOD[j];
        }
    }
    array<ll, K> operator()(int l, int r) {
        array<ll, K> ans;
        rep(j, 0, K) {
            ans[j] = h[r][j] - (l > 0 ? h[l - 1][j] * ph[r - l + 1][j] % MOD[j] : 0);
            if (ans[j] < 0) ans[j] += MOD[j];
        }
        return ans;
    }
};

