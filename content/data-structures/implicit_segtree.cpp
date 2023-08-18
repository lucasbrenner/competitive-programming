#include "bits/stdc++.h"
using namespace std;

#define endl '\n'
typedef long long ll;
std::mt19937 rng((int) std::chrono::steady_clock::now().time_since_epoch().count());

struct Data {
    ll sum;
    Data() {
        sum = 0;
    }
    Data operator + (const Data &oth) const {
        Data ans;
        ans.sum = sum + oth.sum;
        return ans;
    }
};

struct Vertex {
    int l, r;
    Data info;
    Vertex *lc = nullptr, *rc = nullptr;

    Vertex(int lb, int rb) {
        l = lb;
        r = rb;
        info.sum = 0;
    }

    void extend() {
        if (!lc && l != r) {
            int mid = (l + r) / 2;
            lc = new Vertex(l, mid);
            rc = new Vertex(mid + 1, r);
        }
    }

    void update(int pos, int val) {
        if (l == r) {
            info.sum = val;
        } else {
            extend();
            int mid = (l + r) / 2;
            if (pos <= mid) lc->update(pos, val);
            else rc->update(pos, val);
            info = lc->info + rc->info;
        }
    }

    Data query(int lq, int rq) {
        if (lq <= l && r <= rq) return info;
        if (l > rq || r < lq) return Data();
        extend();
        return lc->query(lq, rq) + rc->query(lq, rq);
    }
};

