struct polygon {
    int n;
    vector<pt> pol;
    ptolygon(vector<pt> poly = {}) : pol(poly) {
        n = sz(pol);
    }

    bool inside(pt p, bool strict = true) { //check if point p is inside O(log(n))
        int a = 1, b = n - 1, r = !strict;
        if (n < 3) return r && onSegment(pol[0], pol.back(), p);
        if (sgn(pol[0].cross(pol[a], pol[b])) > 0) swap(a, b);
        if (sgn(pol[0].cross(pol[a], p)) >= r || sgn(pol[0].cross(pol[b], p)) <= -r)
            return false;
        while (abs(a - b) > 1) {
            int c = (a + b) / 2;
            (sgn(pol[0].cross(pol[c], p)) > 0 ? b : a) = c;
        }
        return sgn(pol[a].cross(pol[b], p)) < r;
    }
    pt polygonCenter(const vector<pt>& v) {
		pt res(0, 0); double A = 0;
		for (int i = 0, j = sz(v) - 1; i < sz(v); j = i++) {
			res = res + (v[i] + v[j]) * v[j].cross(v[i]);
			A += v[j].cross(v[i]);
		}
		return res / A / 3;
	}
};

// Returns a vector with the vertices of a polygon with everything to the left of the line going 
// from s to e cut away.
pair<int, pt> lineInter(pt s1, pt e1, pt s2, pt e2) {
	auto d = (e1 - s1).cross(e2 - s2);
	if (d == 0) // if parallel
		return {-(s1.cross(e1, s2) == 0), pt(0, 0)};
	auto p = s2.cross(e1, e2), q = s2.cross(e2, s1);
	return {1, (s1 * p + e1 * q) / d};
}
vector<pt> polygonCut(const vector<pt>& poly, pt s, pt e) {
	vector<pt> res;
	rep(i,0,sz(poly)) {
		pt cur = poly[i], prev = i ? poly[i-1] : poly.back();
		bool side = s.cross(e, cur) < 0;
		if (side != (s.cross(e, prev) < 0))
			res.push_back(lineInter(s, e, cur, prev).second);
		if (side)
			res.push_back(cur);
	}
	return res;
}

// area of the union of $n$ polygons (not necessarily convex)
// O(N^2), N = number of points
int sideOf(pt s, pt e, pt p) { return sgn(s.cross(e, p)); }
int sideOf(const pt& s, const pt& e, const pt& p, double eps) {
	auto a = (e-s).cross(p-s); double l = (e-s).dist()*eps;
	return (a > l) - (a < -l);
}
double rat(pt a, pt b) { return sgn(b.x) ? a.x/b.x : a.y/b.y; }
double polyUnion(vector<vector<pt>>& poly) {
	double ret = 0;
	rep(i,0,sz(poly)) rep(v,0,sz(poly[i])) {
		pt A = poly[i][v], B = poly[i][(v + 1) % sz(poly[i])];
		vector<pair<double, int>> segs = {{0, 0}, {1, 0}};
		rep(j,0,sz(poly)) if (i != j) {
			rep(u,0,sz(poly[j])) {
				pt C = poly[j][u], D = poly[j][(u + 1) % sz(poly[j])];
				int sc = sideOf(A, B, C), sd = sideOf(A, B, D);
				if (sc != sd) {
					double sa = C.cross(D, A), sb = C.cross(D, B);
					if (min(sc, sd) < 0)
						segs.emplace_back(sa / (sa - sb), sgn(sc - sd));
				} else if (!sc && !sd && j<i && sgn((B-A).dot(D-C))>0){
					segs.emplace_back(rat(C - A, B - A), 1);
					segs.emplace_back(rat(D - A, B - A), -1);
				}
			}
		}
		sort(all(segs));
		for (auto& s : segs) s.first = min(max(s.first, 0.0), 1.0);
		double sum = 0;
		int cnt = segs[0].second;
		rep(j,1,sz(segs)) {
			if (!cnt) sum += segs[j].first - segs[j - 1].first;
			cnt += segs[j].second;
		}
		ret += A.cross(B) * sum;
	}
	return ret / 2;
}