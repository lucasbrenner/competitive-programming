#include "../contest/template.cpp"

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

