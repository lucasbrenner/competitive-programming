#include "../contest/template.cpp"

// dados a e b, retorna g = gcd(a, b)
// a * x + b * y = g
//
// podemos encontrar a^-1 mod M da seguinte forma:
// a * x + M * y = 1
// aplicando mod M nos dois lados:
// a * x == 1 (mod M)
// então, basta chamar ext_gcd(a, M, x, y)
// se g != 1, não tem inverso
// se g = 1, o inverso é (x%M + M) % M
ll ext_gcd(ll a, ll b, ll &x, ll &y) {
    if (!b) return x = 1, y = 0, a;
    ll d = ext_gcd(b, a % b, y, x);
    return y -= a/b * x, d;
}

