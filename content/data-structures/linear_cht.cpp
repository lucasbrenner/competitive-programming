// https://codeforces.com/contest/1083/problem/E
#include "bits/stdc++.h"
using namespace std;

#define endl '\n'
typedef long long ll;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

struct line {
    ll a, b;
    ll eval(ll x) {
        return a * x + b;
    }
    long double inter(const line &oth) const {
        return (long double) (-b + oth.b) / (a - oth.a);
    }
};

// non-increasing slope, non-decreasing queries
// max queries
struct cht {
    deque<line> q;
    void add(ll a, ll b) {
        line cur = { a, b };
        while (q.size() > 1) {
            if (q.back().a == a) {
                if (b <= q.back().b) return;
                q.pop_back();
                continue;
            }
            if (cur.inter(q[q.size() - 1]) < cur.inter(q[q.size() - 2])) break;
            q.pop_back();
        }
        q.push_back(cur);
    }
    ll query(ll x) {
        while (q.size() > 1 && q[0].eval(x) <= q[1].eval(x)) q.pop_front();
        return q[0].eval(x);
    }
};

void solvetask() {
    int n; cin >> n;
    vector<array<ll, 3>> a(n);
    for (auto &[x, y, c] : a) cin >> x >> y >> c;
    sort(a.begin(), a.end());
    vector<ll> dp(n);
    cht t;
    t.add(0, 0);
    for (int i = 0; auto [x, y, c] : a) {
        dp[i] = t.query(y) + x * y - c;
        t.add(-x, dp[i]);
        i++;
    }
    cout << *max_element(dp.begin(), dp.end()) << endl;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t = 1;
    while(t--) solvetask();
}

