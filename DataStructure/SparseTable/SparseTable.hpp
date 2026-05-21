#pragma once


/// @brief staticな列に対してO(nlogn)で構築O(1)で範囲取得ができる（結合則が必要）
/// @tparam T 
/// @tparam op 
template<class T, T (*op)(T, T)>
struct SparseTable{
    int n;
    int LOG;
    vector<vector<T>> data;
    vector<int> log_table;
    SparseTable() {}
    SparseTable(int n): n(n){
        LOG = 30;
        while((n>>LOG&1) == 0) LOG--;
        data.resize(n, vector<T>(LOG+1));
    }
    SparseTable(vector<T> data): n(data.size()), data(data){
        build();
    }
    void set(int i, T x){
        data[i][0] = x;
    }
    void build(){
        for(int i=0; i<LOG; i++){
            for(int j=0; j<n; j++){
                if(j + (1<<i) >= n) break;
                data[j][i+1] = op(data[j][i], data[j+(1<<i)][i]);
            }
        }
        build_log_table(n);        
    }

    T prod(int l, int r){
        return op(data[l][log_table[r-l]], data[r-(1<<log_table[r-l])][log_table[r-l]]);
    }

    private:
    void build_log_table(int n){
        log_table.resize(n+1, -1);
        for(int i=1; i<=n; i++){
            log_table[i] = log_table[i>>1]+1; 
        } 
    }
};