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