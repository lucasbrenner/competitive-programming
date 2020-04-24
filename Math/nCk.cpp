#include<bits/stdc++.h>
using namespace std;

long long const N = 2e5 + 1, M = 1e9 + 7;
long long fn[N], fd[N], iv[N];

void initnck(){
    iv[1] = fn[1] = fd[1] = fn[0] = fd[0] = 1;
    for (long long i=2; i<N; i++){
        iv[i] = (M - (M/i) * iv[M%i] % M) % M;
        fn[i] = fn[i-1]*i%M;
        fd[i] = fd[i-1]*iv[i]%M;
    }
}

long long nck(long long n, long long k){
    return fn[n] * fd[n-k] % M * fd[k] % M;
}

int main(){
    initnck();
    cout << nck(5, 2) << endl;
}
