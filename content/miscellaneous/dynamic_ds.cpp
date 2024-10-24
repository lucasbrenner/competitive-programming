#include"../contest/template.cpp"

template<class ds, class T> struct dynamic_ds {
    vector<ds> a = { ds() };
    vector<vector<T>> at = { {} };
    dynamic_ds() {}
    void insert(const T &val) {
        at[0].push_back(val);
        rep(i, 0, sz(a)) {
            if (sz(at[i]) > (1 << i)) {
                if (i == sz(a) - 1) {
                    at.push_back({});
                    a.push_back(ds());
                }
                for (T x : at[i]) {
                    at[i + 1].push_back(x);
                }
                at[i].clear();
                a[i] = ds();
                continue;
            }
            a[i] = ds();
            for (T x : at[i]) {
                a[i].insert(x);
            }
            a[i].build();
            break;
        }
    }
    ll query(const T &val) {
        ll ans = 0;
        rep(i, 0, sz(a)) ans += a[i].query(val);
        return ans;
    }
};

