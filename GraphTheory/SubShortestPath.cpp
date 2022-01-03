/*
[USACO06NOV] Roadblocks G P : Strictly Sub-shortest Path
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

constexpr int N = 5005;
constexpr int M = 100005;
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

int head[N],ecnt = -1;
struct Edge {
	int nxt,to,w;
}e[M << 1];
inline void AddEdge(int st,int ed,int w) {
	e[++ecnt] = (Edge) {head[st],ed,w},head[st] = ecnt;
	e[++ecnt] = (Edge) {head[ed],st,w},head[ed] = ecnt;
}

int dis1[N],dis2[N];
void dijkstra(int s) {
	std::priority_queue<pii,std::vector<pii>,std::greater<pii> > q;
	mems(dis1,63),mems(dis2,63),dis1[s] = 0,q.push(std::make_pair(0,s));
	while(!q.empty()) {
		int u = q.top().second;q.pop();
		repg(i,u) {
            int v = e[i].to,w = e[i].w;
            bool flag = 0;
            if(dis1[u] + w < dis1[v])
                dis1[v] = dis1[u] + w,flag = 1;
            if(dis1[u] + w > dis1[v] && dis1[u] + w < dis2[v])
                dis2[v] = dis1[u] + w,flag = 1;
            if(dis2[u] + w < dis2[v])
                dis2[v] = dis2[u] + w,flag = 1;
            if(flag) q.push(std::make_pair(dis1[v],v));
        }
	}
}

int main() {
	init_IO();
	mems(head,-1);
	int n = read(),m = read();
	rep(i,1,m) {
		int st = read(),ed = read(),w = read();
		AddEdge(st,ed,w);
	}
	dijkstra(1);
	write(dis2[n]),enter;
	end_IO();
	return 0;
}