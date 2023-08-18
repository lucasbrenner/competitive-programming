#include "../primitives/mint.cpp"

const ll N = 2e5 + 1, mod = 1e9 + 7;
Int fn[N], fd[N], iv[N];

void initnck() {
    iv[1] = fn[1] = fd[1] = fn[0] = fd[0] = 1;
    for (ll i = 2; i < N; i++){
        iv[i] = Int() - iv[mod % i] * (mod / i);
        fn[i] = fn[i - 1] * i;
        fd[i] = fd[i - 1] * iv[i];
    }
}

Int nck(int n, int k) {
    return fn[n] * fd[n - k] * fd[k];
}

