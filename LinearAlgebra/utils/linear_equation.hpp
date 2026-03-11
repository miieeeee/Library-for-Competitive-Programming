#include <vector>
using namespace std;
#include "gaussian_elimination.hpp"


/// @brief 線形方程式Ax = bを解く。
/// @tparam T 
/// @param A 
/// @param b 
/// @return {解一つ, 基底}. 解がなければ空.
template<typename T>
pair<vector<T>, vector<vector<T>>> linear_equation(vector<vector<T>> A, vector<T> &b) {
    const int N = A.size();
    if (N == 0) return {{}, {}};
    const int M = A[0].size();

    // 拡大係数行列を作る
    vector<vector<T>> mat(N, vector<T>(M + 1));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) mat[i][j] = A[i][j];
        mat[i][M] = b[i];
    }

    int rank = 0;
    vector<int> pivot_col(M, -1);

    for (int col = 0; col < M; col++) {
        int sel = -1;
        for (int row = rank; row < N; row++) {
            if (mat[row][col] != T(0)) {
                sel = row;
                break;
            }
        }
        if (sel == -1) continue;

        swap(mat[rank], mat[sel]);
        T inv = T(1) / mat[rank][col];
        for (int j = col; j <= M; j++) mat[rank][j] *= inv;

        for (int row = 0; row < N; row++) {
            if (row != rank && mat[row][col] != T(0)) {
                T factor = mat[row][col];
                for (int j = col; j <= M; j++) {
                    mat[row][j] -= factor * mat[rank][j];
                }
            }
        }
        pivot_col[col] = rank++;
    }

    // 一意解が存在するかチェック（不整合がないか）
    for (int row = rank; row < N; row++) {
        if (mat[row][M] != T(0)) {
            // 解なし
            return {{}, {}};
        }
    }

    // 一つの解を構築
    vector<T> x(M);
    for (int col = 0; col < M; col++) {
        if (pivot_col[col] != -1) {
            x[col] = mat[pivot_col[col]][M];
        } else {
            x[col] = T(0);  // 自由変数は 0 にする（任意解の1つ）
        }
    }

    // 解空間の基底ベクトル（自由変数に対するベクトルを構築）
    vector<vector<T>> basis;
    for (int col = 0; col < M; col++) {
        if (pivot_col[col] == -1) {
            // 自由変数 col に対する方向ベクトルを作成
            vector<T> vec(M, T(0));
            vec[col] = T(1);
            for (int j = 0; j < M; j++) {
                if (pivot_col[j] != -1) {
                    vec[j] = -mat[pivot_col[j]][col];
                }
            }
            basis.push_back(vec);
        }
    }

    return {x, basis};
}

pair<BitSet, vector<BitSet>> linear_equation(vector<BitSet> A, BitSet b) {
    int n = A.size();
    if (n == 0) return {BitSet(0), {}};
    int m = A[0].size();

    // 拡大係数行列の作成
    for (int i = 0; i < n; i++) {
        A[i].set(m, b[i]);  // A[i] の右端に b[i] を追加
    }

    int rank = 0;
    vector<int> pivot_col(m, -1);

    for (int col = 0; col < m; col++) {
        int sel = -1;
        for (int row = rank; row < n; row++) {
            if (A[row].test(col)) {
                sel = row;
                break;
            }
        }
        if (sel == -1) continue;

        swap(A[rank], A[sel]);
        pivot_col[col] = rank;

        for (int row = 0; row < n; row++) {
            if (row != rank && A[row].test(col)) {
                A[row] ^= A[rank];
            }
        }
        rank++;
    }

    // 解が存在するか確認
    for (int row = rank; row < n; row++) {
        if (A[row].test(m)) {
            // 矛盾がある（0 = 1）→ 解なし
            return {BitSet(0), {}};
        }
    }

    // 一つの解を構築
    BitSet x(m);
    for (int col = 0; col < m; col++) {
        if (pivot_col[col] != -1) {
            x[col] = A[pivot_col[col]].test(m);
        } else {
            x[col] = 0;  // 自由変数は 0 にする
        }
    }

    // 解空間の基底を構築
    vector<BitSet> basis;
    for (int col = 0; col < m; col++) {
        if (pivot_col[col] == -1) {
            BitSet vec(m);
            vec[col] = 1;
            for (int j = 0; j < m; j++) {
                if (pivot_col[j] != -1 && A[pivot_col[j]].test(col)) {
                    vec[j] = 1;
                }
            }
            basis.push_back(vec);
        }
    }

    return {x, basis};
}
