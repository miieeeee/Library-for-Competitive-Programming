#include "LowLink.hpp"

struct BiConnectedComponents: LowLink{
    using LL = LowLink;

    vector<int> used;
    vector<vector<pair<int, int>>> bc;
    vector<pair<int, int>> tmp;
    vector<vector<int>> bcv;

    BiConnectedComponents(vector<vector<int>> &g, bool need_bcv=false): LL(g){
        build(); 
        if(need_bcv){
            build_bcv();
        }
    }

    void build(){
        used.assign(this->G.size(), 0);
        for(int i=0; i<(int)used.size(); i++){
            if (!used[i]) dfs(i, -1);
        }
    }

    void build_bcv(){
        vector<bool> flag(this->G.size());
        for(auto group : bc){
            vector<int> vs;
            for(auto p : group){
                vs.push_back(p.first);
                vs.push_back(p.second);
                flag[p.first] = true;
                flag[p.second] = true;
            }
            sort(vs.begin(), vs.end());
            vs.erase(unique(vs.begin(), vs.end()), vs.end());
            bcv.push_back(vs);
        }
        for(int i=0; i<(int)this->G.size(); i++){
            if(!flag[i]) bcv.push_back({i}); 
        }
    }

    

    void dfs(int idx, int par) {
        used[idx] = true;
        for (auto &to : this->G[idx]){
            if (to == par) continue;
            if (!used[to] || this->order[to] < this->order[idx]){
                tmp.emplace_back(minmax<int>(idx, to));
            }
            if (!used[to]) {
                dfs(to, idx);
                if (this->low[to] >= this->order[idx]){
                    bc.emplace_back();
                    while(true){
                        auto e = tmp.back();
                        bc.back().emplace_back(e);
                        tmp.pop_back();
                        if (e.first == min<int>(idx, to) && e.second == max<int>(idx, to)){
                            break;
                        }
                    }
                }
            }
        }
    }
};