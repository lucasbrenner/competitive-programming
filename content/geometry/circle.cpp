#include "./point.cpp"

struct circle{
    pt center; long double r;
    circle (pt c = pt(0, 0), long double rr = 0) : center(c), r(rr) {}
    bool intersect(circle o){
        pt v = center - o.center;
        return v.dist() <= r + o.r && v.dist() >= fabs(r - o.r);
    }
    vector<pt> intersection(circle o){
        vector<pt> ans;
        long double d = (center-o.center).dist(), R = o.r, x, y;
        if (d > r + R || d < fabs(r - R)) return ans;
        x = (d*d - R*R + r*r)/(2*d*r);
        y = r*sqrt(1 - x*x);
        pt middle = center + (o.center - center)*( (r*x) / d);
        pt vdif = (o.center - center).r90cw()*(y / d);
        ans.push_back(middle + vdif); ans.push_back(middle - vdif);
        return ans;
    }
};

//radius of the circle going through points A, B and C
double ccRadius(const pt& A, const pt& B, const pt& C) {
    return (B-A).dist()*(C-B).dist()*(A-C).dist()/
            abs((B-A).cross(C-A))/2;
}

pt ccCenter(const pt& A, const pt& B, const pt& C) {
    pt b = C-A, c = B-A;
    return A + (b*c.dist2()-c*b.dist2()).perp()/b.cross(c)/2;
}

/*Returns the area of the intersection of a circle with a ccw polygon.
 O(n)*/
#define arg(p, q) atan2(p.cross(q), p.dot(q))
double circleptoly(pt c, double r, vector<pt> ps) {
    auto tri = [&](pt p, pt q) {
        auto r2 = r * r / 2;
        pt d = q - p;
        auto a = d.dot(p)/d.dist2(), b = (p.dist2()-r*r)/d.dist2();
        auto det = a * a - b;
        if (det <= 0) return arg(p, q) * r2;
        auto s = max((ld).0, -a-sqrt(det)), t = min((ld)1., -a+sqrt(det));
        if (t < 0 || 1 <= s) return arg(p, q) * r2;
        pt u = p + d * s, v = p + d * t;
        return arg(p,u) * r2 + u.cross(v)/2 + arg(v,q) * r2;
    };
    auto sum = 0.0;
    rep(i,0,sz(ps))
        sum += tri(ps[i] - c, ps[(i + 1) % sz(ps)] - c);
    return sum;
}

/* Finds the external tangents of two circles, or internal if r2 is negated.
Can return 0, 1, or 2 tangents -- 0 if one circle contains the other (or overlaps it, in the internal case, or if the circles are the same);
1 if the circles are tangent to each other (in which case .first = .second and the tangent line 
is perpendicular to the line between the centers).
.first and .second give the tangency points at circle 1 and 2 respectively.
To find the tangents of a circle with a point set r2 to 0. */
vector<pair<pt, pt>> tangents(pt c1, double r1, pt c2, double r2) {
    pt d = c2 - c1;
    double dr = r1 - r2, d2 = d.dist2(), h2 = d2 - dr * dr;
    if (d2 == 0 || h2 < 0)  return {};
    vector<pair<pt, pt>> out;
    for (double sign : {-1, 1}) {
        pt v = (d * dr + d.perp() * sqrt(h2) * sign) / d2;
        out.push_back({c1 + v * r1, c2 + v * r2});
    }
    if (h2 == 0) out.pop_back();
    return out;
}

// Computes the minimum circle that encloses a set of points. O(N)
pair<pt, double> mec(vector<pt> ps) {
    shuffle(all(ps), mt19937(time(0)));
    pt o = ps[0];
    double r = 0, EPS = 1 + 1e-8;
    rep(i,0,sz(ps)) if ((o - ps[i]).dist() > r * EPS) {
        o = ps[i], r = 0;
        rep(j,0,i) if ((o - ps[j]).dist() > r * EPS) {
            o = (ps[i] + ps[j]) / 2;
            r = (o - ps[i]).dist();
            rep(k,0,j) if ((o - ps[k]).dist() > r * EPS) {
                o = ccCenter(ps[i], ps[j], ps[k]);
                r = (o - ps[i]).dist();
            }
        }
    }
    return {o, r};
}