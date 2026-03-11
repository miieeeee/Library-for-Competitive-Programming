#include <vector>
using namespace std;

template<typename T>
T determinant(vector<vector<T>> A){
    int n = A.size();
    if(n == 0) return 1;
    assert(A[0].size() == n);
    T ret = 1;
    for(int i=0; i<n; i++){
        int idx = -1;
        for(int j=i; j<n; j++){
            if(A[j][i] != 0){
                idx = j;
                break;
            }
        }
        if(idx == -1) return 0;
        if(idx != i){
            ret *= -1;
            swap(A[i], A[idx]);
        }
        ret *= A[i][i];
        T den = A[i][i];
        for(int j=i; j<n; j++) A[i][j] /= den;
        for(int j=i+1; j<n; j++){
            T mul = A[j][i];
            for(int k=i; k<n; k++){
                A[j][k] -= A[i][k]*mul;
            }
        }
    }
    return ret;
}

// from TKO919 submission
// https://judge.yosupo.jp/submission/76850
int determinant_mod(vector<vector<long long>> A,int mo){
    int n=A.size();
    long long ret=1;
    for(int i=0; i<n; i++){
        for(int j=i+1; j<n; j++){
            while(A[j][i]){
                ret=(mo-ret)%mo;
                int c=A[i][i]/A[j][i];
                for(int k=i; k<n; k++){
                    A[i][k]-=A[j][k]*c;
                    A[i][k]%=mo;
                    if(A[i][k]<0)A[i][k]+=mo;
                    swap(A[i][k],A[j][k]);
                }
            }
        }
        ret=(ret*A[i][i])%mo;
    }
    return ret%mo;
}