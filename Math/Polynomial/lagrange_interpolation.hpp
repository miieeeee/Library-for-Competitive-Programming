#pragma once
#include <vector>

template<typename T>
struct lagrange_interpolation{
    int D;
    std::vector<T> xs, ys;
    std::vector<T> fact, ifact;
    lagrange_interpolation(std::vector<T> xs, std::vector<T> ys):xs(xs), ys(ys), D(xs.size()-1), fact(xs.size(), 1), ifact(xs.size()){
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

    std::vector<T> interpolate() {
        int D = (int) xs.size() - 1;

        std::vector<T> f(D + 1), dp(D + 2);
        dp[0] = 1;
        for(int j = 0; j <= D; j++) {
            for(int l = D + 1; l > 0; l--) {
            dp[l] = dp[l] * -xs[j] + dp[l - 1];
            }
            dp[0] *= -xs[j];
        }

        for(int i = 0; i <= D; i++) {
            T d = 1;
            for(int j = 0; j <= D; j++) {
            if(i != j) {
                d *= xs[i] - xs[j];
            }
            }
            T mul = ys[i] / d;
            if(xs[i] == 0) {
            for(int j = 0; j <= D; j++) {
                f[j] += dp[j + 1] * mul;
            }
            } else {
            T inv = T(1) / (-xs[i]), pre = 0;
            for(int j = 0; j <= D; j++) {
                T cur = (dp[j] - pre) * inv;
                f[j] += cur * mul;
                pre = cur;
            }
            }
        }
        return f;
    }
};