#include"bits/stdc++.h"
using namespace std;

#define endl '\n'

vector<int> manacher(const string &s) {
    string t = "$#";
    for (int i = 0; i < s.size(); i++){
        t += s[i];
        t += '#';
    }
    t += '@';
    vector<int> a(t.size() + 1), only_odd(s.size());
    for (int i = 2, c = 1, r = 1; i < t.size()-1; i++){
        int m = 2 * c - i;
        if (i < r) a[i] = min(r - i, a[m]);
        while (t[i - a[i] - 1] == t[i + a[i] + 1]) a[i]++;
        if (i + a[i] > r) {
            c = i;
            r = i + a[i];
        }
    }
    for (int i = 2, p = 0; i < t.size() - 1; i += 2) only_odd[p++] = a[i];
    return a;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    string s = "abacaba";
    vector<int> m = manacher(s);
    for (int i = 0; i < m.size(); i++) cout << m[i] << " \n"[i == m.size() - 1];
}
