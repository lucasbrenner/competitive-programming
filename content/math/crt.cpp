#include "ext_gcd.cpp"

// encontra a solução para o sistema
// x == a mod m
// x == b mod n
//
// uma solução existe se e somente se
// gcd(n, m) dividir a - b
//
// a solução é única módulo lcm(n, m)
// 
ll crt(ll a, ll m, ll b, ll n) {
    if (n > m) swap(a, b), swap(m, n);
    ll x, y, g = ext_gcd(m, n, x, y);
    if((a - b) % g != 0) return -1;
    x = (b - a) % n * x % n / g * m + a;
    return x < 0 ? x + m*n/g : x;
}

