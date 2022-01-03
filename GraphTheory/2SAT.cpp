/*
Luogu P4782 2-SAT
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

constexpr int N = 1000005;
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
	
	inline void putStr(const char *s) {
	    int len = strlen(s);
	    rep(i,0,len - 1)
	        putC(s[i]);
	    enter;
	}
}
using IO::init_IO;
using IO::end_IO;
using IO::read;
using IO::putStr;
using IO::putC;

int head[N << 1],ecnt = -1;
struct Edge {
    int nxt,to;
}e[N << 1];
inline void AddEdge(int st,int ed) {
    e[++ecnt] = (Edge) {head[st],ed};
    head[st] = ecnt;
}

#define id(x,y) (x + n * ((y) & 1))
int dfs_clock,top,cnt;
int dfn[N << 1],low[N << 1];
int scc[N << 1],stk[N << 1];

void tarjan(int u) {
    dfn[u] = low[u] = ++dfs_clock;
    stk[++top] = u;
    repg(i,u) {
        int v = e[i].to;
        if(!dfn[v]) {
            tarjan(v);
            low[u] = std::min(low[u],low[v]);
        }
        else if(!scc[v])
            low[u] = std::min(low[u],dfn[v]);
    }
    if(dfn[u] == low[u]) {
        scc[u] = ++cnt;
        while(stk[top] != u)
            scc[stk[top--]] = cnt;
        --top;
    }
}

int main() {
	init_IO();
	mems(head,-1);
	int n = read(),m = read();
	rep(i,1,m) {
	    int u = read(),p1 = read();
	    int v = read(),p2 = read();
	    AddEdge(id(u,!p1),id(v,p2));
	    AddEdge(id(v,!p2),id(u,p1));
	}
	rep(i,1,(n << 1)) if(!dfn[i])
	    tarjan(i);
	bool res = 1;
	rep(i,1,n) if(scc[i] == scc[i + n]) {
	    res = 0;
	    break;
	}
	if(!res) putStr("IMPOSSIBLE");
	else {
	    putStr("POSSIBLE");
	    rep(i,1,n) {
	        if(scc[i] > scc[i + n])
	            putC('1');
	        else 
	            putC('0');
	        space;
	    }
	}
	end_IO();
	return 0;
}