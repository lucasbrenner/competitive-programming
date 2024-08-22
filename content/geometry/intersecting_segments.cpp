// tested on timus 1469
// need point and onSegment (kactl)

bool segInter(point a, point b, point c, point d) {
    auto oa = c.cross(d, a), ob = c.cross(d, b),
         oc = a.cross(b, c), od = a.cross(b, d);
    if (sgn(oa) * sgn(ob) < 0 && sgn(oc) * sgn(od) < 0) return true;
    if (onSegment(c, d, a)) return true;
    if (onSegment(c, d, b)) return true;
    if (onSegment(a, b, c)) return true;
    if (onSegment(a, b, d)) return true;
    return false;
}

const double eps = 1e-9;
struct seg {
    point a, b;
    int idx;
    double get_y(double x) const {
        if (a.x == b.x) return a.y;
        return a.y + (b.y - a.y) * (x - a.x) / (b.x - a.x);
    }
    bool operator < (const seg &other) const {
        ll x = max(a.x, other.a.x);
        return get_y(x) < other.get_y(x) - eps;
    }
};

struct event {
    ll x, type, idx;
    bool operator < (const event &other) const {
        if (x == other.x) return type < other.type;
        return x < other.x;
    }
};

pair<int, int> solve(vector<seg> a) {
    int n = sz(a);
    vector<event> evs;
    rep(i, 0, n) {
        if (a[i].a.x > a[i].b.x || (a[i].a.x == a[i].b.x &&
            a[i].a.y > a[i].b.y)) swap(a[i].a, a[i].b);
        evs.push_back({a[i].a.x, 0, i});
        evs.push_back({a[i].b.x, 1, i});
    }
    sort(all(evs));

    auto intersect = [&](int i, int j) {
        return segInter(a[i].a, a[i].b, a[j].a, a[j].b);
    };

    set<seg> s;
    for (auto [x, type, i] : evs) {
        if (type) {
            auto it = s.find(a[i]);
            if (it != s.begin()) {
                auto prv = prev(it);
                auto nxt = next(it);
                if (nxt != s.end() && intersect(prv->idx, nxt->idx)) {
                    return { prv->idx, nxt->idx };
                }
            }
            s.erase(it);
        } else {
            auto it = s.lower_bound(a[i]);
            if (it != s.end() && intersect(i, it->idx)) {
                return { i, it->idx };
            }
            if (it != s.begin() && intersect(i, prev(it)->idx)) {
                return { i, prev(it)->idx };
            }
            s.insert(a[i]);
        }
    }
    return { -1, -1 };
}

