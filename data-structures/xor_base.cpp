#include "bits/stdc++.h"
using namespace std;

#define endl '\n'
typedef long long ll;

struct xor_base {
    const static int B = 60;
    ll b[B], size = 0, free = 0;
    xor_base() { memset(b, 0, sizeof b); }

    void insert(ll x) {
        for (int i = B - 1; i >= 0; i--) {
            if (x & (1ll << i)) {
                if (!b[i]) {
                    size++;
                    b[i] = x;
                    return;
                }
                x ^= b[i];
            }
        }
        free++;
    }

    ll kth(ll k) {
        ll ans = 0, n = (1ll << size);
        for (int i = B - 1; i >= 0; i--) {
            if (!b[i]) continue;
            
            if ((k <= n / 2) ^ ((ans & (1ll << i)) == 0)) ans ^= b[i];
            if (k > n / 2) k -= n / 2;
            n /= 2;
        }
        return ans;
    }

    bool contains(ll x) {
        for (int i = B - 1; i >= 0; i--) {
            if (x & (1ll << i)) {
                if (!b[i]) {
                    return false;
                }
                x ^= b[i];
            }
        }
        return true;
    }
};

