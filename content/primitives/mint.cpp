#include "../contest/template.cpp"

template<int mod = (int)1e9 + 7>
struct mint {
    int x;
    mint() : x(0) {}
    mint(ll _x) { _x %= mod; if (_x < 0) _x += mod; x = _x; }
    mint& operator += (mint o) { x += o.x; if (x >= mod) x -= mod; return *this; }
    mint& operator -= (mint o) { x -= o.x; if (x < 0) x += mod; return *this; }
    mint& operator *= (mint o) { x = (ll)x * o.x % mod; return *this; }
    mint& operator /= (mint o) {
        ll a = o.x, b = mod, u = 1, v = 0;
        while (b > 0) {
            ll t = a / b;
            a -= t * b; swap(a, b);
            u -= t * v; swap(u, v);
        }
        if (u < 0) u += mod;
        return *this *= u;
    }
    mint& operator ^= (ll e) { 
        ll b = x; x = 1;
        while (e > 0) {
            if (e & 1ll) x = x * b % mod;
            b = b * b % mod, e >>= 1ll;
        }
        return *this;
    }
    mint operator + (mint o) const { return mint(*this) += o; }
    mint operator - (mint o) const { return mint(*this) -= o; }
    mint operator * (mint o) const { return mint(*this) *= o; }
    mint operator / (mint o) const { return mint(*this) /= o; }
    mint operator ^ (ll o) const { return mint(*this) ^= o; }
    bool operator < (mint o) const { return x < o.x; }
    bool operator == (mint o) const { return x == o.x; }
    bool operator != (mint o) const { return x != o.x; }
};

template <typename U, int mod>
U& operator >> (U& is, mint<mod>& number) {
    ll x;
    is >> x;
    number = mint(x);
    return is;
}

template<typename U, int mod>
U& operator << (U& os, mint<mod>& number){
    os << number.x;
    return os;
}

using Int = mint<(int)1e9 + 7>;
