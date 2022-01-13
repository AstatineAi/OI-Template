/*
Luogu P3369 splay
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
constexpr int INF = 2e9;
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

struct Splay {
	int tot,rt;
	int fa[N],ch[N][2];
	int cnt[N],siz[N];
	int val[N];
	
	#define ls(x) (ch[x][0])
	#define rs(x) (ch[x][1])
	#define dir(x) (x == ch[fa[x]][1])
	
	inline void PushUp(int x) {
		siz[x] = siz[ls(x)] + siz[rs(x)] + cnt[x];
	}
	
	inline void rotate(int x) {
		int y = fa[x],z = fa[y],d = dir(x),w = ch[x][d ^ 1];
		ch[y][d] = w,fa[w] = y;
		ch[z][dir(y)] = x,fa[x] = z;
		ch[x][d ^ 1] = y,fa[y] = x;
		PushUp(y),PushUp(x);
	}
	
	inline void splay(int x,int goal = 0) {
		while(fa[x] != goal) {
			int y = fa[x];
			if(fa[y] != goal)
				rotate(dir(x) == dir(y) ? y : x);
			rotate(x);
		}
		if(!goal) rt = x;
	}
	
	inline void find(int x) {
		int cur = rt;
		while(ch[cur][x > val[cur]] && val[cur] ^ x)
			cur = ch[cur][x > val[cur]];
		splay(cur);
	}
	
	inline void ins(int x) {
		int cur = rt,p = 0;
		while(cur && val[cur] ^ x) {
			p = cur;
			cur = ch[cur][x > val[cur]];
		}
		if(cur) ++cnt[cur];
		else {
			cur = ++tot;
			if(p) ch[p][x > val[p]] = cur;
			val[cur] = x,fa[cur] = p;
			siz[cur] = cnt[cur] = 1;
		}
		splay(cur);
	}
	
	inline int pre(int x) {
		find(x);
		if(val[rt] < x) return rt;
		int cur = ls(rt);
		while(rs(cur))
			cur = rs(cur);
		splay(cur);
		return cur;
	}
	
	inline int suc(int x) {
		find(x);
		if(val[rt] > x) return rt;
		int cur = rs(rt);
		while(ls(cur))
			cur = ls(cur);
		splay(cur);
		return cur;
	}
	
	inline void del(int x) {
		int l = pre(x),r = suc(x);
		splay(l),splay(r,l);
		int d = ls(r);
		if(cnt[d] > 1) --cnt[d],splay(d);
		else ls(r) = 0;
		PushUp(r),PushUp(rt);
	}
	
	inline int rnk(int x) {
		find(x);
		if(val[rt] < x) return siz[ls(rt)] + cnt[rt];
		return siz[ls(rt)];
	}
	
	inline int kth(int x) {
		int cur = rt;
		while(1) {
			if(x <= siz[ls(cur)] && ls(cur))
				cur = ls(cur);
			else {
				if(x > siz[ls(cur)] + cnt[cur]) {
					x -= siz[ls(cur)] + cnt[cur];
					cur = rs(cur);
				}
				else {
					splay(cur);
					return val[cur];
				}
			}
		}
	}
}T;

int main() {
	init_IO();
	int m = read();
	T.ins(-INF),T.ins(INF);
	while(m--) {
		int op = read(),x = read();
		switch(op) {
			case 1 : T.ins(x);break;
			case 2 : T.del(x);break;
			case 3 : write(T.rnk(x)),enter;break;
			case 4 : write(T.kth(x + 1)),enter;break;
			case 5 : write(T.val[T.pre(x)]),enter;break;
			case 6 : write(T.val[T.suc(x)]),enter;break;
		}
	}
	end_IO();
	return 0;
}