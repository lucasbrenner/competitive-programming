#include <bits/stdc++.h>
using namespace std;

template<typename T>
struct seg_tree{
    int n;
    vector<T> tree, start, lazy;

    seg_tree(vector<T> start_) : start(start_){
        n = start_.size();
        tree.resize(n * 4);
        lazy.resize(n * 4);
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

    void prop(int id, int l, int r){
        if (lazy[id]){
            tree[id] += lazy[id] * (r - l + 1); // merge / set
            if (l != r){
                lazy[id<<1] += lazy[id];
                lazy[id<<1|1] += lazy[id];
            }
            lazy[id] = 0;
        }
    }

    void upd(int id, int l, int r, int lq, int rq, T val){
        if (l > rq || r < lq) prop(id, l, r);
        else if (lq <= l && r <= rq){
            lazy[id] += val;
            prop(id, l, r);
        } else{
            prop(id, l, r);
            int m = (l+r)>>1;
            upd(id<<1, l, m, lq, rq, val);
            upd(id<<1|1, m+1, r, lq, rq, val);
            tree[id] = merge(tree[id<<1], tree[id<<1|1]);
        }
    }

    T qry(int id, int l, int r, int lq, int rq){
        prop(id, l, r);
        if (l > rq || r < lq) return identity();
        if (lq <= l && r <= rq) return tree[id];
        int m = (l+r)>>1;
        return merge(qry(id<<1, l, m, lq, rq), qry(id<<1|1, m+1, r, lq, rq));
    }

    void upd(int pos, T val){upd(1, 1, n, pos, pos, val);}
    void upd(int l, int r, T val){upd(1, 1, n, l, r, val);}
    T qry(int l, int r){return qry(1, 1, n ,l, r);}
    T qry(int pos){return qry(1, 1, n , pos, pos);}
};

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n,q; cin >> n >> q;
    vector<long long> a(n);
    for (int i=0; i<n; i++) cin >> a[i];
    seg_tree<long long> stree(a);
}