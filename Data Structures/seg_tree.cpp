#include <bits/stdc++.h>
using namespace std;
 
template<typename T>
struct seg_tree{
    int n;
    vector<T> tree, start;

    seg_tree(vector<T> start_) : start(start_){
        n = start_.size();
        tree.resize(n * 4);
        build(1, 1, n);
    }

    seg_tree(int n_) : n(n_){
        seg_tree(vector<T>(n_));
    }

    T identity(){
        return 0;
    }

    T merge(T a, T b){
        return a + b;
    }
    
    void build(int id, int l, int r){
        if (l == r) tree[id] = start[l-1];
        else{
            int m = (l+r)>>1;
            build(id<<1, l, m);
            build(id<<1|1, m+1, r);
            tree[id] = merge(tree[id<<1], tree[id<<1|1]);
        }
    }

    void upd(int id, int l, int r, int pos, T val){
        if (l == r) tree[id] = val;
        else{
            int m = (l+r)>>1;
            if (pos <= m) upd(id<<1, l, m, pos, val);
            else upd(id<<1|1, m+1, r, pos, val);
            tree[id] = merge(tree[id<<1], tree[id<<1|1]);
        }
    }

    T qry(int id, int l, int r, int lq, int rq){
        if (l > rq || r < lq) return identity();
        else if (lq <= l && r <= rq) return tree[id];
        else{
            int m = (l+r)>>1;
            return merge(qry(id<<1, l, m, lq, rq), qry(id<<1|1, m+1, r, lq, rq));
        }
    }

    void upd(int pos, T val){upd(1, 1, n, pos, val);}
    T qry(int l, int r){return qry(1, 1, n, l, r);}
};

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n,q; cin >> n >> q;
    vector<long long> a(n);
    for (int i=0; i<n; i++) cin >> a[i];
    seg_tree<long long> stree(a);
    while(q--){
        int tp, a, b; cin >> tp >> a >> b;
        if (tp == 1) stree.upd(a, b);
        else cout << stree.qry(a, b) << '\n';
    }
}