#include "../contest/template.cpp"

const ld eps = 1e-6;
template<typename T>
pair<int, vector<T>> gauss(vector<vector<T>> a, vector<T> b){
    int n = sz(a), m = sz(a[0]);
    rep(i,0,n) a[i].push_back(b[i]);

    vector<int> pivot(m, -1);
    int f = 0;
    rep(i,0,m){
        rep(j,f,n){
            if(fabs(a[j][i]) < eps) continue;
            
            swap(a[j], a[f]);
            T div = a[f][i];
            for(auto &x: a[f]) x /= div;
            pivot[i] = f++;
            break;
        }

        if(pivot[i] == -1) continue;
        rep(j,0,n){
            if(j == f - 1) continue;
            T div = a[j][i];
            rep(k,0,m + 1) a[j][k] -= a[f - 1][k] * div;
        }       
    }

    vector<T> ans(m);
    rep(i,0,m){
        if(pivot[i] == -1) continue;
        ans[i] = a[pivot[i]].back();
    }

    rep(i,0,n){
        T res = 0;
        rep(j,0,m){
            res += a[i][j] * ans[j];
        }        
        if(fabs(res - a[i].back()) > eps){
            return {0, {}};
        }
    }

    if(f == m) return {1, ans};
    return {2, ans};
}
