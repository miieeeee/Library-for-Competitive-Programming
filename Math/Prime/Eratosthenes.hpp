#include <vector>

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