/*
Luogu P3377 Leftist Tree
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
#define repl(a,b,c) for(int a = (b);a < (c);++a)
#define repr(a,b,c) for(int a = (b);a > (c);--a)
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

int dsu[N];

int find(int x) {
	return dsu[x] == x ? x : dsu[x] = find(dsu[x]);
}

struct Node {
	int val,ch[2],dist;
}T[N];

int merge(int x,int y) {
	if(!x || !y) return x | y;
	if(T[x].val > T[y].val) std::swap(x,y);
	T[x].ch[1] = merge(T[x].ch[1],y);
	if(T[T[x].ch[1]].dist > T[T[x].ch[0]].dist)
		std::swap(T[x].ch[0],T[x].ch[1]);
	T[x].dist = T[T[x].ch[1]].dist + 1;
	return x;
}

bool vis[N];

int main() {
	init_IO();
	int n = read(),m = read();
	rep(i,1,n) {
		T[i].val = read();
		dsu[i] = i;
	}
	while(m--) {
		int op = read(),x = read();
		if(op & 1) {
			int y = read();
			int fx = find(x),fy = find(y);
			if(fx == fy || vis[x] || vis[y])
				continue;
			dsu[fx] = dsu[fy] = merge(fx,fy);
		}
		else {
			if(vis[x]) {
				putC('-'),putC('1');
				enter;
				continue;
			}
			int fx = find(x);vis[fx] = 1;
			write(T[fx].val),enter;
			dsu[fx] =
			dsu[T[fx].ch[0]] =
			dsu[T[fx].ch[1]] =
			merge(T[fx].ch[0],T[fx].ch[1]);
		}
	}
	end_IO();
	return 0;
}