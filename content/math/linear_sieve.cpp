#include "../contest/template.cpp"

const int MAX = 1e7;
int lp[MAX + 1];
vector<int> pr;

void linear_sieve() {
    rep(i, 2, MAX + 1) {
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

