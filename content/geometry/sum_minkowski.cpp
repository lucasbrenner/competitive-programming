vector<pt> minkowski(vector<pt> &P, vector<pt> &Q) {
    auto reorder = [](vector<pt> &P) {
        size_t pos = 0;
        for(size_t i = 1; i < P.size(); i++){
            if(P[i].y < P[pos].y || (P[i].y == P[pos].y && P[i].x < P[pos].x))
                pos = i;
        }
        rotate(P.begin(), P.begin() + pos, P.end());
        P.pb(P[0]);
        P.pb(P[1]);
    };

    reorder(P);
    reorder(Q);
    vector<pt> result;
    size_t i = 0, j = 0;
    while(i < P.size() - 2 || j < Q.size() - 2){
        result.push_back(P[i] + Q[j]);
        auto cross = (P[i + 1] - P[i]).cross(Q[j + 1] - Q[j]);
        if(cross >= 0)
            ++i;
        if(cross <= 0)
            ++j;
    }
    return result;
}