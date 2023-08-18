#include "../contest/template.cpp"

const int MOD_COUNT = 3;
const ll BASE[] = { 104000711, 104000717, 1000000007 };

struct hsh {
    int a[MOD_COUNT];
    hsh() {
        for (int i = 0; i < MOD_COUNT; i++) a[i] = 1;
    }
    bool operator < (const hsh &o) const {
        for (int i = 0; i < MOD_COUNT; i++) {
            if (a[i] < o.a[i]) return true;
            if (a[i] > o.a[i]) return false;
        }
        return false;
    }
    bool operator == (const hsh &o) const {
        for (int i = 0; i < MOD_COUNT; i++) if (a[i] != o.a[i]) return false;
        return true;
    }
};

