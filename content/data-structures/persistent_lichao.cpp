// tested on https://codeforces.com/group/XrhoJtxCjm/contest/422715/problem/K
#include "../contest/template.cpp"

const ll INF = 1e18;
struct PersistentLiChaoTree {
    PersistentLiChaoTree() {
        tree.push_back({-1, -1, s, e, Line(0, -INF)});
    }

    struct Line {
        int idx;
        ll a, b;
        Line(ll a, ll b, int idx = -1) : a(a), b(b), idx(idx) {}
        Line() {}
        ll f(ll x) {
            return a * x + b;
        }

        bool best(Line ot, ll x) {
            return f(x) > ot.f(x);
        }
    };
    Line best(Line a, Line b, ll x) {
        return (a.best(b, x) ? a : b);
    };

    struct Node {
        int l, r;
        ll xl, xr;
        Line line;
        Node(int l, int r, ll xl, ll xr, Line line) : l(l), r(r), xl(xl), xr(xr), line(line) {}
    };

    struct Info {
        int l, r;
        ll a, b;
    };

    vector<Node> tree;
    vector<vector<pair<int, Info>>> change;
    ll s = -2e9, e = 2e9;

    void add_line(Line new_line, int i = 0) {
        ll xl = tree[i].xl, xr = tree[i].xr;
        ll xm = (xl + xr) >> 1;

        change.back().push_back({i, {tree[i].l, tree[i].r, tree[i].line.a, tree[i].line.b}});

        Line low = tree[i].line, high = new_line;
        if (low.best(high, xl)) swap(low, high);

        if (high.best(low, xr)) {
            tree[i].line = high;
            return;
        }else if (high.best(low, xm)) {
            tree[i].line = high;
            if (tree[i].r == -1) {
                tree[i].r = tree.size();
                tree.push_back({-1, -1, xm + 1, xr, Line(0, -INF)});
            }
            add_line(low, tree[i].r);
        }else {
            tree[i].line = low;
            if (tree[i].l == -1) {
                tree[i].l = tree.size();
                tree.push_back({-1, -1, xl, xm, Line(0, -INF)});
            }
            add_line(high, tree[i].l);
        }
    }

    Line query2(ll x, int i = 0) {
        if (i == -1) return Line(0,-INF);
        ll xl = tree[i].xl, xr = tree[i].xr;
        ll xm = (xl + xr) >> 1;
        if (x <= xm) return best(tree[i].line, query2(x, tree[i].l), x);
        else return best(tree[i].line, query2(x, tree[i].r), x);
    }
    ll query(ll x, int i = 0) { return query2(x, i).f(x); }

    void add_line(ll a, ll b) {
        change.push_back({});
        add_line({a, b}, 0);
    }

    void delete_line() {
        for (auto &[i, info] : change.back()) {
            tree[i].l = info.l;
            tree[i].r = info.r;
            tree[i].line.a = info.a;
            tree[i].line.b = info.b;
        }
        change.pop_back();
    }
};
