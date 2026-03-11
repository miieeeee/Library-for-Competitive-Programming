#include <vector>
#include <bitset>
#include "../../DataStructure/BitSet/BitSet.hpp"
using namespace std;

template<typename T>
vector<vector<T>> matrix_product(vector<vector<T>> &A, vector<vector<T>> &B){
    int nA = A.size(); int nB = B.size();
    assert(nA > 0 && nB > 0);
    int mA = A[0].size(); int mB = B[0].size();
    assert(mA == nB);
    vector<vector<T>> ret(nA, vector<T>(mB));
    for(int i=0; i<nA; i++){
        for(int j=0; j<mB; j++){
            for(int k=0; k<mA; k++){
                ret[i][j] += A[i][k]*B[k][j];
            }
        }
    }
    return ret;
}

vector<BitSet> matrix_product(vector<BitSet> &A, vector<BitSet> &B){
    int nA = A.size(); int nB = B.size();
    assert(nA > 0 && nB > 0);
    int mA = A[0].size(); int mB = B[0].size();
    assert(mA == nB);
    vector<BitSet> ret(nA, BitSet(mB));
    for(int i=0; i<nA; i++){
        for(int j=0; j<mA; j++){
            if(A[i].test(j)){
                ret[i] ^= B[j];
            }
        }
    }
    return ret;
}