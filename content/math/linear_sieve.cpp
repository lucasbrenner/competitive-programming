#include"bits/stdc++.h"
using namespace std;

const int MAX = 1e7;
int lp[MAX + 1];
vector<int> pr;

void linear_sieve() {
    for (int i = 2; i <= MAX; i++) {
        if (lp[i] == 0) {
            lp[i] = i;
            pr.push_back(i);
        }
        for (int j = 0; i * pr[j] <= MAX; j++) {
            lp[i * pr[j]] = pr[j];
            if (pr[j] == lp[i]) break;
        }
    }
}

