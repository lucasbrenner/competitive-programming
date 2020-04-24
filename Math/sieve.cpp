#include<bits/stdc++.h>
using namespace std;

int const N = 2e5 + 1;

vector<int> primes;
void sieve(int n){
    bool prime[n+1];
    memset(prime, 1, sizeof prime);
    for (int p=2; p*p<=n; p++){
        if (prime[p]){
            for (int i=p*p; i<=n; i+=p) prime[i] = 0;
        }
    }
    for (int i=2; i<=n; i++) if (prime[i]) primes.push_back(i);
}

int main(){
    sieve(50);
    for (int x : primes) cout << x << " ";
    cout << endl;
}
