#include "../contest/template.cpp"

struct F {
    ll a;
    ll b;
 
    F() = default;
    F(ll v) : b{v} {}
    F(ll a, ll b) : a{a}, b{b} {}
 
    ll operator()(ll x) {
        return (a * x + b);
    }

    //F(g(x))
    const F operator() (F g){
        F ans;
        ans.a = a * g.a;
        ans.b = (b + a * g.b);
        return ans;
    }

    //F(x) + g(x)
    const F operator+ (F g){
        F ans;
        ans.a = (a + g.a);
        ans.b = (b + g.b);

        return ans;
    }
};