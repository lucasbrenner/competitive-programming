#include "bits/stdc++.h"
using namespace std;
 
#define endl '\n'
 
struct bit {
    int n;
    vector<vector<int>> a;
    bit (int n_) {
        n = n_;
        a = vector<vector<int>>(n + 1, vector<int>(n + 1));
    }
 
    void add(int i, int j, int val) {
        for (; i <= n; i += i & -i) {
            for (int pos = j; pos <= n; pos += pos & -pos) {
                a[i][pos] += val;
            }
        }
    }
    int query(int i, int j) {
        int ans = 0;
        for (; i > 0; i -= i & -i) {
            for (int pos = j; pos > 0; pos -= pos & -pos) {
                ans += a[i][pos];
            }
        }
        return ans;
    }
};
 
