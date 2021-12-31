/*
Luogu P3806 : Tree Divide and Conquer
Author : AstatinrAi
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
}
using IO::init_IO;
using IO::end_IO;
using IO::read;
using IO::putC;

int head[N],ecnt = -1;
struct Edge {
    int nxt,to,w;
}e[N << 1];
inline void AddEdge(int st,int ed,int w) {
    e[++ecnt] = (Edge) {head[st],ed,w},head[st] = ecnt;
    e[++ecnt] = (Edge) {head[ed],st,w},head[ed] = ecnt;
}

int n,m;
int q[105];
bool res[105],vis[N];
bool buc[10000005];

int dist[N],tmpd[N];
int siz[N],f[N];

int totsiz,rt,cnt;

#define Max(a,b) ((a) > (b) ? (a) : (b))
void calcsiz(int u,int _f) {
    siz[u] = 1,f[u] = 0;
    repg(i,u) {
        int v = e[i].to;
        if(v == _f || vis[v]) continue;
        calcsiz(v,u);
        f[u] = Max(f[u],siz[v]);
        siz[u] += siz[v];
    }
    f[u] = Max(f[u],totsiz - siz[u]);
    if(f[u] < f[rt]) rt = u;
}

void calcdist(int u,int _f) {
    tmpd[++cnt] = dist[u];
    repg(i,u) {
        int v = e[i].to;
        if(v == _f || vis[v]) continue;
        dist[v] = dist[u] + e[i].w;
        calcdist(v,u);
    }
}

std::queue<int> tag;

void solve(int u,int _f) {
    buc[0] = 1;
    tag.push(0);
    vis[u] = 1;
    repg(i,u) {
        int v = e[i].to;
        if(v == _f || vis[v]) continue;
        dist[v] = e[i].w;
        calcdist(v,u);
        rep(j,1,cnt) rep(k,1,m) if(q[k] >= tmpd[j])
            res[k] |= buc[q[k] - tmpd[j]];
        rep(j,1,cnt) if(tmpd[j] < 10000000)
            tag.push(tmpd[j]),buc[tmpd[j]] = 1;
        cnt = 0;
    }
    while(!tag.empty())
        buc[tag.front()] = 0,tag.pop();
    repg(i,u) {
        int v = e[i].to;
        if(v == _f || vis[v]) continue;
        totsiz = siz[v];
        rt = 0;
        f[rt] = INF;
        calcsiz(v,u);
        calcsiz(rt,rt);
        solve(rt,u);
    }
}

int main() {
	init_IO();
	mems(head,-1);
	n = read(),m = read();
	rep(i,1,n - 1) {
	    int st = read(),ed = read(),w = read();
	    AddEdge(st,ed,w);
	}
	rep(i,1,m) q[i] = read();
	rt = 0,f[rt] = INF;
	totsiz = n;
	calcsiz(1,1);
	calcsiz(rt,rt);
	solve(rt,rt);
	rep(i,1,m) if(res[i])
	    putC('A'),putC('Y'),putC('E'),enter;
	else
	    putC('N'),putC('A'),putC('Y'),enter;
	end_IO();
	return 0;
}