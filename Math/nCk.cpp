#include"bits/stdc++.h"
using namespace std;

typedef long long ll;

const long long N = 2e5 + 1, mod = 1e9 + 7;
long long fn[N], fd[N], iv[N];


void initnck() {
    iv[1] = fn[1] = fd[1] = fn[0] = fd[0] = 1;
    for (ll i = 2; i < N; i++){
        iv[i] = (mod - (mod / i) * iv[mod % i] % mod) % mod;
        fn[i] = fn[i - 1] * i % mod;
        fd[i] = fd[i - 1] * iv[i] % mod;
    }
}

ll nck(ll n, ll k) {
    return fn[n] * fd[n - k] % mod * fd[k] % mod;
}

int main() {
    initnck();
    cout << nck(5, 2) << endl;
}

