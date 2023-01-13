#include"bits/stdc++.h"
using namespace std;

typedef long long ll;

const ll mod = 1e9 + 7;
ll fpow(ll b, ll e) {
    b %= mod;
    ll ans = 1;
    while (e > 0) {
        if (e & 1ll) ans = ans * b % mod;
        b = b * b % mod;
        e >>= 1ll;
    }
    return ans;
}

int main() {
    ll b, e; cin >> b >> e;
    cout << fpow(b, e) << endl;
}

