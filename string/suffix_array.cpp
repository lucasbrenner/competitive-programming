#include<bits/stdc++.h>
using namespace std;

vector<int> suffix_array(string s){
    int n = s.size(), alf = max(256, n+2);
    vector<int> ans, rnk(n), temp_rnk(n), aux[alf];
    
    for (int i=0; i<n; i++) rnk[i] = s[i];

    function<int (int)> gr = [&](int i){ return (i < n ? rnk[i] : -1); }; //get rank

    for (int d=1; d<=n; d <<= 1){

        ans.clear();
        for (int i=0; i<n; i++) aux[gr(i+d)+1].push_back(i);
        for (int i=0; i<alf; i++){
            for (int j=0; j<aux[i].size(); j++){
                ans.push_back(aux[i][j]);
            }
            aux[i].clear();
        }
        for (int i=0; i<n; i++) aux[gr(ans[i])].push_back(ans[i]);
        ans.clear();
        for (int i=0; i<alf; i++){
            for (int j=0; j<aux[i].size(); j++){
                ans.push_back(aux[i][j]);
            }
            aux[i].clear();
        }

        temp_rnk[ans[0]] = 0;
        for (int i=1; i<n; i++){
            temp_rnk[ans[i]] = temp_rnk[ans[i-1]] + (make_pair(gr(ans[i]), gr(ans[i]+d)) != make_pair(gr(ans[i-1]), gr(ans[i-1]+d)));
        }
        rnk = temp_rnk;
        if (rnk[ans[n-1]] == n-1) break;
    }
    return ans;
}

int main(){
    string s; cin >> s;

    vector<int> a = suffix_array(s);
    for (int i=0; i<a.size(); i++) cout << a[i] << " \n"[i == a.size()-1];
}
