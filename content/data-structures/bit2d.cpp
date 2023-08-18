#include "../contest/template.cpp"
 
template<typename T> struct bit {
    int n;
    vector<vector<T>> a;
    bit (int n) : n(n), a(n + 1, vector<int>(n + 1)) {}
    void add(int i, int j, T val) {
        for (; i <= n; i += i & -i) {
            for (int pos = j; pos <= n; pos += pos & -pos) {
                a[i][pos] += val;
            }
        }
    }
    T query(int i, int j) {
        T ans = 0;
        for (; i > 0; i -= i & -i) {
            for (int pos = j; pos > 0; pos -= pos & -pos) {
                ans += a[i][pos];
            }
        }
        return ans;
    }
};
 
