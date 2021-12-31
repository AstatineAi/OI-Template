/*
Luogu P3379 LCA : Heavy Light Desompsition
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

int fa[N],dep[N];
int siz[N],hson[N];
void HLD1(int u,int _f) {
	dep[u] = dep[_f] + 1,fa[u] = _f;
	siz[u] = 1;
	repg(i,u) {
		int v = e[i].to;
		if(v == _f) continue;
		HLD1(v,u);
		siz[u] += siz[v];
		if(siz[hson[u]] < siz[v])
			hson[u] = v;
	}
}

int top[N];
void HLD2(int u,int _f) {
	top[u] = _f;
	if(hson[u]) HLD2(hson[u],_f);
	repg(i,u) {
		int v = e[i].to;
		if(v == fa[u] || v == hson[u])
			continue;
		HLD2(v,v);
	}
}

inline int LCA(int u,int v) {
	while(top[u] != top[v]) {
		if(dep[top[u]] < dep[top[v]])
			std::swap(u,v);
		u = fa[top[u]];
	}
	return dep[u] < dep[v] ? u : v;
}

int main() {
	init_IO();
	mems(head,-1);
	int n = read(),m = read(),r = read();
	rep(i,1,n - 1) AddEdge(read(),read());
	HLD1(r,r),HLD2(r,r);
	while(m--) {
		int u = read(),v = read();
		write(LCA(u,v)),enter;
	}
	end_IO();
	return 0;
}