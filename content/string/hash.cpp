#include "../contest/template.cpp"

struct poly_hash {
    const static int N = 2e6 + 10, K = 2;
    constexpr static ll base[] = { 307, 317 }, mod[] = { 104000711, 104000717 };

    ll iv[N][K], p[N][K], h[N][K];

    ll inverse(ll a, ll b, ll s0 = 1, ll s1 = 0) {
        return b == 0 ? s0 : inverse(b, a % b, s1, s0 - s1 * (a / b));
    }

    poly_hash(const string &s) {
        for (int k = 0; k < K; k++) {
            p[0][k] = iv[0][k] = 1;
            p[1][k] = base[k];
            iv[1][k] = inverse(base[k], mod[k]);
            for (int i = 2; i < N; i++){
                p[i][k] = p[i - 1][k] * p[1][k] % mod[k];
                iv[i][k] = iv[i - 1][k] * iv[1][k] % mod[k];
            }
        }
        for (int i = 1; i <= (int)s.size(); i++) for (int k = 0; k < K; k++) {
            h[i][k] = (h[i - 1][k] + (s[i - 1] - 'a' + 1) * p[i][k] % mod[k]) % mod[k];
        }
    }

    array<ll, K> query(int l, int r){
        l++; r++;
        array<ll, 2> ans;
        for (int k = 0; k < K; k++){
            ans[k] = (h[r][k] - h[l - 1][k] + mod[k]) % mod[k] * iv[l][k] % mod[k];
        }
        return ans;
    }
};

