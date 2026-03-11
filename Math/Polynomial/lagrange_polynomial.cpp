#include<bits/stdc++.h>
#include<atcoder/modint>
using namespace std;
using mint = atcoder::modint1000000007;
template<typename T>
struct lagrange_polynomial{
    int D;
    vector<T> xs, ys;
    vector<T> fact, ifact;
    lagrange_polynomial(vector<T> xs, vector<T> ys):xs(xs), ys(ys), D(xs.size()-1), fact(xs.size(), 1), ifact(xs.size()){
        for(int i=1; i<=D; i++){
            fact[i] = fact[i-1]*i;
        }
        for(int i=0; i<=D; i++){
            ifact[i] = fact[i].inv();
        }
    }
    T get(T N){
        T ret = 0;
        for(int i=0; i<=D; i++){
            T add = ys[i];
            for(int j=0; j<=D; j++){
                if(i == j) continue;
                add *= N-xs[j];
                add *= (xs[i] - xs[j]).inv();
            }
            ret += add;
        }
        return ret;
    }
    T get2(T N){
        if(D == 0) return ys[0];
        T ret = 0;
        T diff = xs[1] - xs[0];
        T mul = 1;
        for(int i=0; i<=D; i++){
            if(N == xs[i]){
                return ys[i];
            }
            mul *= N-xs[i];
        }
        for(int i=0; i<=D; i++){
            T num = mul/(N-xs[i]);
            T den = T(-1).pow(D-i)*fact[i]*fact[D-i]*diff.pow(D);
            ret += ys[i]*num/den;
        }
        return ret;
    }
};

int main(){
    int n;
    cin >> n;
    vector<mint> xs(n+1);
    vector<mint> ys(n+1);
    for(int i=0; i<=n; i++){
        int a;
        cin >> a;
        ys[i] = a;
        xs[i] = i;
    }
    int t;
    cin >> t;
    lagrange_polynomial<mint> lp(xs, ys);
    cout << lp.get2(t).val() << endl;
}