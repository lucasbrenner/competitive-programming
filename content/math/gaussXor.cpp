#include "../contest/template.cpp"

const int N = 103;
pair<int, vector<bool>> gaussXor(vector<bitset<N>> a, vector<bool> b){
    int n = sz(a), m = N - 1;
    rep(i,0,n) a[i][N - 1] = b[i];

    vector<int> pivot(m, -1);
    int f = 0;
    rep(i,0,m){
        rep(j,f,n){
            if(!a[j][i]) continue;
            
            swap(a[j], a[f]);
            pivot[i] = f++;
            break;
        }

        if(pivot[i] == -1) continue;
        rep(j,0,n){
            if(j == f - 1 || !a[j][i]) continue;
            a[j] ^= a[f - 1];
        }       
    }
    vector<bool> ans(m);
    for(int i = m - 1; i >= 0; i--){
        if(pivot[i] == -1) continue;
        ans[i] = a[pivot[i]][N - 1];
    }

    rep(i,0,n){
        bool res = 0;
        rep(j,0,m){
            res ^= (a[i][j] & ans[j]);
        }        
        if(res != a[i][N - 1]){
            return {0, {}};
        }
    }
    if(f == m) return {1, ans};
    return {2, ans};
}
