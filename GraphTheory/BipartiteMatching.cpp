/*
Luogu P3386 : Maximum Bipartite Matching
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

constexpr int N = 1005;
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
	
	inline void write(ll x) {
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
	int nxt,to,cap;
}e[M << 1];
inline void AddEdge(int st,int ed,int cap) {
	e[++ecnt] = (Edge) {head[st],ed,cap},head[st] = ecnt;
	e[++ecnt] = (Edge) {head[ed],st,0},head[ed] = ecnt;
}

int n,m,s,t;
int dep[N];
bool bfs() {
	std::queue<int> q;q.push(s);
	memset(dep,0,sizeof(int) * (n + 1)),dep[s] = 1;
	memcpy(cur,head,sizeof(int) * (n + 1));
	while(!q.empty()) {
		int u = q.front();q.pop();
		repg(i,u) {
			int v = e[i].to;
			if(dep[v] || !e[i].cap) continue;
			dep[v] = dep[u] + 1;
			q.push(v);
		}
	}
	return dep[t];
}

int dfs(int u,int f) {
	if(u == t || !f) return f;
	int maxf = 0,tf;
	for(int i = cur[u]; ~i && f;i = e[i].nxt) {
		int v = e[i].to;cur[u] = i;
		if(dep[v] != dep[u] + 1 || !e[i].cap) continue;
		tf = dfs(v,std::min(e[i].cap,f));
		maxf += tf,f -= tf;
		e[i].cap -= tf,e[i ^ 1].cap += tf;
	}
	if(!maxf) dep[u] = -1;
	return maxf;
}

int dinic() {
	int maxf = 0,x;
	while(bfs()) {
		while(x = dfs(s,INF))
			maxf += x;
	}
	return maxf;
}

int main() {
	init_IO();
	n = read(),m = read(),s = 0,t = n + m + 1;
	memset(head,-1,sizeof(int) * (n + m + 2));
	int p = read();
	rep(i,1,p) {
		int st = read(),ed = read();
		AddEdge(st,ed + n,1);
	}
	rep(i,1,n) AddEdge(s,i,1);
	rep(i,1,m) AddEdge(i + n,t,1);
	n += m + 1;
	write(dinic());
	end_IO();
	return 0;
}