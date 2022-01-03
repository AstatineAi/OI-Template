/*
Luogu P3381 MCMF : Successive Shortest Path
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
#include <queue>

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

constexpr int N = 5005;
constexpr int M = 50005;
constexpr int INF = 1e9;
constexpr int I = 0x3f3f3f3f;
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
		int res = 0;char ch = getC();bool m = 1;
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
	
	inline void write(int x) {
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
int cur[N];
struct Edge {
	int nxt,to,cap,w;
}e[M << 1];
inline void AddEdge(int st,int ed,int cap,int w) {
	e[++ecnt] = (Edge) {head[st],ed,cap,w},head[st] = ecnt;
	e[++ecnt] = (Edge) {head[ed],st,0,-w},head[ed] = ecnt;
}

int n,m,s,t;
bool vis[N];
int dis[N];
bool SSSP() {
	memset(dis,63,sizeof(int) * (n + 1)),dis[s] = 0;
	std::queue<int> q;q.push(s);
	memcpy(cur,head,sizeof(int) * (n + 1));
	while(!q.empty()) {
		int u = q.front();q.pop();
		vis[u] = 0;
		repg(i,u) {
			int v = e[i].to;
			if(dis[v] > dis[u] + e[i].w && e[i].cap) {
				dis[v] = dis[u] + e[i].w;
				if(!vis[v]) {
					vis[v] = 1;
					q.push(v);
				}
			}
		}
	}
	return dis[t] != I;
}

int minc = 0;
int dfs(int u,int f) {
	if(u == t || !f) return f;
	vis[u] = 1;int maxf = 0,tf;
	for(int i = cur[u]; ~i && f;i = e[i].nxt) {
		int v = e[i].to;cur[u] = i;
		if(vis[v] || dis[v] != dis[u] + e[i].w || !e[i].cap) continue;
		tf = dfs(v,std::min(e[i].cap,f));
		maxf += tf,f -= tf;
		e[i].cap -= tf,e[i ^ 1].cap += tf;
		minc += (tf * e[i].w);
	}
	vis[u] = 0;
	return maxf;
}

void MCMF() {
	int maxf = 0,x;
	while(SSSP()) {
		while(x = dfs(s,INF))
			maxf += x;
	}
	write(maxf),space,write(minc),enter;
}

int main() {
	init_IO();
	n = read(),m = read(),s = read(),t = read();
	memset(head,-1,sizeof(int) * (n + 1));
	rep(i,1,m) {
		int st = read(),ed = read(),cap = read(),w = read();
		AddEdge(st,ed,cap,w);
	}
	MCMF();
	end_IO();
	return 0;
}