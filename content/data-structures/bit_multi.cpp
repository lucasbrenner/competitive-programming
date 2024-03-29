// adapted from https://codeforces.com/blog/entry/64914
#include "../contest/template.cpp"

template <int... ArgsT> struct bit {
    int val = 0;
    void update(int val) { this->val += val; }
    int query() { return val; }
    int pre() { return val; }
};

template <int N, int... Ns> struct bit<N, Ns...> {
    bit<Ns...> b[N + 1];
    template<typename... Args>
    void update(int idx, Args... args) {
        for (; idx <= N; b[idx].update(args...), idx += idx & -idx);
    }
    template<typename... Args>
    int query(int l, int r, Args... args) {
        int ans = 0;
        for (; r >= 1; ans += b[r].query(args...), r -= r & -r);
        for (--l; l >= 1; ans -= b[l].query(args...), l -= l & -l);
        return ans;
    }
    template<typename... Args>
    int pre(int idx, Args... args) {
        int ans = 0;
        for (; idx > 0; ans += b[idx].pre(args...), idx -= idx & -idx);
        return ans;
    }
};

