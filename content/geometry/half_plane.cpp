//N testado !!
#define INF 0x3f3f3f3f
double EPS = 1e-6;
typedef pair<pt, pt> HF;
pt dir(HF h) { return h.second - h.first; }
bool parallel(pt a, pt b) { return fabs(a.cross(b)) < EPS; }
bool belongs(HF h, pt a) { return dir(h).cross(a - h.first) > EPS; }
pt lineIntersectSeg(pt p, pt q, pt A, pt B) {
	double c = (A-B).cross(p-q);
	double a = A.cross(B);
	double b = p.cross(q);
	return ((p-q)*(a/c)) - ((A-B)*(b/c));
}

bool hpcomp(HF ha, HF hb) {
	pt a = dir(ha), b = dir(hb);
	if (parallel(a, b) && a.dot(b) > EPS)
		return b.cross(ha.first - hb.first) < -EPS;
	if (b.y*a.y > EPS) return a.cross(b) > EPS;
	else if (fabs(b.y) < EPS && b.x > EPS) return false;
	else if (fabs(a.y) < EPS && a.x > EPS) return true;
	else return b.y < a.y;
}

vector<pt> intersect(vector<HF> H, double W = INF) {
	H.pb(HF(pt(-W,-W), pt(W,-W)));
	H.pb(HF(pt(W,-W), pt(W,W)));
	H.pb(HF(pt(W,W), pt(-W,W)));
	H.pb(HF(pt(-W,W), pt(-W,-W)));
	sort(H.begin(), H.end(), hpcomp);
	int i = 0;
	while(parallel(dir(H[0]), dir(H[i]))) i++;

	deque<pt> P;
	deque<HF> S;
	S.pb(H[i-1]);
	for(; i < sz(H); i++) {
		while(!P.empty() && !belongs(H[i], P.back()))
			P.pop_back(), S.pop_back();
		pt df = dir(S.front()), di = dir(H[i]);
		if (P.empty() && df.cross(di) < EPS)
			return {};
		P.pb(lineIntersectSeg(H[i].first, H[i].second,
			S.back().first, S.back().second));
		S.pb(H[i]);
	}
	while(!belongs(S.back(), P.front()) ||
		!belongs(S.front(), P.back())) {
		while(!belongs(S.back(), P.front()))
			P.pop_front(), S.pop_front();
		while(!belongs(S.front(), P.back()))
			P.pop_back(), S.pop_back();
	}
	P.pb(lineIntersectSeg(S.front().first,
		S.front().second, S.back().first, S.back().second));
	return vector<pt>(P.begin(), P.end());
}