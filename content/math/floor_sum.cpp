#include "../contest/template.cpp"

// somatorio de floor((a * x + b) / m)
// para x em [0, n)
ll floor_sum(ll n, ll m, ll a, ll b) {
    ll a1 = a / m;
    ll a2 = a % m;
    ll ans = n * (n - 1) / 2 * a1;
    if (a2 == 0) {
        return ans + (b / m) * n;
    }
    ll b1 = b / m;
    ll b2 = b % m;
    ll y = (a2 * n + b2) / m;
    ans += n * (y + b1) - floor_sum(y, a2, m, m + a2 - b2 - 1);
    return ans;
}

