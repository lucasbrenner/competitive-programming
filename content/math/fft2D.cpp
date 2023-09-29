#include "../contest/template.cpp"

using cd = complex<double>;
const double PI = acos(-1);
 
void fft(vector<cd> & a, bool invert) {
    int n = a.size();
 
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;
 
        if (i < j)
            swap(a[i], a[j]);
    }
 
    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2 * PI / len * (invert ? -1 : 1);
        cd wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len) {
            cd w(1);
            for (int j = 0; j < len / 2; j++) {
                cd u = a[i+j], v = a[i+j+len/2] * w;
                a[i+j] = u + v;
                a[i+j+len/2] = u - v;
                w *= wlen;
            }
        }
    }
 
    if (invert) {
        for (cd & x : a)
            x /= n;
    }
}
 
void fft2D(vector<vector<cd>> &a, bool invert){
    int n = sz(a), m = sz(a[0]);
 
    if(!invert) for(int i = 0; i < n; i++) fft(a[i], invert);
 
    for(int j = 0; j < m; j++){
        vector<cd> col;
        for(int i = 0; i < n; i++){
            col.push_back(a[i][j]);
        }
        fft(col, invert);
        for(int i = 0; i < n; i++){
            a[i][j] = col[i];
        }
    }
 
    if(invert) for(int i = 0; i < n; i++) fft(a[i], invert);
}
 
vector<vector<cd>> conv2D(vector<vector<cd>> a, vector<vector<cd>> b) {
    int n = 1;
    while (n < sz(a) + sz(b)) 
        n <<= 1;
    int m = 1;    
    while (m < sz(a[0]) + sz(b[0])) m <<= 1;
    a.resize(n);
    b.resize(n);
 
    rep(i,0,n){
        a[i].resize(m);
        b[i].resize(m);
    }
 
    fft2D(a, false);
    fft2D(b, false);
    for (int i = 0; i < n; i++) for(int j = 0; j < m; j++)
        a[i][j] *= b[i][j];
        
    fft2D(a, true);
 
    return a;
}
