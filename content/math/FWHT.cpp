#include "../contest/template.cpp"

// Fast Walsh Hadamard Transform
//
// FWHT<'|'>(f) eh SOS DP
// FWHT<'&'>(f) eh soma de superset DP
// Se chamar com ^, usar tamanho potencia de 2!!
//
// O(n log(n))

template<char op, class T> vector<T> FWHT(vector<T> f, bool inv = false) {
    int n = f.size();
    for (int k = 0; (n-1)>>k; k++) for (int i = 0; i < n; i++) if (i>>k&1) {
        int j = i^(1<<k);
        if (op == '^') f[j] += f[i], f[i] = f[j] - f[i] * 2;
        if (op == '|') f[i] += f[j] * (inv ? -1 : 1);
        if (op == '&') f[j] += f[i] * (inv ? -1 : 1);
    }
    if (op == '^' and inv) for (auto& i : f) i /= n;
    return f;
}

template<char op> vl conv(vl a, vl b) {
    a = FWHT<op>(a), b = FWHT<op>(b);
    rep(i, 0, sz(a)) a[i] *= b[i];
    a = FWHT<op>(a, 1);
    return a;
}

