#include "../contest/template.cpp"
#include "./ext_gcd.cpp"

ll crt(ll a, ll m, ll b, ll n) {
    if (n > m) swap(a, b), swap(m, n);
    ll x, y, g = ext_gcd(m, n, x, y);
    if((a - b) % g != 0) return -1;
    x = (b - a) % n * x % n / g * m + a;
    return x < 0 ? x + m*n/g : x;
}
