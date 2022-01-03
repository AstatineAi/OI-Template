/*
Luogu P5960 : Difference Constraints
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
struct Edge {
    int nxt,to,w;
}e[N];
inline void AddEdge(int st,int ed,int w) {
    e[++ecnt] = (Edge) {head[st],ed,w};
    head[st] = ecnt;
}

int n;
int dis[N];
int cnt[N];
bool inq[N];
bool SPFA() {
    mems(dis,63),dis[0] = 0;
    std::queue<int> q;q.push(0);
    while(!q.empty()) {
        int u = q.front();q.pop();
        inq[u] = 0;
        repg(i,u) {
            int v = e[i].to;
            if(dis[v] > dis[u] + e[i].w) {
                dis[v] = dis[u] + e[i].w;
                if(!inq[v]) {
                    inq[v] = 1;
                    q.push(v);
                    if(++cnt[v] == n + 1)
                        return 0;
                }
            }
        }
    }
    return 1;
}

int main() {
	init_IO();
	mems(head,-1);
	n = read();int m = read();
	rep(i,1,m) {
	    int st = read(),ed = read(),w = read();
	    AddEdge(ed,st,w);
	}
	rep(i,1,n) AddEdge(0,i,0);
	if(SPFA())
	    rep(i,1,n) write(dis[i]),space;
	else putC('N'),putC('O'),enter;
	end_IO();
	return 0;
}