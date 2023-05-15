// tested on https://cses.fi/problemset/task/2084/
#include "bits/stdc++.h"
using namespace std;

typedef long long ll;

struct line {
    ll a, b;
    ll eval(ll x) {
        return a * x + b;
    }
    ll inter(const line &oth) const {
        ll num = -b + oth.b, den = a - oth.a;
        if ((num < 0) ^ (den < 0)) return num / den;
        num = abs(num), den = abs(den);
        return - (num + den - 1) / den;
    }
};

// non-increasing slope, non-decreasing queries
struct cht {
    deque<line> q;
    void add(ll a, ll b) {
        line cur = { a, b };
        while (q.size() > 1) {
            if (q.back().a == a) {
                if (b >= q.back().b) return;
                q.pop_back();
                continue;
            }
            if (cur.inter(q[q.size() - 1]) < cur.inter(q[q.size() - 2])) break;
            q.pop_back();
        }
        q.push_back(cur);
    }
    ll query(ll x) {
        while (q.size() > 1 && q[0].eval(x) >= q[1].eval(x)) q.pop_front();
        return q[0].eval(x);
    }
};

