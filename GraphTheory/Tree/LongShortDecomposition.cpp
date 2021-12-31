/*
POI2014 HOT-Hotels : LongShortDecomposition
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
    int nxt,to;
}e[N << 1];
inline void AddEdge(int st,int ed) {
    e[++ecnt] = (Edge) {head[st],ed},head[st] = ecnt;
    e[++ecnt] = (Edge) {head[ed],st},head[ed] = ecnt;
}

int n;
int len[N],son[N];
ll tmp[N << 2];
ll *f[N],*g[N],*id = tmp;
ll ans;

void dfs(int u,int _f){
	repg(i,u) {
	    int v = e[i].to;
		if (v != _f){
			dfs(v,u);
			if(len[v] > len[son[u]]) 
		        son[u] = v;
		}
	}
	len[u] = len[son[u]] + 1;
}

void dp(int u,int _f){
	if(son[u]) {
	    f[son[u]] = f[u] + 1;
	    g[son[u]] = g[u] - 1;
	    dp(son[u],u);
	}
	f[u][0] = 1;
	ans += g[u][0];
	repg(i,u) {
		int v = e[i].to;
		if(v == _f || v == son[u]) continue;
		f[v] = id;
		id += len[v] << 1;
		g[v] = id;
		id += len[v] << 1;
		dp(v,u);
		rep(j,0,len[v] - 1){
			if(j) ans += f[u][j - 1] * g[v][j];
			ans += g[u][j + 1] * f[v][j];
		}
		rep(j,0,len[v] - 1){
			g[u][j + 1] += f[u][j + 1] * f[v][j];
			if(j) g[u][j - 1] += g[v][j];
			f[u][j + 1] += f[v][j];
		}
	}
}

int main() {
    init_IO();
    mems(head,-1);
	n = read();
	rep(i,1,n - 1) AddEdge(read(),read());
	dfs(1,1);
	f[1] = id,id += len[1] << 1;
	g[1] = id,id += len[1] << 1;
	dp(1,0);
	write(ans),enter;
	end_IO();
	return 0;
}