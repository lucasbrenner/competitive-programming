#include<bits/stdc++.h>
using namespace std;

#define endl '\n'

int manacher(string& s){
    string t = "$#";
    for (int i=0; i<s.size(); i++){
        t += s[i];
        t += '#';
    }
    t += '@';
    int a[t.size()+1], c = 1, r = 1, ans = 0;
    memset(a, 0, sizeof a);
    for (int i=2; i<t.size()-1; i++){
        int m = 2*c - i;
        if (i < r) a[i] = min(r - i, a[m]);
        
        while(t[i - a[i] - 1] == t[i + a[i] + 1]) a[i]++;
        if (i + a[i] > r){
            c = i;
            r = i + a[i];
        }
        ans = max(ans, a[i]);
    }
    return ans;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    string s; cin >> s;
    cout << manacher(s) << endl;
}
