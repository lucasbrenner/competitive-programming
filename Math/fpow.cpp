#include<bits/stdc++.h>
using namespace std;

const long long MOD = 1000000007;
long long fpow(long long b, long long e){
    b %= MOD;
    long long ans = 1;
    while (e > 0) {
        if (e & 1ll) ans = ans * b % MOD;
        b = b * b % MOD;
        e >>= 1ll;
    }
    return ans;
}

int main(){
    long long b, e; cin >> b >> e;
    cout << fpow(b, e) << endl;
}
