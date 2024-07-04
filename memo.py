


mod = 998244353
INF = float('INF')



# 標準入力
S = input()
S = list(input())
S, T = input().split()
N = int(input())
N, M = map(int, input().split())
A = list(map(int,input().split()))



# 複数行同時読み込み(例)
A = [list(map(int,input().split())) for _ in range(N)]
S = [list(input()) for _ in range(N)]



# 1-indexed を 0-indexed に直して受け取る
N = int(input())-1
N, M = map(lambda x: int(x)-1, input().split())
A = list(map(lambda x: int(x)-1, input().split()))



# defaultdict
from collections import defaultdict
d = defaultdict(lambda: 0)



# 二分探索 (A.sort()されている必要がある)
import bisect
print(bisect.bisect(A,N))



# sortedset, sortedlist (平衡二分木)
# (基本 priority queue よりこっちの方が実装が楽?? 初期化が重いけど)
# 値の追加，削除，取得がO(logN)
# 詳細 https://qiita.com/Shirotsume/items/706742162db68c481c3c
from sortedcontainers import SortedSet
S = SortedSet(A) # O(NlogN)
from sortedcontainers import SortedList
S = SortedList(A) # O(NlogN)



# 昇順ソート
A.sort()
B = sorted(A)



# 降順ソート
A.sort(reverse=True)
B = sorted(A, reverse=True)



# ある要素についてソート
A.sort(key = lambda x: x[0])



# Nの逆元 (modは素数，Nはmodで割り切れない整数のとき)
pow(N,-1,mod)



# copy
import copy
B = copy.copy(A)
B = copy.deepcopy(A)



# 集合の演算
C = list(set(A) | set(B)) #和集合
C = list(set(A) & set(B)) #積集合



# 再帰回数上限解放
import sys
sys.setrecursionlimit(10**8)



# 逆元の計算
pow(N, -1, 998244353)



# メモ化再帰
from functools import cache
@cache
def f():
    return 0



# n進数
int(N, base=M) #M進数を10進数に(接頭辞はあってもなくてもよい)
print(f'{N:b}') #接頭辞なし文字列(結果はstr)(2進数に)
print(f'{N:o}') #接頭辞なし文字列(結果はstr)(8進数に)
print(f'{N:h}') #接頭辞なし文字列(結果はstr)(16進数に)



# bit演算
print(N&M) #AND
print(N|M) #OR
print(N^M) #XOR
print(~N) #NOT
print(N>>M) #shift(右)
print(N<<M) #shift(左)



# 置換
print(S.replace('(', '[').replace(')', ']')) #strが引数



# 反転
print(S[::-1])



# 文字列定数
import string
print(string.ascii_lowercase) #abcdefghijklmnopqrstuvwxyz
print(string.ascii_uppercase) #ABCDEFGHIJKLMNOPQRSTUVWXYZ
print(string.digits) #0123456789
print(string.hexdigits) #0123456789abcdefABCDEF
print("a".upper()) #大文字に変換
print("A".lower()) #小文字に変換



# リストの重複削除
B = list(set(A))



# すべての順列を列挙
import itertools
print(list(itertools.product(A,repeat=M))) #集合のM重直積
print(list(itertools.permutations(A,M))) #nPm, M省略でM=N
print(list(itertools.combinations(A,M))) #nCm
print(list(itertools.combinations_with_replacement(A,M))) #nHm



# キュー、スタック、デック
from collections import deque
d = deque()
d.append('a') #right
d.pop()
d.appendleft('a') #left
d.popleft()



# enumerate (for文でindexも使いたいときに新しい配列を定義しなくて済む)
enumerate(A) # [(i,A[i]) for i in range(N)]



# 累積和 (普通に実装しても大した手間ではないが...)
import itertools
B = list(itertools.accumulate(A))



# priority queue
import heapq
heapq.heapify(A) # O(N)
heapq.heappush(A, 10) # O(logN)
print(A[0]) # min O(1)
heapq.heappop(A) # min を pop O(N) (maxを取り出したい場合は全て-1倍で実装し、最小値を-1倍する)



