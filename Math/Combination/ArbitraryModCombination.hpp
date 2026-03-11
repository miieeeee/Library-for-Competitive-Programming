#pragma once
#include <vector>
#include <utility>
#include "Math/CRT/crt.hpp"
#include "Math/Modint/inv_mod.hpp"

struct Combination {
    std::vector<std::vector<std::pair<long long, int>>> fact, ifact;
    std::vector<std::pair<long long, int>> ps;
    std::vector<long long> ms;
    std::vector<std::vector<long long>> power;
    long long MOD;
    Combination(int sz, long long mod): fact(sz+1), ifact(sz+1), MOD(mod) {
        {
            long long x = MOD;
            for(long long i=2; i*i<=x; i++) {
                int cnt = 0;
                while(x%i == 0) {
                    x /= i;
                    cnt++;
                }
                ps.push_back({i, cnt});
            }
            if(x != 1) ps.push_back({x, 1});
        }

        for(int i=0; i<ps.size(); i++) {
            long long x = 1;
            power.push_back({1});
            for(int j=0; j<ps[i].second; j++) {
                x = x*ps[i].first%MOD;
                power[i].push_back(x);
            }
        }

        for(int i=0; i<ps.size(); i++) {
            for(int j=0; j<sz; j++) {
                int x = j+1;
                fact[i][j+1].second = 0;
                while(x%ps[i].first == 0) {
                    x /= ps[i].first;
                    fact[i][j+1].second++;
                }
                fact[i][j+1].first = x;
                ifact[i][j+1].first = inv_mod(x, power[i][ps[i].second]);
                ifact[i][j+1].second = -fact[i][j+1].second;
            }
        }
    }

    long long C(int n, int r) const {
        if(n < 0 || n < r) return 0;
        std::vector<long long> rs(ps.size());
        for(int i=0; i<ps.size(); i++) {
            std::pair<long long, int> xy;
            xy.first = fact[i][n].first*ifact[i][n-r].first%MOD*ifact[i][r].first%MOD;
            xy.second = fact[i][n].second+ifact[i][n-r].second+ifact[i][r].second;
            if(xy.second >= ps[i].second) {
                rs[i] = 0;
            }
            else {
                rs[i] = xy.first*power[i][xy.second]%MOD;
            }
        }

        return crt(rs, ms).first;
    }
};