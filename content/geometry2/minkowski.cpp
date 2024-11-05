#include "point.cpp"

typedef Point<long long> P;

void reorder_polygon(vector<P> & pts){
    int pos = 0;
    for(int i = 1; i < pts.size(); i++){
        if(pts[i].y < pts[pos].y || (pts[i].y == pts[pos].y && pts[i].x < pts[pos].x))
            pos = i;
    }
    rotate(pts.begin(), pts.begin() + pos, pts.end());
}

vector<P> minkowski(vector<P> A, vector<P> B){
    // the first vertex must be the lowest
    reorder_polygon(A);
    reorder_polygon(B);
    // we must ensure cyclic indexing
    A.push_back(A[0]);
    A.push_back(A[1]);
    B.push_back(B[0]);
    B.push_back(B[1]);
    // main part
    vector<P> result;
    int i = 0, j = 0;
    while(i < A.size() - 2 || j < B.size() - 2){
        result.push_back(A[i] + B[j]);
        auto cross = (A[i + 1] - A[i]).cross(B[j + 1] - B[j]);
        if(cross >= 0 && i < A.size() - 2)
            ++i;
        if(cross <= 0 && j < B.size() - 2)
            ++j;
    }
    return result;
}