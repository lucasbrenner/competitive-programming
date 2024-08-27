// https://codeforces.com/contest/1083/problem/E
#include "../contest/template.cpp"

struct line {
    ll a, b;
    ll eval(ll x) {
        return a * x + b;
    }
    long double inter(const line &oth) const {
        return (long double) (-b + oth.b) / (a - oth.a);
    }
};

// non-increasing slope, non-increasing queries, max queries
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

