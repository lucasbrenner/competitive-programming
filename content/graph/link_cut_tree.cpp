#include "../contest/template.cpp"

struct SplayTree {
	struct Node {
		int p = 0, ch[2] = {0, 0};
		ll self = 0, path = 0;	// Path aggregates
		ll sub = 0, vir = 0;	// Subtree aggregates
		bool flip = 0;			// Lazy tags
	};
	vector<Node> t;
	SplayTree(int n) : t(n + 1) {}
	
	void push(int v) {
		if(!v || !t[v].flip) return;
		auto &[l, r] = t[v].ch;
		t[l].flip ^= 1, t[r].flip ^= 1;
		swap(l, r), t[v].flip = 0;
	}

	void pull(int v) {
		auto [l, r] = t[v].ch; push(l), push(r);
		t[v].path = t[l].path + t[v].self + t[r].path;
		t[v].sub = t[v].vir + t[l].sub + t[v].self + t[r].sub;
	}

	void set(int u, int d, int v) {
		t[u].ch[d] = v, t[v].p = u, pull(u);
	}

	void splay(int v) {
		auto dir = [&](int x) {
			int u = t[x].p;
			return t[u].ch[0] == x ? 0 : t[u].ch[1] == x ? 1 : -1;
		};
		auto rotate = [&](int x) {
			int y = t[x].p, z = t[y].p, dx = dir(x), dy = dir(y);
			set(y, dx, t[x].ch[!dx]), set(x, !dx, y);
			if(~dy) set(z, dy, x);
			t[x].p = z;
		};
		for(push(v); ~dir(v); ) {
			int y = t[v].p, z = t[y].p;
			push(z), push(y), push(v);
			int dv = dir(v), dy = dir(y);
			if(~dy) rotate(dv == dy ? y : v);
			rotate(v);
		}
	}
};

struct LinkCut : SplayTree {	// One-indexed
	LinkCut(int n) : SplayTree(n) {}

	int access(int v) {
		int u = v, x = 0;
		for(; u; x = u, u = t[u].p) {
			splay(u);
			int &ox = t[u].ch[1];
			t[u].vir += t[ox].sub;
			t[u].vir -= t[x].sub;
			ox = x, pull(u);
		}
		return splay(v), x;
	}

	void reroot(int v) {
		access(v), t[v].flip ^= 1, push(v);
	}

	void link(int u, int v) {
		reroot(u), access(v);
		t[v].vir += t[u].sub;
		t[u].p = v, pull(v);
	}

	void cut(int u, int v) {
		reroot(u), access(v);
		t[v].ch[0] = t[u].p = 0, pull(v);
	}

	// Rooted tree LCA. Returns 0 if u and v are not connected.
	int lca(int u, int v) {
		if(u == v) return u;
		access(u); int ret = access(v);
		return t[u].p ? ret : 0;
	}

	// Query subtree of u where v is outside the subtree.
	ll getSub(int u, int v) {
		reroot(v), access(u);
		return t[u].vir + t[u].self;
	}

	ll getPath(int u, int v) {
		reroot(u), access(v);
		return t[v].path;
	}

	// Add val in vertex u
	void update(int u, ll val) {
		access(u), t[u].self += val, pull(u);
	}

	// Finds the root of the tree containing node v
    int find_root(int v) {
    	access(v);
    	for (; t[v].ch[0]; v = t[v].ch[0]);
    	access(v);
    	return v;
    }
};
