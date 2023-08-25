struct pt {
    using T = double;

    T x, y;
    explicit pt(T x=0, T y=0) : x(x), y(y) {}
    bool operator < (pt p) const { return tie(x,y) < tie(p.x,p.y); }
    bool operator == (pt p) const { return tie(x,y)==tie(p.x,p.y); }
    pt operator + (pt p) const { return pt(x+p.x, y+p.y); }
    pt operator - (pt p) const { return pt(x-p.x, y-p.y); }
    pt operator * (T d) const { return pt(x*d, y*d); }
    pt operator / (T d) const { return pt(x/d, y/d); }
    T dot(pt p) const { return x*p.x + y*p.y; }
    T cross(pt p) const { return x*p.y - y*p.x; }
    T cross(pt &a, pt &b) const { return (a-*this).cross(b-*this); }
    T dist2() const { return x*x + y*y; }
    double dist() const { return sqrt((double)dist2()); }
    double angle() const { return atan2(y, x); }
    pt unit() const { return *this/dist(); } // makes dist()=1
    pt perp() const { return pt(-y, x); } // rotates +90 degrees
    pt normal() const { return perp().unit(); } 
    friend ostream& operator << (ostream &os, pt p) {
        return os << "(" << p.x << ", " << p.y << ")";}
    T ori(pt a, pt b) const { T f = cross(a, b); return (f < 0 ? -1 : (f > 0 ? 1 : 0)); }    
    pt r90cw(){ return pt(y, -x);} // rotate 90 degrees clock wise
    pt r90ccw(){ return pt(-y, x);} // rotate 90 degrees counter clock wise 
};
bool onSegment(pt &s, pt &e, pt &p) {
    return p.cross(s, e) == 0 && (s - p).dot(e - p) <= 0;
}
int sgn(ll x) { return (x > 0) - (x < 0); }

bool onSegment(pt &s, pt &e, pt &p) {
    return p.cross(s, e) == 0 && (s - p).dot(e - p) <= 0;
}
int sgn(ll x) { return (x > 0) - (x < 0); }

double areaPoly(vector<pt> &poly) {
    assert(3<=sz(poly));
    ll area=poly.back().cross(poly[0]);
    for(int i=0;i<sz(poly)-1;++i)
        area += poly[i].cross(poly[i+1]);
    return abs(area)/2.0;
}

using line=array<double,3>;
line bisector(pt o, pt a, pt b) { //bissetriz de AOB, p
    a = a - o, b = b - o;                 // (a*b)  k  (b*a)
    pt k = a * b.dist() + b * a.dist() + o; //   \    o   /   k/=k.dist()
    //reta Ax+By+C=0
    double A=k.y-o.y, B = o.x-k.x, C = -A*o.x - B*o.y;
    return {A,B,C};
}

//dist P to line(b,c), A=c.y-b.y, B=b.x - c.x, C = -A*b.x - B*b.y
//dist P to line(Ax+By+C=0) =|A.x + B.y + C| / (sqrt(A^2+B^2))
//dist p to segment(s,e)
double segDist(pt& s, pt& e, pt& p) {
    if (s==e) return (p-s).dist();
    auto d = (e-s).dist2(), t = min(d,max(.0,(p-s).dot(e-s)));
    return ((p-s)*d-(e-s)*t).dist()/d;
}

double segRay(pt& s, pt& e, pt& p) {
    if (s==e) return (p-s).dist();
    if((p-s).dot(e-s) <= 0.0) return (p-s).dist();
    return abs((p-s).cross(e-s)) / (e-s).dist();    
}

template<class T> vector<T> seg_int(T a, T b, T c, T d) {
    auto oa = c.cross(d, a), ob = c.cross(d, b),
         oc = a.cross(b, c), od = a.cross(b, d);
    if (sgn(oa) * sgn(ob) < 0 && sgn(oc) * sgn(od) < 0)
        return {(a * ob - b * oa) / (ob - oa)};
    set<T> s;
    if (on_segment(c, d, a)) s.insert(a);
    if (on_segment(c, d, b)) s.insert(b);
    if (on_segment(a, b, c)) s.insert(c);
    if (on_segment(a, b, d)) s.insert(d);
    return {s.begin(), s.end()};
}
