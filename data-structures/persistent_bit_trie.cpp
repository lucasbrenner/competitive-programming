// tested on https://codeforces.com/group/XrhoJtxCjm/contest/422671/problem/H
#include "bits/stdc++.h"
using namespace std;

#define endl '\n'
typedef long long ll;

struct trie {
    struct node {
        int ch[2], cnt;
        node() {
            ch[0] = ch[1] = -1;
            cnt = 0;
        }
    };

    const static int ms = (500000) * 20, LG = 20;
    node buffer[ms];
    int CNT = 1;
    vector<int> vs = { 0 };

    int get_cnt(int v) {
        return v == -1 ? 0 : buffer[v].cnt;
    }

    int get_ch(int v, int bit) {
        return v == -1 ? -1 : buffer[v].ch[bit];
    }

    int insert(int v, int x, int bit) {
        int ans = CNT++;
        if (bit < 0) {
            buffer[ans].cnt = 1 + get_cnt(v);
            return ans;
        }
        int nxt = (x & (1 << bit)) > 0;
        buffer[ans].ch[nxt] = insert(get_ch(v, nxt), x, bit - 1);
        buffer[ans].ch[nxt ^ 1] = get_ch(v, nxt ^ 1);
        buffer[ans].cnt = get_cnt(buffer[ans].ch[0]) + get_cnt(buffer[ans].ch[1]);
        return ans;
    }
    void insert(int x) {
        vs.push_back(insert(vs.back(), x, LG));
    }

    int xor_max(int vl, int vr, int x, int bit) {
        if (bit < 0) return 0;

        int nxt = (x & (1 << bit)) == 0;
        if (get_cnt(get_ch(vr, nxt)) - get_cnt(get_ch(vl, nxt)) > 0) {
            return (1 << bit) + xor_max(get_ch(vl, nxt), get_ch(vr, nxt), x, bit - 1);
        }
        return xor_max(get_ch(vl, nxt ^ 1), get_ch(vr, nxt ^ 1), x, bit - 1);
    }
    int xor_max(int l, int r, int x) {
        return xor_max(vs[l - 1], vs[r], x, LG);
    }

    void erase(int k) {
        while (k--) {
            vs.pop_back();
        }
    }
};

void solvetask() {
    int q; cin >> q;
    trie t;
    while (q--) {
        int tp; cin >> tp;
        if (tp == 0) {
            int x; cin >> x;
            t.insert(x);
        } else if (tp == 1) {
            int l, r, x; cin >> l >> r >> x;
            cout << (t.xor_max(l, r, x) ^ x) << endl;
        } else {
            int k; cin >> k;
            t.erase(k);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t = 1;
    while(t--) solvetask();
}

