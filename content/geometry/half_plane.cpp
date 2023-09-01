#include "./point.cpp"
const double EPS = 1e-6;
const double PI = acos(-1);
const double INF = 1e9;

pt lineIntersectSeg(pt p, pt q, pt A, pt B) {
    double c = (A-B).cross(p-q);
    double a = A.cross(B);
    double b = p.cross(q);
    return ((p-q)*(a/c)) - ((A-B)*(b/c));
}

bool parallel(pt a, pt b) {
    return fabs(a.cross(b)) < EPS;
}

typedef vector<pt> polygon;
double signedArea(polygon &P) {
    double result = 0.0;
    int n = sz(P);
    for(int i=0;i<n;++i)
        result += P[i].cross(P[(i+1)%n]);    
    return result / 2.0;
}

typedef pair<pt, pt> halfplane;
pt dir(halfplane h) {
    return h.second - h.first;
}
bool belongs(halfplane h, pt a) {
    return dir(h).cross(a - h.first) > EPS;
}

bool hpcomp(halfplane ha, halfplane hb) {
    pt a = dir(ha), b = dir(hb);
    if (parallel(a, b) && a.dot(b) > EPS)
        return b.cross(ha.first - hb.first) < -EPS;
    if (b.y*a.y > EPS) return a.cross(b) > EPS;
    else if (fabs(b.y) < EPS && b.x > EPS) return false;
    else if (fabs(a.y) < EPS && a.x > EPS) return true;
    else return b.y < a.y;
}

polygon intersect(vector<halfplane> H, double W = INF) {
    H.pb(halfplane(pt(-W,-W), pt(W,-W)));//-1,-1 | 1,-1
    H.pb(halfplane(pt(W,-W), pt(W,W)));  // 1,-1 | 1, 1
    H.pb(halfplane(pt(W,W), pt(-W,W))); //  1, 1 |-1, 1
    H.pb(halfplane(pt(-W,W), pt(-W,-W)));//-1, 1 |-1,-1
    sort(all(H), hpcomp);
    int i = 0;
    while(parallel(dir(H[0]), dir(H[i]))) i++;
    deque<pt> P;
    deque<halfplane> S;
    S.pb(H[i-1]);
    for(;i<sz(H);++i) {
        while(!P.empty() && !belongs(H[i], P.back()))
            P.pop_back(), S.pop_back();
        pt df = dir(S.front()), di = dir(H[i]);
        if (P.empty() && df.cross(di) < EPS)
            return polygon();
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
    return polygon(all(P));
}

int main() {
    int n; cin>>n;
    vector<pt> polygon(n);
    for(auto &p : polygon)
        cin>>p.x>>p.y;    

    vector<halfplane> halfplanes;
    for(int i=0;i<n;++i) {
        halfplane currLine = {polygon[(i+1)%n], polygon[i]};
        halfplanes.pb(currLine);
    }

    auto poly = intersect(halfplanes);
    double ans = fabs(signedArea(poly));
    cout<<fixed<<setprecision(12);
    cout<<ans<<endl;
}
