#include "../contest/template.cpp"

const int LG = 29;
struct trie {
    trie *ch[2];

    trie() { ch[0] = ch[1] = nullptr; }
    void insert(int x, int bit = LG) {
        if (bit < 0) return;

        int nxt = (x & (1 << bit)) > 0;
        if (!ch[nxt]) ch[nxt] = new trie();
        ch[nxt]->insert(x, bit - 1);
    }
    int xor_min(int x, int bit = LG) {
        if (bit < 0) return 0;

        int nxt = (x & (1 << bit)) > 0;
        if (ch[nxt]) return ch[nxt]->xor_min(x, bit - 1);
        return (1 << bit) + ch[nxt ^ 1]->xor_min(x, bit - 1);
    }
    int xor_max(int x, int bit = LG) {
        if (bit < 0) return 0;

        int nxt = (x & (1 << bit)) > 0;
        if (ch[nxt ^ 1]) return (1 << bit) + ch[nxt ^ 1]->xor_max(x, bit - 1);
        return ch[nxt]->xor_max(x, bit - 1);
    }
    void get_all(vector<int> &v, int bit = LG, int x = 0) {
        if (bit < 0) {
            v.push_back(x);
            return;
        }
        if (ch[0]) ch[0]->get_all(v, bit - 1, x);
        if (ch[1]) ch[1]->get_all(v, bit - 1, x | (1 << bit));
    }
};

