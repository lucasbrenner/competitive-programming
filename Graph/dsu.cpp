#include <bits/stdc++.h>
using namespace std;

struct dsu{
    int n;
    vector<int> p, rnk;

    dsu(int n_) : n(n_){
        p.resize(n+1, 0);
        iota(p.begin(), p.end(), 0);
        rnk.resize(n+1, 1);
    }

    int find(int x){
        if (p[x] == x) return x;
        return p[x] = find(p[x]);
    }

    bool join(int a, int b){
        a = find(a); b = find(b);
        if (a == b) return false;
        if (rnk[a] > rnk[b]){
            p[b] = a;
            rnk[a] += rnk[b];
        } else{
            p[a] = b;
            rnk[b] += rnk[a];
        }
        return true;
    }
};
 
int main(){
}