/*
Luogu P3366 : Minimum Spanning Tree
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

constexpr int N = 5005;
constexpr int M = 200005;
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

struct MST {
    int st,ed,w;
}e[M],b[M];

unsigned int buc[256];

#define SORTBYTE(TYPE,FR,TO,LEN,BIT) {\
    memset(buc,0,sizeof(buc));\
    for (TYPE *it = (FR) + LEN; it != (FR); it--)\
        ++buc[(it[-1].w >> BIT) & 255];\
    for (unsigned int *it = buc; it != buc + 255; it++)\
        it[1] += it[0];\
    for (TYPE *it = (FR) + LEN; it != (FR); it--)\
        (TO)[--buc[(it[-1].w >> BIT) & 255]] = it[-1];\
}

inline void Radix_sort(int m) {
    SORTBYTE(MST,e + 1,b + 1,m,0);
    SORTBYTE(MST,b + 1,e + 1,m,8);
    SORTBYTE(MST,e + 1,b + 1,m,16);
    SORTBYTE(MST,b + 1,e + 1,m,24);
}

int fa[N];
int find(int x) {
    return (~fa[x]) ? fa[x] = find(fa[x]) : x;
}

void Kruskal(int n,int m) {
    Radix_sort(m);
    int cnt = 0;bool flag = 0;
    int ans = 0;
    rep(i,1,m) {
        int fx = find(e[i].st);
        int fy = find(e[i].ed);
        if(fx == fy) continue;
        fa[fx] = fy,ans += e[i].w;
        if(++cnt == n - 1) {
			flag = 1;
            break;
        }
    }
    if(!flag) putC('o'),putC('r'),putC('z');
    else write(ans);
    enter;
}

int main() {
	init_IO();
	int n = read(),m = read();
	mems(fa,-1);
	rep(i,1,m)
	    e[i].st = read(),e[i].ed = read(),e[i].w = read();
	Kruskal(n,m);
	end_IO();
	return 0;
}