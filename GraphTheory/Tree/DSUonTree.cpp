/*
CF600E : DSU on Tree
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

constexpr int N = 100005;
constexpr int INF = 1e9;
constexpr int MOD = 998244353;

namespace IO {
	#define IS stdin
	#define OS stdout
	// #define IS is
	// #define OS os
	FILE *is,*os;
	constexpr int IOLIM = 10000;
	char ibuf[IOLIM],obuf[IOLIM];
	char *_i = ibuf,*_o = obuf;
	inline void init_IO() {
		#ifndef DEBUG
		is = fopen(".in","r");
		os = fopen(".out","w");
		#endif
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
	
	inline ll read() {
		ll res = 0;char ch = getC();bool m = 1;
		while(!isdigit(ch)) {
			if(ch == '-') m = 0;
			ch = getC();
		}
		while(isdigit(ch)) {
			res = res * 10 + (ch ^ 48);
			ch = getC();
		}
		return m ? res : -res;
	}
	
	inline void write(ll x) {
		if(x < 0) putC('-'),x = -x;
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

int dfs_clock;
int dfn[N],rnk[N];
int siz[N],hson[N];
void dfs_pre(int u,int _f) {
    dfn[++dfs_clock] = u,rnk[u] = dfs_clock;
    siz[u] = 1,hson[u] = -1;
    repg(i,u) {
        int v = e[i].to;
        if(v == _f) continue;
        dfs_pre(v,u);
        siz[u] += siz[v];
        if(hson[u] == -1 || siz[hson[u]] < siz[v])
            hson[u] = v;
    }
}
int n;
ll ans[N];
ll col[N];
ll buc[N];
ll res[N];
int bmx;

inline void Add(int p) {
    res[++buc[p]] += p;
    if(buc[p] > bmx) bmx = buc[p];
}

inline void Del(int p) {
    if(res[buc[p]] == p && bmx == buc[p]) {
        --bmx;
        while(!res[bmx]) --bmx;
    }
    res[buc[p]--] -= p;
}

void dfs(int u,int _f,bool mem) {
    repg(i,u) {
        int v = e[i].to;
        if(v == hson[u] || v == _f) continue;
        dfs(v,u,0);
    }
    if(~hson[u]) dfs(hson[u],u,1);
    repg(i,u) {
        int v = e[i].to;
        if(v == hson[u] || v == _f) continue;
        int r = rnk[v] + siz[v] - 1;
        rep(i,rnk[v],r) Add(col[dfn[i]]);
    }
    Add(col[u]);
    ans[u] = res[bmx];
    if(!mem) {
        int r = rnk[u] + siz[u] - 1;
        rep(i,rnk[u],r) Del(col[dfn[i]]);
    }
}

int main() {
	init_IO();
	mems(head,-1);
	n = read();
	rep(i,1,n) col[i] = read();
	rep(i,1,n - 1) {
	    int st = read(),ed = read();
	    AddEdge(st,ed);
	}
	dfs_pre(1,1);
	dfs(1,1,0);
	rep(i,1,n) write(ans[i]),space;
	end_IO();
	return 0;
}