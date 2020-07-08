#include<bits/stdc++.h>
using namespace std;

int const N = 100001, LG = 33 - __builtin_clz(N);
int anc[N][LG], n, prof[N];
vector<int> adj[N];

void dfs(int v=1, int p=-1, int d=1){
    prof[v] = d;
    for (int c : adj[v]){
        if (c == p) continue;
        anc[c][0] = v;
        dfs(c, v, d+1);
    }
}

void initlca(){
    dfs();
    for (int i=1; i<LG; i++){
        for (int v=1; v<=n; v++){
            if (prof[v] - (1 << i) < 1) continue;
            anc[v][i] = anc[anc[v][i-1]][i-1];
        }
    }
}

int lca(int a, int b){
    if (prof[a] < prof[b]) swap(a, b);
    for (int i=LG-1; i>=0; i--){
        if (prof[a] - prof[b]  >= (1 << i)) a = anc[a][i];
    }
    if (a == b) return a;
    for (int i=LG-1; i>=0; i--){
        if (anc[a][i] != anc[b][i]){
            a = anc[a][i];
            b = anc[b][i];
        }
    }
    return anc[a][0];
}

int main(){
    cin >> n;
    for (int i=1; i<n; i++){
        int u,v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    initlca();
    int q; cin >> q;
    while(q--){
        int a,b; cin >> a >> b;
        cout << lca(a,b) << endl;
    }
}