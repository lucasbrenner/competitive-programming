struct treap {
    struct node {
        ll val, ma1, ma2, cnt, sum, lazy;
        int rnk, siz, l, r;
        node(ll &_val) {
            val = sum = ma1 = _val;
            ma2 = -1;
            siz = 1;
            cnt = 1;
            rnk = rng();
            l = r = -1;
            lazy = 0;
        }

        void chmin(ll x) {
            if(ma1 <= x) return;
            sum -= (ma1 - x) * cnt;
            ma1 = x;
            val = min(val, x);
        }

        void soma(ll x) {
            if(ma2 != -1) ma2 += x;
            ma1 += x;
            sum += siz * x;
            lazy += x;
            val += x;
        }
    };

    vector<node> cur;    
    inline int g_siz(int x) {
        return (x == -1 ? 0 : cur[x].siz);
    }

    void prop(int x) {
        if(cur[x].l != -1) {
            cur[cur[x].l].soma(cur[x].lazy);
            cur[cur[x].l].chmin(cur[x].ma1);
        }
        if(cur[x].r != -1){
            cur[cur[x].r].soma(cur[x].lazy);
            cur[cur[x].r].chmin(cur[x].ma1);
        }
        cur[x].lazy = 0;
    }
 
    void calc(int x) {
        cur[x].siz = 1;
        cur[x].sum = cur[x].ma1 = cur[x].val;
        cur[x].ma2 = -1;
        cur[x].cnt = 1;
        if(cur[x].l != -1) {
            int l = cur[x].l;
            cur[x].siz += cur[l].siz;
            cur[x].sum += cur[l].sum;

            if(cur[l].ma1 == cur[x].ma1) {
                cur[x].cnt += cur[l].cnt;                
            }else if(cur[l].ma1 > cur[x].ma1) {
                cur[x].cnt = cur[l].cnt;
                swap(cur[x].ma1, cur[x].ma2);
                cur[x].ma1 = cur[l].ma1;
            }else if(cur[l].ma1 > cur[x].ma2) {
                cur[x].ma2 = cur[l].ma1;
            }
            if(cur[l].ma2 > cur[x].ma2) cur[x].ma2 = cur[l].ma2;
        }

        if(cur[x].r != -1) {
            int r = cur[x].r;
            cur[x].siz += cur[r].siz;
            cur[x].sum += cur[r].sum;

            if(cur[r].ma1 == cur[x].ma1) {
                cur[x].cnt += cur[r].cnt;                
            }else if(cur[r].ma1 > cur[x].ma1) {
                cur[x].cnt = cur[r].cnt;
                swap(cur[x].ma1, cur[x].ma2);
                cur[x].ma1 = cur[r].ma1;
            }else if(cur[r].ma1 > cur[x].ma2) {
                cur[x].ma2 = cur[r].ma1;
            }
            if(cur[r].ma2 > cur[x].ma2) cur[x].ma2 = cur[r].ma2;
        }
    }
 
    int root = -1;
    void push(ll x) {
        cur.push_back(node(x));
        root = merge(root, sz(cur) - 1);
    }
 
    int merge(int a, int b) {
        if(b == -1) return a;
        if(a == -1) return b;
        prop(a), prop(b);
        if(cur[a].rnk > cur[b].rnk) {
            cur[a].r = merge(cur[a].r, b);
            calc(a);
            return a;
        } else {
            cur[b].l = merge(a, cur[b].l);
            calc(b);
            return b;
        }
    } 
 
    void split(int a, int cnt, int &l, int &r) {
        if(a == -1) {
            l = -1, r = -1;
            return;
        }
        prop(a);
        if(g_siz(cur[a].l) >= cnt) {
            split(cur[a].l, cnt, l, r);
            cur[a].l = r;
            calc(a);
            r = a;
        } else {
            split(cur[a].r, cnt - g_siz(cur[a].l) - 1, l, r);
            cur[a].r = l;
            calc(a);
            l = a;
        }
    }
 
    void swap_ranges(int l1, int r1, int l2, int r2) {
        int p1, p2, p3, p4, p5;
        split(root, l1, p1, p2);
        split(p2, r1 - l1 + 1, p2, p3);
        split(p3, l2 - r1 - 1, p3, p4);
        split(p4, r2 - l2 + 1, p4, p5);
 
        int r = merge(p1, p4);
        r = merge(r, p3);
        r = merge(r, p2);
        r = merge(r, p5);        
    }
 
    void dale(int a, ll x) {
        if(a == -1) return;
        prop(a);
        if(cur[a].ma2 >= x) {
            dale(cur[a].l, x);
            dale(cur[a].r, x);
            if(cur[a].val > x) cur[a].val = x;
            calc(a);
        }else if(cur[a].ma1 > x) {
            cur[a].chmin(x);
        }
    }

    void chmin(int l, int r, ll h) {
        int p1, p2, p3;
        split(root, l, p1, p2);
        split(p2, r - l + 1, p2, p3);
        dale(p2, h);
        merge(merge(p1, p2), p3);
    }

    void sum(int l, int r, ll h) {
        int p1, p2, p3;
        split(root, l, p1, p2);
        split(p2, r - l + 1, p2, p3);
        cur[p2].soma(h);
        prop(p2);
        calc(p2);
        merge(merge(p1,p2), p3);
    }

    void print(int x) {
        if(x == -1) return;
        print(cur[x].l);
        cout << cur[x].val << " ";
        print(cur[x].r);
    };

    inline void print() {print(root);}
};
