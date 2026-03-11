#include <vector>
using namespace std;
#include "../../DataStructure/BitSet/BitSet.hpp"

template<typename T>
vector<vector<T>> gaussian_elimination(vector<vector<T>> A, int lim=-1){
    int n = A.size();
    if(n == 0) return vector<vector<T>>(0);
    int m = A[0].size();
    if(lim == -1) lim = m;
    else lim = min(lim, m);
    int now = 0;
    for(int i=0; i<lim; i++){
        int idx = -1;
        for(int j=now; j<n; j++){
            if(A[j][i] != 0){
                idx = j;
                break;
            }
        }
        if(idx == -1) continue;
        if(idx != now){
            swap(A[idx], A[now]);
        }
        T den = A[now][i];
        for(int j=i; j<m; j++) A[now][j] /= den;
        for(int j=0; j<n; j++) if(j != now){
            T mul = A[j][i]/A[now][i];
            for(int k=i; k<m; k++){
                A[j][k] -= A[now][k]*mul;
            }
        }
        now++;
    }
    return A;
}

template<typename T>
vector<vector<T>> gaussian_elimination(vector<vector<T>> A, int &rank){
    int n = A.size();
    if(n == 0){
      rank = 0;
      return vector<vector<T>>(0);
    }
    int m = A[0].size();
    int now = 0;
    for(int i=0; i<m; i++){
        int idx = -1;
        for(int j=now; j<n; j++){
            if(A[j][i] != 0){
                idx = j;
                break;
            }
        }
        if(idx == -1) continue;
        if(idx != now){
            swap(A[idx], A[now]);
        }
        T den = A[now][i];
        for(int j=i; j<m; j++) A[now][j] /= den;
        for(int j=0; j<n; j++) if(j != now){
            T mul = A[j][i]/A[now][i];
            for(int k=i; k<m; k++){
                A[j][k] -= A[now][k]*mul;
            }
        }
        now++;
    }
    rank = now;
    return A;
}

vector<BitSet> gaussian_elimination(vector<BitSet> A){
    int n = A.size();
    if(n == 0) return vector<BitSet>(0);
    int m = A[0].size();
    int now = 0;
    for(int i=0; i<m; i++){
        int idx = -1;
        for(int j=now; j<n; j++){
            if(A[j].test(i)){
                idx = j;
                break;
            }
        }
        if(idx == -1) continue;
        if(idx != now){
            swap(A[idx], A[now]);
        }
        for(int j=0; j<n; j++) if(j != now){
            if(A[j].test(i)) A[j] ^= A[now];
        }
        now++;
    }
    return A;
}

vector<BitSet> gaussian_elimination(vector<BitSet> A, int &rank){
    int n = A.size();
    if(n == 0){
        rank = 0;
        return vector<BitSet>(0);
    }
    int m = A[0].size();
    int now = 0;
    for(int i=0; i<m; i++){
        int idx = -1;
        for(int j=now; j<n; j++){
            if(A[j].test(i)){
                idx = j;
                break;
            }
        }
        if(idx == -1) continue;
        if(idx != now){
            swap(A[idx], A[now]);
        }
        for(int j=0; j<n; j++) if(j != now){
            if(A[j].test(i)) A[j] ^= A[now];
        }
        now++;
    }
    rank = now;
    return A;
}