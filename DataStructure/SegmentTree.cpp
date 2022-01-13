/*
Luogu P3372 Segement Tree
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

struct SegmentTree {
	ll T[N << 2];
	ll laz[N << 2];
	
	inline void PushDown(int p,int len) {
		T[p << 1] += laz[p] * (len - (len >> 1)),laz[p << 1] += laz[p];
		T[p << 1 | 1] += laz[p] * (len >> 1),laz[p << 1 | 1] += laz[p];
		laz[p] = 0;
	}
	
	void build(int p,int l,int r,int *val) {
		if(l == r) {
			T[p] = val[l];
			return ;
		}
		int mid = (l + r) >> 1;
		build(p << 1,l,mid,val);
		build(p << 1 | 1,mid + 1,r,val);
		T[p] = T[p << 1] + T[p << 1 | 1];
	}
	
	void modify(int p,int pl,int pr,int l,int r,int v) {
		if(l <= pl && pr <= r) {
			T[p] += v * (pr - pl + 1);
			laz[p] += v;
			return;
		}
		int mid = (pl + pr) >> 1;
		if(laz[p]) PushDown(p,pr - pl + 1);
		if(l <= mid) modify(p << 1,pl,mid,l,r,v);
		if(mid < r) modify(p << 1 | 1,mid + 1,pr,l,r,v);
		T[p] = T[p << 1] + T[p << 1 | 1];
	}
	
	ll query(int p,int pl,int pr,int l,int r) {
		if(l <= pl && pr <= r) return T[p];
		int mid = (pl + pr) >> 1;ll res = 0;
		if(laz[p]) PushDown(p,pr - pl + 1);
		if(l <= mid) res += query(p << 1,pl,mid,l,r);
		if(mid < r) res += query(p << 1 | 1,mid + 1,pr,l,r);
		return res;
	}
}T;

int a[N];

int main() {
	init_IO();
	int n = read(),m = read();
	rep(i,1,n) a[i] = read();
	T.build(1,1,n,a);
	while(m--) {
		int op = read(),x = read(),y = read();
		if(op & 1) T.modify(1,1,n,x,y,read());
		else write(T.query(1,1,n,x,y)),enter;
	}
	end_IO();
	return 0;
}