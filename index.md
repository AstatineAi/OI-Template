# OI-Templates by AstatineAi

使用统一命名方式,在给定缺省源下直接可以使用的模板库.

代码保证在 NOI Linux 2.0 内置 GNU GCC 的 `-std=c++14` 下可以编译并运行.

不定时更新.

可能出现大量 C 风格与 C++ 风格混用的情况.

为了这个模板库,我需要把写过的模板都重写一遍,某种意义上的模板马拉松(?).

# 目录 Catalogue

- [Source](https://github.com/AstatineAi/OI-Template/blob/main/Source/Source.cpp)

## 基础算法 Basic Algo

### 排序 Sorting

- [归并排序](https://github.com/AstatineAi/OI-Template/blob/main/BasicAlgo/MergeSort.cpp) Merge Sort
- [基数排序](https://github.com/AstatineAi/OI-Template/blob/main/BasicAlgo/RadixSort.cpp) Radix Sort

### 搜索 Search

- 深度优先搜索 DFS (真的需要这种模板吗?)
- 广度优先搜索 BFS (真的需要这种模板吗?)
- [A*](https://github.com/AstatineAi/OI-Template/blob/main/BasicAlgo/Astar.cpp)
- [迭代加深 A* 搜索](https://github.com/AstatineAi/OI-Template/blob/main/BasicAlgo/IDAstar.cpp) Iterative Deepening A*
- [舞蹈链](https://github.com/AstatineAi/OI-Template/blob/main/BasicAlgo/DLX.cpp) Dancing Links (DLX)

## 动态规划 Dynamic Programming

DP 并没有所谓的 "模板" 可言,相对自由多变.

可以说写出了某种 DP 是表层,但能设计 DP 状态和转移才是深层.

 - "动态" DP
 - 插头 DP

## 字符串 String

- [字符串哈希](https://github.com/AstatineAi/OI-Template/blob/main/String/StringHash.cpp) String Hash
- [字典树](https://github.com/AstatineAi/OI-Template/blob/main/String/Trie.cpp) Trie
- [前缀函数与 KMP 字符串匹配](https://github.com/AstatineAi/OI-Template/blob/main/String/KMP.cpp) Prefix Func and Knuth-Morris-Pratt Algo
- 扩展 KMP Z-Func
- [AC 自动机](https://github.com/AstatineAi/OI-Template/blob/main/String/AhoCorasickAutomaton.cpp) Aho-Corasick Automaton
- [后缀数组](https://github.com/AstatineAi/OI-Template/blob/main/String/SuffixArray.cpp) Suffix Array
- [后缀自动机](https://github.com/AstatineAi/OI-Template/blob/main/String/SuffixAutomaton.cpp) Suffix Automaton
- [广义后缀自动机](https://github.com/AstatineAi/OI-Template/blob/main/String/GeneralSAM.cpp) General SAM
- [Manacher 算法](https://github.com/AstatineAi/OI-Template/blob/main/String/Manacher.cpp)

## 图论 Graph Theory

- 树上问题
    - [树直径](https://github.com/AstatineAi/OI-Template/blob/main/GraphTheory/Tree/TreeDiameter.cpp) Tree Diameter
    - [树重心](https://github.com/AstatineAi/OI-Template/blob/main/GraphTheory/Tree/TreeCentroid.cpp) Tree Centroid
    - 最近公共祖先 Lowest Common Ancestor
        - [欧拉序 & RMQ](https://github.com/AstatineAi/OI-Template/blob/main/GraphTheory/Tree/LCA_RMQ.cpp) Euler Tour Technique
        - [重链剖分](https://github.com/AstatineAi/OI-Template/blob/main/GraphTheory/Tree/LCA_HLD.cpp) Heavy Light Decomposition
        - [树上倍增](https://github.com/AstatineAi/OI-Template/blob/main/GraphTheory/Tree/LCA_BL.cpp) Binary Lifting
        - [动态树](https://github.com/AstatineAi/OI-Template/blob/main/GraphTheory/Tree/LCA_LCT.cpp) Link-Cut Tree
    - 树链剖分
        - [重链剖分](https://github.com/AstatineAi/OI-Template/blob/main/GraphTheory/Tree/HeavyLightDecomposition.cpp) Heavy Light Decomposition
        - [长链剖分](https://github.com/AstatineAi/OI-Template/blob/main/GraphTheory/Tree/LongShortDecomposition.cpp) Long Short Decompostiton
        - [长链剖分求树上 k 级祖先](https://github.com/AstatineAi/OI-Template/blob/main/GraphTheory/Tree/LevelAncestor.cpp) Level Ancestor
    - [树上启发式合并](https://github.com/AstatineAi/OI-Template/blob/main/GraphTheory/Tree/DSUonTree.cpp) DSU on Tree
    - 虚树 Virtual Tree
    - [点分治](https://github.com/AstatineAi/OI-Template/blob/main/GraphTheory/Tree/TreeDivideandConquer.cpp) Tree Divide and Conquer
    - 点分树 Dynamic Tree Divide
    - 树哈希 Tree Hash
- [最小生成树](https://github.com/AstatineAi/OI-Template/blob/main/GraphTheory/MST.cpp)  Minimum Spanning Tree
- 单源最短路径 Single Source Shortest Paths
    - [堆优化 Dijkstra 算法](https://github.com/AstatineAi/OI-Template/blob/main/GraphTheory/Dijkstra.cpp)
    - [Bellman-Ford 算法](https://github.com/AstatineAi/OI-Template/blob/main/GraphTheory/BellmanFord.cpp)
    - [队列优化的 Bellman-Ford 算法](https://github.com/AstatineAi/OI-Template/blob/main/GraphTheory/SPFA.cpp)
- 全源最短路径 All Pairs Shortest Paths
    - [Floyd-Warshall 算法](https://github.com/AstatineAi/OI-Template/blob/main/GraphTheory/FloydWarshall.cpp)
    - [Johnson 算法](https://github.com/AstatineAi/OI-Template/blob/main/GraphTheory/Johnson.cpp)
- [差分约束](https://github.com/AstatineAi/OI-Template/blob/main/GraphTheory/DifferenceConstraints.cpp) Difference Constraints
- [严格次短路](https://github.com/AstatineAi/OI-Template/blob/main/GraphTheory/SubShortestPath.cpp) Strictly Sub-shortest Path
- k 短路 Kth Shortest Path
    - [普通 A* k 短路](https://github.com/AstatineAi/OI-Template/blob/main/GraphTheory/KthShortestPath.cpp)
    - 可持久化可并堆优化
- [强连通分量](https://github.com/AstatineAi/OI-Template/blob/main/GraphTheory/SCC.cpp) Strongly Connecting Components
- [割点](https://github.com/AstatineAi/OI-Template/blob/main/GraphTheory/ArticulationPoint.cpp) & [桥](https://github.com/AstatineAi/OI-Template/blob/main/GraphTheory/Bridge.cpp) Articulation Point and Bridge
- 圆方树 Block Forest
- [2-SAT](https://github.com/AstatineAi/OI-Template/blob/main/GraphTheory/2SAT.cpp)
- [欧拉路径 & 欧拉回路](https://github.com/AstatineAi/OI-Template/blob/main/GraphTheory/EulerianTrail.cpp) Eulerian Trail & Eulerian Circuit
- [拓扑排序](https://github.com/AstatineAi/OI-Template/blob/main/GraphTheory/TopoSort.cpp) Topo Sort
- [最大流](https://github.com/AstatineAi/OI-Template/blob/main/GraphTheory/MaixmumFlowDinic.cpp) Maximum Flow - Dinic Algo
- 费用流 
    - [O(nmf) 伪多项式](https://github.com/AstatineAi/OI-Template/blob/main/GraphTheory/SSP.cpp)
    - [多项式](https://github.com/AstatineAi/OI-Template/blob/main/GraphTheory/PrimalDual.cpp) poly(VE)
- [二分图最大匹配](https://github.com/AstatineAi/OI-Template/blob/main/GraphTheory/BipartiteMatching.cpp) Maximum Bipartite Matching
- [二分图最大权匹配](https://github.com/AstatineAi/OI-Template/blob/main/GraphTheory/WeightBipartiteMatching.cpp) Maximum Weight Bipartite Matching

## 数据结构 Data Structure

- [单调栈](https://github.com/AstatineAi/OI-Template/blob/main/DataStructure/MinimumStack.cpp) Minimum Stack
- [单调队列](https://github.com/AstatineAi/OI-Template/blob/main/DataStructure/MinimumQueue.cpp) Minimum Queue
- [稀疏表](https://github.com/AstatineAi/OI-Template/blob/main/DataStructure/SparseTable.cpp) Sparse Table
- [并查集](https://github.com/AstatineAi/OI-Template/blob/main/DataStructure/DisjointSetUnion.cpp) Disjoint Set Union
- [哈希表](https://github.com/AstatineAi/OI-Template/blob/main/DataStructure/HashTable.cpp) Hash Table
- 堆 Heap
    - [二叉堆](https://github.com/AstatineAi/OI-Template/blob/main/DataStructure/BinaryHeap.cpp) Binary Heap
    - [左偏树](https://github.com/AstatineAi/OI-Template/blob/main/DataStructure/LeftistTree.cpp) Leftist Tree
- [树状数组](https://github.com/AstatineAi/OI-Template/blob/main/DataStructure/BIT.cpp) Fenwick Tree/Binary Indexed Tree
- [二维树状数组](https://github.com/AstatineAi/OI-Template/blob/main/DataStructure/2DBIT.cpp) 2D Fenwick Tree
- [线段树](https://github.com/AstatineAi/OI-Template/blob/main/DataStructure/SegmentTree.cpp) Segment Tree
- [可持久化权值线段树/主席树](https://github.com/AstatineAi/OI-Template/blob/main/DataStructure/PersistantSegmentTree.cpp) Persistent Segment Tree
- 李超线段树 Li Chao Tree
- 吉老师线段树 Segment Tree Beats
- [划分树](https://github.com/AstatineAi/OI-Template/blob/main/DataStructure/DividingTree.cpp) Dividing Tree
- [猫树](https://github.com/AstatineAi/OI-Template/blob/main/DataStructure/CatTree.cpp) Cat Tree
- 平衡树 Self Balanced Tree
    - [伸展树](https://github.com/AstatineAi/OI-Template/blob/main/DataStructure/Splay.cpp) Splay
    - 树堆 Treap
    - 替罪羊树 Scapegoat Tree
- 树套树
    - 线段树套平衡树 BST in SegTree
    - 线段树套线段树 SegTree in SegTree
    - 树状数组套主席树 Chairman Tree in BIT
- K-D Tree
- [Link-Cut Tree](https://github.com/AstatineAi/OI-Template/blob/main/DataStructure/LCT.cpp)

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
- 米勒-拉宾素性测试 Miller-Rabin Primality Test
- 波拉德 Rho 因数分解 Pollard-Rho Algo
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
- [A+B problem,but solved by Dinic's Algorithm](https://github.com/AstatineAi/OI-Template/blob/main/Misc/A%2BB_Dinic.cpp)
- [A Quine Written By C++](https://github.com/AstatineAi/OI-Template/blob/main/Misc/quine.cpp)
- [猴子排序 Bogo Sort](https://github.com/AstatineAi/OI-Template/blob/main/Misc/bogo_sort.cpp)
