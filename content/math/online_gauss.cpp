template<int N>
struct online_gauss {
    bitset<N> gauss[N];

    void add(bitset<N> x){
        for(int b = N - 1; b >= 0; b--){
            if(!gauss[b][b] && x[b]){
                gauss[b] = x;
                break;
            }else if(x[b]) x ^= gauss[b];
        }
    }

    //if MIN = 0, max xor starting with x
    //if MIN = 1, min xor starting with x
    bitset<N> query(bitset<N> x, bool MIN=0){
        for(int b = N - 1; b >= 0; b--)
            if(x[b] == MIN) x ^= gauss[b];
        return x;
    }
};
