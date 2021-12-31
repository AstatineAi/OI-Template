/*
Luogu P5903 Level Ancestor
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
#include <vector>

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
	
	inline ll read() {
		ll res = 0;char ch = getC();
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
struct Edge {
    int nxt,to,w;
}e[N];
inline void AddEdge(int st,int ed) {
    e[++ecnt] = (Edge) {head[st],ed};
    head[st] = ecnt;
}

int dep[N];
int anc[N][20];
int hson[N],len[N],top[N];
std::vector<int> upp[N],low[N];
void dfs1(int u) {
    len[u] = dep[u] = dep[anc[u][0]] + 1;
    repg(i,u) {
        int v = e[i].to;
        anc[v][0] = u;
        for(int j = 0;anc[v][j];++j)
            anc[v][j + 1] = anc[anc[v][j]][j];
        dfs1(v);
        if(len[v] > len[u])
            len[u] = len[v],hson[u] = v;
    }   
}

void dfs2(int u,int t) {
    top[u] = t;
    if(u == t) {
        int p = u;
        rep(i,0,len[u] - dep[u])
            upp[u].push_back(p),p = anc[p][0];
        p = u;
        rep(i,0,len[u] - dep[u])
            low[u].push_back(p),p = hson[p];
    }
    if(hson[u]) dfs2(hson[u],t);
    repg(i,u) {
        int v = e[i].to;
        if(v == hson[u]) continue;
        dfs2(v,v);
    }
}

#define l2(x) (31 - __builtin_clz(x))
inline int query(int u,int k) {
    if(!k) return u;
    u = anc[u][l2(k)];
    k -= (1 << l2(k)),k -= dep[u] - dep[top[u]];
    u = top[u];
    return k >= 0 ? upp[u][k] : low[u][-k];
}

unsigned int s;

inline unsigned int get(unsigned int x) {
	x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;
	return s = x; 
}

int main() {
	init_IO();
	mems(head,-1);
	int n = read(),q = read();s = read();
	int rt = 0;
	rep(i,1,n) {
	    int _f = read();
	    if(!_f) rt = i;
	    else AddEdge(_f,i);
	}
	dfs1(rt);
	dfs2(rt,rt);
	ll ans = 0;
	ll lstans = 0;
	rep(i,1,q) {
	    int x = (get(s) ^ lstans) % n + 1;
	    int k = (get(s) ^ lstans) % dep[x];
	    lstans = query(x,k);
	    ans ^= ((ll)i * lstans);
	}
	write(ans),enter;
	end_IO();
	return 0;
}