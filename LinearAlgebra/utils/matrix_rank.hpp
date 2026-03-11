#include <vector>
#include "gaussian_elimination.hpp"
using namespace std;

template<typename T>
int matrix_rank(vector<vector<T>> A){
    int rank;
    gaussian_elimination(A, rank);
    return rank
}
