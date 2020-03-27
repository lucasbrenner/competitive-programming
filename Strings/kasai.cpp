#include<bits/stdc++.h>
using namespace std;

vector<int> kasai(vector<int> sa, string s){
    int n = sa.size();
    vector<int> r(n), lcp(n);
    for (int i=0; i<n; i++) r[sa[i]] = i;

    int h=0;
    for (int i=0; i<n; i++){
        if (r[i] == n-1) h = lcp[n-1] = 0;
        else{
            int j = sa[r[i] + 1];
            while(i + h < n && j + h < n && s[i+h] == s[j+h]) h++;
            lcp[r[i]] = h;
            h = max(0, h-1);
        }
    }
    return lcp;
}