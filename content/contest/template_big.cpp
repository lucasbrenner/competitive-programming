#include "bits/stdc++.h"
using namespace std;
//#pragma once
//#pragma GCC optimize("O3,unroll-loops")
//#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#define endl '\n'
#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
#define sq(x) (x)*(x)
template<class T, class U> inline void chmin(T& a, U b) { if (a > b) a = b; }
template<class T, class U> inline void chmax(T& a, U b) { if (a < b) a = b; }
mt19937 rng((int) chrono::steady_clock::now().time_since_epoch().count());
typedef long long ll;
typedef long double ld;
typedef __int128 i128;

void solve_tc() {
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int tc = 1;
    cin >> tc;
    while (tc--) solve_tc();
}