# エラトステネスの篩 O(NloglogN)
def sieve_of_eratosthenes(n):
    primes = [True] * (n+1)
    primes[0], primes[1] = False, False
    for i in range(2, int(n**0.5)+1):
        if primes[i]:
            for j in range(i**2, n+1, i):
                primes[j] = False
    return [num for num, is_prime in enumerate(primes) if is_prime]



# 高速な素因数分解 (O(sqrt(N)))
def factorization(n):
    arr = []
    temp = n
    for i in range(2, int(-(-n**0.5//1))+1):
        if temp%i==0:
            cnt=0
            while temp%i==0:
                cnt+=1
                temp //= i
            arr.append([i, cnt])

    if temp!=1:
        arr.append([temp, 1])

    if arr==[]:
        arr.append([n, 1])

    return arr



# 拡張ユークリッドの互除法 (O(log(a,b)))
# return g, x, y
# ax + by = g なる g, x, y であって， |g| は |a| と |b| の最小公倍数
def extended_gcd(a, b):
    if b == 0:
        return a, 1, 0
    else:
        d, x, y = extended_gcd(b, a % b)
        return d, y, x - (a // b) * y



# Bit全探索 O(2^N)
# 0から2^N-1までを2進数に直してもいい(N進数のところを参照)けど，
# 次のように集合の直積を使って実装する手もある(超楽になるわけでもないけど...)
from itertools import product
for i in product([0, 1], repeat = N):
    for j in range(N):
        i[j] # i 通り目の j 番目のビット



# メモ化再帰
from functools import lru_cache
@lru_cache(maxsize=None)
def f():
    return 0
    
    

# 座標圧縮 
# https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_4_A&lang=ja (2次元座標圧縮の基本問題)



# 深さ優先探索 (DFS, Deapth First Search)
# 普通に再帰で実装するとできる探索
# 深くなりすぎないときはこっちの方が実装が楽
# たとえば以下を参照されたい(貼るほどでもないが...)
# https://github.com/E869120/kyopro-tessoku/blob/main/codes/python/chap09/answer_A62.py



# 幅優先探索 (BFS, Breadth First Search)
# 迷路の探索など，最悪のケースの深さがめちゃめちゃ深い場合に使える
# たとえば以下を参照されたい
# https://github.com/E869120/kyopro-tessoku/blob/main/codes/python/chap09/answer_A63.py
        


# 二部グラフ判定
# https://prd-xxx.hateblo.jp/entry/2017/10/13/004256
# https://atcoder.jp/contests/math-and-algorithm/submissions/36866121 (謎のライブラリ)
# https://atcoder.jp/contests/math-and-algorithm/submissions?f.LanguageName=Python&f.Status=AC&f.Task=math_and_algorithm_ao&f.User=&orderBy=source_length (提出結果)



# Convex Hull Trick
# https://tjkendev.github.io/procon-library/python/convex_hull_trick/deque.html



# ダブリング
# https://zenn.dev/fjnkt98/articles/3c0c21778b6101



# 最適二分探索木問題 (貪欲でいけるハフマン木問題と似てる)
# https://atcoder.jp/contests/atc002/tasks/atc002_c
        

        
# クヌース–モリス–プラット法 (KMP法, Knuth–Morris–Pratt algorithm)
# https://qiita.com/t_fuki/items/f32406da0233ed51ec86



# Rolling Hash

B = 200
MOD = 10**16 + 61

# 半分全列挙

# 最大二部マッチング問題：最大流問題に帰着可能

# Grundy 数 (Nimまわり)

# Manacherのアルゴリズム (回文)

# 区間を set で管理するテクニック

# Dynamic Segment Tree

# Chu-Liu/Edmond のアルゴリズム (最小有向全域木問題)

# 最長共通部分列(LCS)

# 最長増加部分列(LIS)

# 最小全域木問題(MST)

    # ブルーフカ(Borůvka)法

    # クラスカル(Kruskal)法

    # プリム(Prim)法

# ゼータ変換 / メビウス変換
# https://atcoder.jp/contests/abc349/tasks/abc349_f

# BM (Boyer-Moore)
# Trie木
# KMP (Knuth-Morris-Pratt)

# ac-library-python
# https://github.com/not522/ac-library-python/tree/master (ソース)

    # 使ってみた集
    # https://qiita.com/hyouchun/items/4958618268407a5442cc
    # https://qiita.com/hyouchun/items/3eee499a7ef31ca55b46

    # セグメントツリー (Segment Tree) 
    # だいたいのクエリはO(log(N))
    # 木にはintまたはlistをのせる
    # RMQ(区間最大クエリ)やRSQ(区間和クエリ)，転倒数の計算など
    # Aの転倒数：st[A[i]] += 1 をしながら st の A[i] 番地より右の領域の総和をiに関して足し続ければ良い(O(NlogN))
    # https://output-zakki.com/inversion_number/ (転倒数についての詳細な解説記事)

    # 遅延評価セグメントツリー Lazy Segment Tree (セグ木の強化版だけど初期設定が大変)
    # だいたいのクエリはO(log(N))
    # RAQ(区間加算クエリ)、RUQ(区間更新クエリ)など
    # https://atcoder.jp/contests/abc340/submissions/50202852 (最近のABCの提出例)
    # https://qiita.com/hyouchun/items/1748bd320d2188a999f2 (LazySegtreeの解説1)
    # https://betrue12.hateblo.jp/entry/2020/09/22/194541 (LazySegtreeの解説2)

    # UnionFind
    # だいたいのクエリはO(alpha(N))
    # https://github.com/not522/ac-library-python/blob/master/atcoder/dsu.py (定義)
    # https://atcoder.jp/contests/practice2/submissions/50188361 (ACL Practice Contest)
    # https://note.nkmk.me/python-union-find/ (ベタ書き)

    # 中国剰余定理 (CRT Chinese Remainder Theorem) (使ってみた集には無い)
    # 配列mとrを渡すと，各iについて，m[i]を法としてr[i]と合同であるようなxをO((配列の長さ)log(m[i]のiに関する最小公倍数))で求める
    # m[i]のiに関する最小公倍数をzとする．0<=y<zであるようなyであって，zを法としてxと合同なy，およびzが(y,z)の形でreturnされる
    # https://atcoder.jp/contests/abc186/submissions/48993543 (ABC186E)
    # https://qiita.com/recuraki/items/11fd78580e03a5a6d58c (上記提出に関連する解説記事)

    # 最大流 最小カット (Ford Fulkerson or Dinic)
    # ざっくり言ってO(M*N^2)程度で最大フローを計算できる
    # 辺を追加すると，追加した順番でナンバリングされる(0-indexed)

    # 最小費用流 (Minimum-cost flow)
    # (最大流量, 最小コスト)，または(流量, 最小コスト)のグラフをO(Flow*(N+M)log(N))程度で計算
    # 辺を追加すると，追加した順番でナンバリングされる(0-indexed)
    # 使ってみた集に載ってる例題がかなり分かりやすい

    # 強連結成分分解 (StronglyConnectedComponent, SCC)，トポロジカルソート (Topological Sort)
    # graph.scc()するだけでSCCもトポロジカルソートもしてくれる(O(N+M))
    # 説明：これは有向グラフの話で，互いに行き来できる頂点をグルーピングすることをSCCという．
    # SCCしたら，たとえば「グループAからグループBへは行けるけど，逆は無理」みたいなことが生じうる
    # このとき，AよりBの方が後ろにくるようにグループを並べ替えることをトポロジカルソートという

    # 2-SAT
    # twosat.satisfiable()で2-SAT問題をO((命題変数の数)+(制約条件の数))で解く(TrueかFalse)
    # twosat.answer()で具体的な真理値割り当てをreturnする(直近でTrueだったtwosat.satisfiable()のときの割り当て)
    # 一度もtwosat.satisfiable()しないでtwosat.answer()すると各要素がFalseであるような配列が返ってきてしまう

    # Suffix Array, LCP Array (Longest Common Prefix Array)
    # たとえば，文字列 S に対して，S の相異なる部分文字列の個数を求める問題をO(N)で解ける
    # 文字列SのSuffix Arrayは，i番地に文字列S[i:]が入っているようなリストを辞書順にソートしたときにインデックスがどこから移ってきたか，ということについてのリスト(O(N))
    # 文字列SのLCP Arrayは，i番地に文字列S[i:]が入っているようなリストのi番地とi+1番地の文字列の最長共通接頭辞の文字数が格納されているようなリスト(O(N))
    # Z algorithm もO(N)でできる (https://qiita.com/Pro_ktmr/items/16904c9570aa0953bf05)

    # FFT (convolution)
    # このライブラリはちょっと遅い 下記のベタ書きも参考に
    # https://atcoder.jp/contests/atc001/submissions/48410412 (ベタ書き)(ATC)
    # https://atcoder.jp/contests/practice2/submissions/48921277 (ベタ書き)(ALCP)
    # https://github.com/shakayami/ACL-for-python (上記提出はshakayamiさんのacl-for-python)(O(NlogN+log(mod)))

    # floor_sum
    # (a*i + b)/m の floor の i についての和 を O(log(n+m+a+b)) で計算できる (いつ使うねん)

    # Fenwick Tree (BIT)
    # セグ木で同じことができるのでセグ木でおけ



# ライブラリその他 (個人が作成)
# https://github.com/ryusuke920/AtCoder-Library

    # オイラーツアー (Euler tour)
    # 根付きを根からDFSし根に戻ってくる行きと戻りの経路を1次元のテーブルに記録したもの
    # 同時に、辿る際に以下のような情報を記録し、それらに対してRMQやRSQを適応することで
    # 木に対するいくつかのクエリを高速に行える

    # 木の中心

    # 木の直径

    # 最小共通祖先 (LCA, LowestCommonAncestor)

    # ベルマンフォード(Bellman_Ford)法 
    # 負辺を含む単一最短経路問題を求める 負閉路の検出も可能

    # ダイクストラ(Dijkstra)法 O(NlogN) or O(MlogN)
    # 単一頂点からの最小距離を求める

    # ワーシャルフロイド(Warshall_Floyd)法 O(N^3)

    # ボイヤー・ムーア(BoyerMoore)法
    # O(|S|)で見つけたい連続部分文字列の存在を判定
    # https://github.com/ryusuke920/AtCoder-Library/blob/main/String/BoyerMoore.py
    # 上のリンクには1か所邪魔なprint関数が入ってるので注意



# 目指せ茶(初級)
# https://qiita.com/e869120/items/f1c6f98364d1443148b3



# 目指せ水(中級)
# https://qiita.com/e869120/items/eb50fdaece12be418faa



# 目指せ赤(上級)
# https://qiita.com/e869120/items/acba3dd8649d913102b5



"""

教える場合

print
intとstrの違い
四則演算
配列について(多次元配列, 要素の追加/削除)
if, for, while(複合代入演算子)
標準入出力(forでの入出力)
関数(max,minやdef)
文字列の分割, 結合
辞書(連想配列)
deepcopyの説明

#整数の受け付け(1つ)
N = int(input())

#スペースで区切られた整数の受け付け(いくつでも)
N, M = map(int, input().split())

#スペースで区切られた整数を配列化して受け付け
A = list(map(int,input().split()))

#文字列の受け付け
S = input()

#スペースで区切られた文字列の受け付け(いくつでも)
S, T = input().split()

#文字列を分離して配列化して受け付け
S = list(input())

https://atcoder.jp/contests/abc283/tasks/abc283_a

"""