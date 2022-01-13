/*
Luogu P3690 : LCT
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

struct LinkCutTree {
	#define dir(x) (x == ch[fa[x]][1])
	#define IsRoot(x) (ch[fa[x]][0] != x && ch[fa[x]][1] != x)
	#define ls(x) ch[x][0]
	#define rs(x) ch[x][1]
	
	bool rev[N];
	int fa[N],ch[N][2];
	int val[N],xsum[N];
	
	inline void PushUp(int x) {
		//siz[x] = siz[ls(x)] + siz[rs(x)] + 1;
		xsum[x] = xsum[ls(x)] ^ xsum[rs(x)] ^ val[x];
	}
	
	inline void PushDown(int x) {
		if(rev[x]) {
			if(ls(x)) rev[ls(x)] ^= 1,std::swap(ls(ls(x)),rs(ls(x)));
			if(rs(x)) rev[rs(x)] ^= 1,std::swap(ls(rs(x)),rs(rs(x)));
			rev[x] = 0;
		}
	}
	
	inline void rotate(int x) {
		int y = fa[x],z = fa[y],d = dir(x),w = ch[x][d ^ 1];
		if(!IsRoot(y)) ch[z][dir(y)] = x;
		ch[y][d] = w,ch[x][d ^ 1] = y;
		fa[y] = x,fa[x] = z;
		if(w) fa[w] = y;
		PushUp(y);
	}
	
	void update(int x) {
		if(!IsRoot(x)) update(fa[x]);
		PushDown(x);
	}
	
	inline void splay(int x) {
		update(x);
		while(!IsRoot(x)) {
			int y = fa[x],z = fa[y];
			if(!IsRoot(y))
				rotate((ls(y) == x) ^ (ls(z) == y) ? x : y);
			rotate(x);
		}
		PushUp(x);
	}
	
	inline void access(int x) {
		for(int p = 0;x;p = x,x = fa[x])
			splay(x),rs(x) = p,PushUp(x);
	}
	
	inline void MakeRoot(int x) {
		access(x),splay(x);
		rev[x] ^= 1,std::swap(ls(x),rs(x));
	}
	
	inline int FindRoot(int x) {
		access(x),splay(x);
		while(ls(x)) PushDown(x),x = ls(x);
		splay(x);
		return x;
	}
	
	inline void link(int x,int y) {
		MakeRoot(x); if(FindRoot(y) != x) fa[x] = y;
	}
	
	inline void split(int x,int y) {
		MakeRoot(x),access(y),splay(y);
	}
	
	inline void cut(int x,int y) {
		MakeRoot(x);
		if(FindRoot(y) == x && fa[y] == x && !ls(y)) {
			fa[y] = rs(x) = 0;
			PushUp(x);
		}
	}
}T;

int main() {
	init_IO();
	int n = read(),m = read();
	rep(i,1,n) T.val[i] = read();
	while(m--) {
		int op = read(),x = read(),y = read();
		switch(op) {
			case 0 : {
				T.split(x,y);
				write(T.xsum[y]),enter;
				break;
			}
			case 1 : {
				T.link(x,y);
				break;
			}
			case 2 : {
				T.cut(x,y);
				break;
			}
			case 3 : {
				T.splay(x),T.val[x] = y;
				break;
			}
		}
	}
	end_IO();
	return 0;
}