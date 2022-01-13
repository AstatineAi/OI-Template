/*
Luogu P3373 Binary Indexed Tree
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
	// #define IS is
	// #define OS os
	FILE *is,*os;
	constexpr int IOLIM = 10000;
	char ibuf[IOLIM],obuf[IOLIM];
	char *_i = ibuf,*_o = obuf;
	inline void init_IO() {
		#ifndef DEBUG
		is = fopen(".in","r");
		os = fopen(".out","w");
		#endif
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

struct BinaryIndexedTree {
	int n;
	ll T1[N];
	ll T2[N];
	
	#define lb(x) (x & (-x))
	
	inline void build(int *val,int len) {
		n = len;
		rep(i,1,n) {
			ll vt = val[i] - val[i - 1];
			T1[i] += vt;
			T2[i] += vt * i;
			if(i + lb(i) <= n) {
				T1[i + lb(i)] += T1[i];
				T2[i + lb(i)] += T2[i];
			}
		}
	}
	
	inline void M(int p,ll v) {
		ll vt = v * p;
		for(;p <= n;p += lb(p))
			T1[p] += v,T2[p] += vt;
	}
	
	inline ll Q(ll *T,int p) {
		ll res = 0;
		for(;p;p -= lb(p))
			res += T[p];
		return res;
	}
	
	inline void modify(int l,int r,ll v) {
		M(r + 1,-v),M(l,v);
	}
	
	inline ll query(int l,int r) {
		return Q(T1,r) * (r + 1ll) - Q(T2,r) - Q(T1,l - 1) * l + Q(T2,l - 1);
	}
}T;

int a[N];

int main() {
	init_IO();
	int n = read(),m = read();
	rep(i,1,n) a[i] = read();
	T.build(a,n);
	while(m--) {
		int op = read(),x = read(),y = read();
		if(op & 1) T.modify(x,y,read());
		else write(T.query(x,y)),enter;
	}
	end_IO();
	return 0;
}