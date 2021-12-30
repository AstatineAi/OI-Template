# OI-Templates by AstatineAi

使用统一命名方式,在给定缺省源下直接可以使用的模板库.

代码保证在 NOI Linux 2.0 内置 GNU GCC 的 `-std=c++14` 下可以编译并运行.

不定时更新.

# 目录 Catalogue

- Source

## 基础算法 Basic Algo

### 排序 Sorting

- 归并排序 Merge Sort
- 基数排序 Radix Sort

### 搜索 Search

- 深度优先搜索 DFS (真的需要这种模板吗?)
- 广度优先搜索 BFS (真的需要这种模板吗?)
- A*
- 迭代加深 A* 搜索 Iterative Deepening A*
- 舞蹈链 Dancing Links (DLX)

## 动态规划 Dynamic Programming

DP 并没有所谓的 "模板" 可言,相对自由多变.

可以说写出了某种 DP 是表层,但能设计 DP 状态和转移才是深层.

 - "动态" DP
 - 插头 DP

## 字符串 String

- 字符串哈希 String Hash
- 哈希表 Hash Table
- 字典树 Trie
- 前缀函数与 KMP 字符串匹配 Prefix Func and Knuth-Morris-Pratt Algo
- 扩展 KMP Z-Func
- AC 自动机 Aho-Corasick Automaton
- 后缀数组 Suffix Array
- 后缀自动机 Suffix Automaton
- 广义后缀自动机 General SAM
- Manacher 算法

## 图论 Graph

- 树上问题
    - 树直径 Tree Diameter
    - 树重心 Tree Centroid
    - 最近公共祖先 Lowest Common Ancestor
        - 欧拉序 & RMQ Euler Tour Technique
        - 重链剖分 Heavy Light Decomposition
        - 树上倍增 Binary Lifting
    - 树链剖分
        - 重链剖分 Heavy Light Decomposition
        - 长链剖分 Long Short Decompostiton
    - 树上启发式合并 DSU on Tree
    - 虚树 Virtual Tree
    - 点分治 Tree Divide and Conquer
    - 点分树 Dynamic Tree Divide
    - 树哈希 Tree Hash
- 最小生成树  Minimum Spanning Tree
- 单源最短路径 Single Source Shortest Paths
    - 堆优化 Dijkstra 算法
    - Bellman-Ford 算法
    - 队列优化的 Bellman-Ford 算法
- 全源最短路径 All Pairs Shortest Paths
    - Floyd-Warshall 算法
    - Johnson 算法
- 差分约束 Difference Constraints
- 严格次短路 Strictly Sub-shortest Path
- k 短路 Kth Shortest Path
- 强连通分量 Strongly Connecting Components
- 割点 & 桥 Articulation Point and Bridge
- 圆方树 Block Forest
- 2-SAT
- 欧拉路径 & 欧拉回路 Eulerian Trail & Eulerian Circuit
- 拓扑排序 Topo Sort
- 最大流 Maximum Flow - Dinic Algo
- 费用流 
    - O(nmf) 做法
    - 强多项式 poly(VE)
- 二分图最大匹配 Maximum Bipartite Matching

## 数据结构 Data Structure

- 单调栈 Minimum Stack
- 单调队列 Minimum Queue
- 稀疏表 Sparse Table
- 并查集 Disjoint Set Union
- 堆 Heap
    - 二叉堆 Binary Heap
    - 左偏树 Leftist Tree
- 树状数组 Fenwick Tree/Binary Indexed Tree
- 二维树状数组 2D Fenwick Tree
- 线段树 Segment Tree
- 李超线段树 Li Chao Tree
- 吉老师线段树 Segment Tree Beats
- 划分树 Dividing Tree
- 平衡树 Self Balanced Tree
    - 伸展树 Splay
    - 树堆 Treap
    - 替罪羊树 Scapegoat Tree
- 可持久化权值线段树/主席树 Persistent Segment Tree
- 树套树
    - 线段树套平衡树 BST in SegTree
    - 线段树套线段树 SegTree in SegTree
    - 树状数组套主席树 Chairman Tree in BIT
- K-D Tree
- Link-Cut Tree

## 数学 Math

- 数学基础内容多合一 Basic
    - 快速幂 Quick Power
    - 最大公约数 Greatest Common Divisor
    - 欧拉筛 Euler Seive
    - 乘法逆元 Inverse
    - 扩展欧几里得 ExGCD
- 中国剩余定理 CRT
- 扩展中国剩余定理 ExCRT
- 卢卡斯定理 Lucas Theorem
- 扩展卢卡斯定理 ExLucas Theorem
- BSGS离散对数 Baby Step Giant Step
- 杜教筛 Du's Seive
- 自适应辛普森法 Adaptive Simpson's Rule
- 矩阵快速幂 Matrix Quick Power
- 矩阵求行列式 Determinant
- 矩阵求逆 Inverse Matrix
- 矩阵树定理 Matrix Tree Theorem
- 线性基 Linear Basis
- 高斯消元求解线性方程组 Gauss Elimination
- 拉格朗日插值 Lagarange Intersection
- Nim游戏与 SG 函数 Nim and Sprague-Grundy Theorem
- 多项式科技 Polynomial
    - 快速傅里叶变换 Fast Fourier Transform
    - 快速数论变换 Fast Number Theory Transform
    - 多项式求逆 Poly Inverse
    - 多项式求导/积分 Poly Derivative/Integration
    - 多项式对数函数/指数函数 Poly Ln/Exp

## 计算几何 Computational geometry

- 计算几何模板 Source of Computational geometry
- 二维凸包 2D Convex Hull
- 扫描线 Sweep Line
- 旋转卡壳 Rotating Calipers
- 半平面交 Half Plane Intersection
- 平面最近点对 Nearest Point Pairs

## 杂项 Misc

- 莫队 Mo's Algo
- 01 分数规划 01 Fraction Programming
