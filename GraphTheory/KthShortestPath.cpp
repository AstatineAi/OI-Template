/*
Kth Shortest Path Normal ver
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

constexpr int N = 100005;
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

typedef struct {
	int nxt,to,w;
} Edge;

namespace Pre {
	int head[N],ecnt = -1;
	struct Edge {
		int nxt,to,w;
	}e[N];
	inline void AddEdge(int st,int ed,int w) {
		e[++ecnt] = (Edge) {head[st],ed,w};
		head[st] = ecnt;
	}
	
	bool vis[N];
	int dis[N];
	void dijkstra(int s) {
		mems(dis,63),dis[s] = 0;
		std::priority_queue<pii,std::vector<pii>,std::greater<pii> > q;
		q.push(std::make_pair(0,s));
		while(!q.empty()) {
			int u = q.top().second;q.pop();
			if(vis[u]) continue;
			vis[u] = 1;
			repg(i,u) {
				int v = e[i].to,w = e[i].w;
				if(dis[v] > dis[u] + w) {
					dis[v] = dis[u] + w;
					q.push(std::make_pair(dis[v],v));
				}
			}
		}
	}
}

#define h(x) Pre::dis[x]
namespace Kth {
	int head[N],ecnt = -1;
	struct Edge {
		int nxt,to,w;
	}e[N];
	inline void AddEdge(int st,int ed,int w) {
		e[++ecnt] = (Edge) {head[st],ed,w};
		head[st] = ecnt;
	}
	
	struct Node {
		int u,dis;
		inline bool operator < (const Node &oth) const {
			return (dis + h(u)) > (oth.dis + h(oth.u));
		}
	};
	
	int Astar(int s,int t,int k) {
		std::priority_queue<Node> q;
		q.push((Node){s,0});int cnt = 0;
		while(!q.empty()) {
			Node p = q.top();q.pop();
			if(p.u == t) {
				++cnt;
				if(cnt == k)
					return p.dis;
			}
			repg(i,p.u)
				q.push((Node){e[i].to,p.dis + e[i].w});
		}
		return -1;
	}
}

int main() {
	init_IO();
	int n = read(),m = read(),k = read(),s = read(),t = read();
	rep(i,1,m) {
		int st = read(),ed = read(),w = read();
		Pre::AddEdge(ed,st,w);
		Kth::AddEdge(st,ed,w);
	}
	Pre::dijkstra(s);
	write(Kth::Astar(s,t,k)),enter;
	end_IO();
	return 0;
}