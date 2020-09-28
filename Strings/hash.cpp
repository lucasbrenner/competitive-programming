#include<bits/stdc++.h>
using namespace std;

const int mxN = 100001;
const vector<long long> base = {307, 317}, mod = {104000711, 104000717};
vector<array<long long, 2>> iv(mxN), p(mxN), h(mxN);
 
long long inverse(int a, int b, int s0 = 1, int s1 = 0){
    return b == 0? s0 : inverse(b, a%b, s1, s0-s1*(a/b));
}
 
void init(const string & s){
    for (int k=0; k<base.size(); k++){
        p[0][k] = iv[0][k] = 1;
        p[1][k] = base[k];
        iv[1][k] = inverse(base[k], mod[k]);
        for (int i=2; i<mxN; i++){
            p[i][k] = p[i-1][k] * p[1][k] % mod[k];
            iv[i][k] = iv[i-1][k] * iv[1][k] % mod[k];
        }
    }
    for (int i=1; i<=s.size(); i++){
        for (int k=0; k<base.size(); k++){
            h[i][k] = (h[i-1][k] + (s[i-1] - 'a' + 1) * p[i][k] % mod[k])%mod[k];
        }
    }
}
 
array<long long, 2> qry(int l, int r){
    l++; r++;
    array<long long, 2> ans;
    for (int k=0; k<base.size(); k++){
        ans[k] = (h[r][k] - h[l-1][k] + mod[k])%mod[k] * iv[l][k] % mod[k];
    }
    return ans;
}