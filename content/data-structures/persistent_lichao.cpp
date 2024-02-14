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
        if (low.f(xl) >= high.f(xl)) swap(low, high);

        if (low.f(xr) <= high.f(xr)) {
            tree[i].line = high;
            return;
        }

        else if (low.f(xm) <= high.f(xm)) {
            tree[i].line = high;
            if (tree[i].r == -1)
            {
                tree[i].r = tree.size();
                tree.push_back({-1, -1, xm + 1, xr, Line(0, -INF)});
            }
            add_line(low, tree[i].r);
        }

        else {
            tree[i].line = low;
            if (tree[i].l == -1) {
                tree[i].l = tree.size();
                tree.push_back({-1, -1, xl, xm, Line(0, -INF)});
            }
            add_line(high, tree[i].l);
        }
    }

    ll query(ll x, int i = 0) {
        if (i == -1) return -INF;
        ll xl = tree[i].xl, xr = tree[i].xr;
        ll xm = (xl + xr) >> 1;
        if (x <= xm) return max(tree[i].line.f(x), query(x, tree[i].l));
        else return max(tree[i].line.f(x), query(x, tree[i].r));
    }

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