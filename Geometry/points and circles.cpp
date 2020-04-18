#include<bits/stdc++.h>
using namespace std;

struct point{
    long double x,y;
    point(long double x=0, long double y=0) : x(x), y(y){}
    point operator - () const{ return point(-x, -y);}
    point& operator += (const point& o){ x += o.x; y += o.y; return *this;}
    point operator + (const point& o) const{ return point(x, y) += o;}
    point& operator -= (const point& o){ x -= o.x; y -= o.y; return *this;}
    point operator - (const point& o) const{ return point(x, y) -= o;}
    point& operator /= (const long double k){ x /= k; y /= k; return *this;}
    point operator / (const long double k){ return point(x, y) /= k;}
    point r90cw(){ return point(y, -x);} // rotate 90 degrees clock wise
    point r90ccw(){ return point(-y, x);} // rotate 90 degrees counter clock wise
    long double dist(point o){ return sqrt((o.x - x)*(o.x - x) + (o.y - y)*(o.y - y));}
};
point operator * (const long double k, const point& p){ return point(p.x*k, p.y*k);}
point operator * (const point& p, const long double k){ return point(p.x*k, p.y*k);}

struct circle{
    point center; long double r;
    circle (point c = point(0, 0), long double rr = 0) : center(c), r(rr) {}
    bool intersect(circle o){
        return center.dist(o.center) <= r + o.r && center.dist(o.center) >= fabs(r - o.r);
    }
    vector<point> intersection(circle o){
        vector<point> ans;
        long double d = center.dist(o.center), R = o.r, x, y;
        if (d > r + R || d < fabs(r - R)) return ans;
        x = (d*d - R*R + r*r)/(2*d*r);
        y = r*sqrt(1 - x*x);
        point middle = center + (o.center - center)*( (r*x) / d);
        point vdif = (o.center - center).r90cw()*(y / d);
        ans.push_back(middle + vdif); ans.push_back(middle - vdif);
        return ans;
    }
};
