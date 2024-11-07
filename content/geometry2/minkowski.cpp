#include "point.cpp"

typedef Point<long long> P;

void reorder_polygon(vector<P> &pts){
    int pos = 0;
    for(int i = 1; i < pts.size(); i++){
        if(pts[i].y < pts[pos].y || (pts[i].y == pts[pos].y && pts[i].x < pts[pos].x))
            pos = i;
    }
    rotate(pts.begin(), pts.begin() + pos, pts.end());
}

vector<P> minkowski(vector<P> a, vector<P> b){
    reorder_polygon(a);
    reorder_polygon(b);
    a.push_back(a[0]);
    a.push_back(a[1]);
    b.push_back(b[0]);
    b.push_back(b[1]);
    vector<P> result;
    int i = 0, j = 0;
    while(i < a.size() - 2 || j < b.size() - 2){
        result.push_back(a[i] + b[j]);
        auto cross = (a[i + 1] - a[i]).cross(b[j + 1] - b[j]);
        if(cross >= 0 && i < a.size() - 2)
            ++i;
        if(cross <= 0 && j < b.size() - 2)
            ++j;
    }
    return result;
}

