#include "../contest/template.cpp"

struct frac {
    ll num, den;
    frac() : num(0), den(1) {}
    frac(ll x) : num(x), den(1) {}
    frac(ll x, ll y) : num(x), den(y) {}
    void norm() {
        if (den < 0) num = -num, den = -den;
        ll g = gcd(num, den);
        num /= g, den /= g;
    }
    frac& operator += (frac o) {
        num = num * o.den + o.num * den, den = den * o.den;
        norm();
        return *this;
    }
    frac& operator -= (frac o) {
        num = num * o.den - o.num * den, den = den * o.den;
        norm();
        return *this;
    }
    frac& operator *= (frac o) {
        num = num * o.num, den = den * o.den;
        norm();
        return *this;
    }
    frac& operator /= (frac o) {
        num = num * o.den, den = den * o.num;
        norm();
        return *this;
    }
    bool operator < (frac o) const { return num * o.den < den * o.num; }
    frac operator + (frac o) const { return frac(*this) += o; }
    frac operator - (frac o) const { return frac(*this) -= o; }
    frac operator * (frac o) const { return frac(*this) *= o; }
    frac operator / (frac o) const { return frac(*this) /= o; }
    string tos() { return to_string(num) + "/" + to_string(den); }
};

