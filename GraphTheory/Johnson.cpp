/*
Luogu P All Pairs Shortest Paths : Johnson
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
#include <vector>
#include <functional>

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

constexpr int N = 3005;
constexpr int M = 10005;
constexpr int INF = 0x3f3f3f3f;
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
	int nxt,to,w;
}e[M];
inline void AddEdge(int st,int ed,int w) {
	e[++ecnt] = (Edge) {head[st],ed,w};
	head[st] = ecnt;
}

int n;

bool vis[N];
int h[N],cnt[N];
bool SPFA(int s) {
	mems(h,63),h[s] = 0;
	std::queue<int> q;q.push(s);
	while(!q.empty()) {
		int u = q.front();q.pop();
		vis[u] = 0;
		repg(i,u) {
			int v = e[i].to;
			if(h[v] > h[u] + e[i].w) {
				h[v] = h[u] +e[i].w;
				if(!vis[v]) {
					q.push(v),vis[v] = 1;
					if(++cnt[v] == n + 1)
						return 0;
				}
			}
		}
	}
	return 1;
}

int dis[N][N];
void Dijkstra(int s) {
	mems(vis,0);
	mems(dis[s],63),dis[s][s] = 0;
	std::priority_queue<pii,std::vector<pii>,std::greater<pii> > q;
	q.push(std::make_pair(0,s));
	while(!q.empty()) {
		int u = q.top().second;q.pop();
		if(vis[u]) continue;
		vis[u] = 1;
		repg(i,u) {
			int v = e[i].to;
			if(dis[s][v] > dis[s][u] + e[i].w) {
				dis[s][v] = dis[s][u] + e[i].w;
				q.push(std::make_pair(dis[s][v],v));
			}
		}
	}
}

int main() {
	init_IO();
	mems(head,-1);
	n = read();int m = read();
	rep(i,1,m) {
		int st = read(),ed = read(),w = read();
		AddEdge(st,ed,w);
	}
	rep(i,1,n) AddEdge(0,i,0);
	if(!SPFA(0)) {
		putC('-'),putC('1'),enter;
		end_IO();
		return 0;
	}
	
	rep(i,1,n) repg(j,i)
		e[j].w += h[i] - h[e[j].to];
	
	rep(i,1,n) Dijkstra(i);
	
	rep(i,1,n) {
		ll ans = 0;
		rep(j,1,n) {
			if (dis[i][j] == INF)
				ans += 1ll * (int)(1e9) * j;
			else
				ans += 1ll * (dis[i][j] - h[i] + h[j]) * j;
		}
		write(ans),enter;
	}
	end_IO();
	return 0;
}