/*
Luogu P4515 2D Fenwick Tree
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

constexpr int N = 2050;
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
	
	inline bool getStr(char *s) {
		int len = 0;char ch = getC();
		while(!isalpha(ch)) {
			ch = getC();
			if(ch == 0) return 0;
		}
		while(isalpha(ch)) {
			s[len++] = ch;
			ch = getC();
		}
		s[len] = '\0';
		return 1;
	}
}
using IO::init_IO;
using IO::end_IO;
using IO::read;
using IO::write;
using IO::getStr;
using IO::putC;

struct BIT {
	int n,m;
	ll T1[N][N];
	ll T2[N][N];
	ll T3[N][N];
	ll T4[N][N];
	
	#define lb(x) (x & (-x))
	
	inline int Q(int x,int y) {
		int s1 = 0,s2 = 0,s3 = 0,s4 = 0;
		for(int i = x;i;i -= lb(i))
			for(int j = y;j;j -= lb(j)) {
				s1 += T1[i][j],s2 += T2[i][j];
				s3 += T3[i][j],s4 += T4[i][j];
			}
		return s1 * (x * y + x + y + 1) - s2 * (y + 1) - s3 * (x + 1) + s4;
	}
	
	inline void M(int x,int y,int v) {
		for(int i = x;i <= n;i += lb(i))
			for(int j = y;j <= m;j += lb(j)) {
				T1[i][j] += v,T2[i][j] += x * v;
				T3[i][j] += y * v,T4[i][j] += x * y * v;
			}
	}
	
	inline void modify(int xa,int ya,int xb,int yb,int v) {
		M(xa,ya,v),M(xb + 1,ya,-v),M(xa,yb + 1,-v),M(xb + 1,yb + 1,v);
	}
	
	inline int query(int xa,int ya,int xb,int yb) {
		return Q(xb,yb) - Q(xa - 1,yb) - Q(xb,ya - 1) + Q(xa - 1,ya - 1);
	}
}T;

int main() {
	init_IO();
	char s[5];
	getStr(s);
	T.n = read(),T.m = read();
	while(getStr(s)) {
		if(s[0] == 'L') {
			int a = read(),b = read();
			int c = read(),d = read();
			int v = read();
			T.modify(a,b,c,d,v);
		}
		else {
			int a = read(),b = read();
			int c = read(),d = read();
			write(T.query(a,b,c,d)),enter;
		}
	}
	end_IO();
	return 0;
}