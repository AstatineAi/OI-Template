/*
Luogu P3388 Articulation Point
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

constexpr int N = 20005;
constexpr int M = 100005;
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
		fclose(IS),fclose(OS);
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
		static int sta[11];int top = 0;
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
}e[M << 1];
inline void AddEdge(int st,int ed) {
	e[++ecnt] = (Edge) {head[st],ed},head[st] = ecnt;
	e[++ecnt] = (Edge) {head[ed],st},head[ed] = ecnt;
}

int dfs_clock;
int dfn[N],low[N];
bool cut[N];

void tarjan(int u,int _f) {
	dfn[u] = low[u] = ++dfs_clock;
	int c = 0;
	repg(i,u) {
		int v = e[i].to;
		if(!dfn[v]) {
			tarjan(v,u),++c;
			low[u] = std::min(low[u],low[v]);
			if(low[v] >= dfn[u]) cut[u] = 1;
		}
		else if(dfn[v] < dfn[u] && v != _f)
			low[u] = std::min(low[u],dfn[v]); 
	}
	if(c == 1 && _f == 0)
		cut[u] = 0;
}

int main() {
	init_IO();
	mems(head,-1);
	int n = read(),m = read();
	rep(i,1,m) AddEdge(read(),read());
	rep(i,1,n) if(!dfn[i])
		tarjan(i,0);
	int ans = 0;
	rep(i,1,n) if(cut[i])
		++ans;
	write(ans),enter;
	rep(i,1,n) if(cut[i])
		write(i),space;
	end_IO();
	return 0;
}