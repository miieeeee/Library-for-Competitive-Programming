#pragma once

#include <vector>
#include <chrono>

/// @brief HashMap. リサイズx.  cf. https://judge.yosupo.jp/submission/186759
/// @tparam T 
template<typename T>
struct HashMap{
    std::vector<bool> used;
    std::vector<unsigned long long> key;
    std::vector<T> value;
    unsigned int mask;
    HashMap(int n){
        int s = 1;
        while(s < n*2) s *= 2;
        used.resize(s);
        key.resize(s);
        value.resize(s);
        mask=s-1;
    }

    T &operator[](const unsigned long long k){
        int h = index(k);
        if(!used[h]){
            used[h] = 1;
            key[h] = k;
            value[h] = T{};
        }
        return value[h];
    }

    T get(const unsigned long long k, T default_value){
        int h = index(k);
        if(used[h]) return value[h];
        return default_value;
    }
    private:
    int hash(unsigned long long x){
        static const unsigned long long FIXED_RANDOM = std::chrono::steady_clock::now().time_since_epoch().count();
        x += FIXED_RANDOM;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return (x ^ (x >> 31)) & mask;
    }

    int index(const unsigned long long &k) {
        int i = 0;
        for (i = hash(k); used[i] && key[i] != k; i = (i + 1) & mask) {}
        return i;
    }
};