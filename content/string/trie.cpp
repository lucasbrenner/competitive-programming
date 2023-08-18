#include"bits/stdc++.h"
using namespace std;

const int N = 1e6 + 10;
struct trie {
    struct node {
        bool end;
        int ch[26];
        node() { memset(ch, -1, sizeof ch), end = false; }
    };
    node a[N];
    int head = 0;

    trie() {
    }

    void insert(const string &s) {
        int cur = 0;
        for (int i = 0; i < (int)s.size(); i++) {
            if (a[cur].ch[s[i] - 'a'] == -1) a[cur].ch[s[i] - 'a'] = ++head;
            cur = a[cur].ch[s[i] - 'a'];
        }
        a[cur].end = true;
    }
} tr;

