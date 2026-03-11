#pragma once

#include <vector>
#include <functional>

/// @brief f(i, j)がmonotoneのときにO(H + Wlog(H))で各iについてf(i, j)が最小値をとるjと最小値をペアにして返す
/// @tparam Compare a < bの真偽を返す関数オブジェクト
/// @tparam T f(i, j)で返る型
/// @param H f(i, j)のiのサイズ
/// @param W f(i, j)のjのサイズ
/// @param f f(i, j)でTが返るmonotone
/// @param comp fで返る値2つを比較する。comp(a, b)でa < bの真偽を返す
/// @return 各iに対して{最小値を取るj, 最小値}を持った配列
template<typename T, typename ft,  typename Compare=std::less<T>>
std::vector<std::pair<int,T>> monotone_minima(int H, int W, const ft &f, const Compare &comp = Compare()){
  std::vector<std::pair<int, T>> dp(H);
  std::function<void(int, int, int, int)> dfs = [&](int top, int bottom, int left, int right) {
    if(top > bottom) return;
    int line = (top + bottom) / 2;
    T ma;
    int mi = -1;
    for(int i = left; i <= right; i++) {
      T cst = f(line, i);
      if(mi == -1 || comp(cst, ma)) {
        ma = cst;
        mi = i;
      }
    }
    dp[line] = std::make_pair(mi, ma);
    dfs(top, line - 1, left, mi);
    dfs(line + 1, bottom, mi, right);
  };
  dfs(0, H - 1, 0, W - 1);
  return dp;
}