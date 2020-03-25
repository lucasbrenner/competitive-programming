#include<bits/stdc++.h>
using namespace std;

vector<int> suffix_array(string s){
    int n = s.size();
    vector<int> ans(n), rnk(n), temp_rnk(n);
    
    for (int i=0; i<n; i++){
        ans[i] = i;
        rnk[i] = s[i] - 'a';
    }

    function<int (int)> gr = [&](int i){ return (i < n ? rnk[i] : -1); }; //get rank

    for (int d=1; d<=n; d <<= 1){
        sort(ans.begin(), ans.end(),
            [&](int i, int j) -> bool{return make_pair(gr(i), gr(i+d)) < make_pair(gr(j), gr(j+d));});
        
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
    string s = "abacaba";
    vector<int> t = suffix_array(s);
    for (int x : t) cout << x << " ";
}