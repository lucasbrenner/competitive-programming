#include "../contest/template.cpp"

const int MAX = 1e6+10;

bool prime[MAX];
int mobius[MAX];

void build_mobius(){
    memset(mobius, -1, sizeof mobius);
    mobius[1] = 1;
    rep(i,2,MAX) prime[i] = 1;

    for(ll i = 2; i < MAX; i++){
        if(!prime[i]) continue;
        for(ll j = i; j < MAX; j += i){
            mobius[j] *= -1;
            prime[j] = false;
        }
        prime[i] = 1;

        for(ll j = 1; i * i * j < MAX; j++){
            mobius[i * i * j] = 0;
        }
    }
}
