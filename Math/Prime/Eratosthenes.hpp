#include <vector>
#include <algorithm>

std::vector<bool> eratosthenes(int n){
    if (n == 0) return {};
    if (n == 1) return {false};
    std::vector<bool> is_prime(n, true);
    is_prime[0] = is_prime[1] = false;
    for(int p=2; p<n; p++){
        if(!is_prime[p]) continue;
        for(int i=p*2; i<n; i+=p) is_prime[i] = false;
    }
    return is_prime;
}

struct Eratostheness {
    std::vector<bool> is_prime;
    std::vector<int> factor;

    Eratostheness(int n) : is_prime(n, true), factor(n, -1) {
        is_prime[0] = is_prime[1] = false;  
        factor[1] = 1;
        for(int p=2; p<n; p++){
            if(!is_prime[p]) continue;
            factor[p] = p;
            for(int i=p*2; i<n; i+=p) {
                is_prime[i] = false;
                if(factor[i] == -1) factor[i] = p;
            }
        }
    }

    std::vector<std::pair<int, int>> prime_factor(int n) {
        std::vector<std::pair<int, int>> ret;
        while(n > 1) {
            int p = factor[n];
            int c = 0;
            while(factor[n] == p) {
                n /= p;
                c++;
            }

            ret.emplace_back(p, c);
        }
        return ret;
    }

    std::vector<int> divisor_enum(int n) {
        std::vector<int> ret(1, 1);
        auto pf = prime_factor(n);
        for(auto [p, c] : pf) {
            int sz = ret.size();
            for(int i=0; i<sz; i++) {
                int v = 1;
                for(int j=0; j<c; j++) {
                    v *= p;
                    ret.push_back(ret[i]*v);
                }
            }
        }

        std::sort(ret.begin(), ret.end());
        return ret;
    }
};