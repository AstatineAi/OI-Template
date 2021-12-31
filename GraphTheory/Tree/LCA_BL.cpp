/*
Luogu P3379 LCA : Binary Lifting
Author : AstatineAi
*/
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <cctype>
#include <climits>
#include <cassert>
#include <algorithm>
#include <iostream>
#include <utility>

#define space putC(' ')
#define enter putC('\n')
#define El_Pueblo_Unido_Jamas_Sera_Vencido

#define rep(a,b,c) for(int a = (b);a <= (c);++a)
#define repb(a,b,c) for(int a = (b);a >= (c);--a)
#define repg(a,b) for(int a = head[b]; ~a ; a = e[a].nxt)
#define mems(a,b) memset(a,b,sizeof(a))

#define DEBUG
// #define NDEBUG // ban assert
#define O(a) std::cerr<<#a<<':'<<a<<std::endl;

typedef long long ll;
typedef unsigned long long ull;
typedef __uint128_t I128;
typedef double db;
typedef std::pair<int,int> pii;

constexpr int N = 500005;
constexpr int INF = 1e9;
constexpr int MOD = 998244353;

namespace IO {
	#define IS stdin
	#define OS stdout
	constexpr int IOLIM = 10000;
	char ibuf[IOLIM],obuf[IOLIM];
	char *_i = ibuf,*_o = obuf;
	inline void init_IO() {
		fread(ibuf,IOLIM,sizeof(char),IS);
	}
	
	inline char getC() {
		if(_i == ibuf + IOLIM) {
			mems(ibuf,0);
			fread(ibuf,IOLIM,sizeof(char),IS);
			_i = ibuf;
		}
		return *_i++;
	}
	
	inline void end_IO() {
		fwrite(obuf,_o - obuf,sizeof(char),OS);
	}
	
	inline void putC(char ch) {
		if(_o == obuf + IOLIM) {
			fwrite(obuf,_o - obuf,sizeof(char),OS);
			_o = obuf;
		}
		*_o++ = ch;
	}
	
	inline int read() {
		int res = 0;char ch = getC();
		while(!isdigit(ch)) ch = getC();
		while(isdigit(ch)) {
			res = res * 10 + (ch ^ 48);
			ch = getC();
		}
		return res;
	}
	
	inline void write(int x) {
		static int sta[20];int top = 0;
		do
			sta[top++] = x % 10,x /= 10;
		while(x);
		while(top) putC(sta[--top] + '0');
	}
}
using IO::init_IO;
using IO::end_IO;
using IO::read;
using IO::write;
using IO::putC;

int head[N],ecnt = -1;
struct Edge {
	int nxt,to;
}e[N << 1];
inline void AddEdge(int st,int ed) {
	e[++ecnt] = (Edge) {head[st],ed},head[st] = ecnt;
	e[++ecnt] = (Edge) {head[ed],st},head[ed] = ecnt;
}

#define l2(x) (31 - __builtin_clz(x))

int dfs_clock;
int fa[N],dfn[N],siz[N];
int anc[19][N],dep[N];
void dfs(int u,int _f) {
	anc[0][u] = _f,dfn[u] = ++dfs_clock;
	dep[u] = dep[_f] + 1,siz[u] = 1;
	int lim = l2(dep[u]);
	rep(i,1,lim)
		anc[i][u] = anc[i - 1][anc[i - 1][u]];
	repg(i,u) {
		int v = e[i].to;
		if(v == _f) continue;
		dfs(v,u);
		siz[u] += siz[v];
	}
}

inline bool IsAnc(int u,int v) {
	return dfn[u] <= dfn[v] && dfn[u] + siz[u] - 1 >= dfn[v];
}

inline int LCA(int u,int v) {
	if(dep[u] > dep[v])
		std::swap(u,v);
	if(IsAnc(u,v)) return u;
	repb(i,18,0) {
		int p = anc[i][u];
		if(p && !IsAnc(p,v))
			u = p;
	}
	return anc[0][u];
}

int main() {
	init_IO();
	mems(head,-1);
	int n = read(),m = read(),r = read();
	rep(i,1,n - 1) AddEdge(read(),read());
	dfs(r,r);
	while(m--) {
		int u = read(),v = read();
		write(LCA(u,v)),enter;
	}
	end_IO();
	return 0;
}