#include<bits/stdc++.h>
using namespace std;

long long const M = 1000000007;
long long fpow(long long b, long long e){
    if (e == 0) return 1LL;
    if (e == 1) return b;
    if (e & 1LL) return b * fpow(b, e-1) % M;
    long long temp = fpow(b, e/2LL);
    return temp * temp % M;
}

int main(){
    cout << fpow(2, 5) << endl;
}