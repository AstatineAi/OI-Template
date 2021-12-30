/*
Luogu P3375 KMP
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
	}
	
	inline void putC(char ch) {
		if(_o == obuf + IOLIM) {
			fwrite(obuf,_o - obuf,sizeof(char),OS);
			_o = obuf;
		}
		*_o++ = ch;
	}
	
	inline void write(int x) {
		static int sta[20];int top = 0;
		do
			sta[top++] = x % 10,x /= 10;
		while(x);
		while(top) putC(sta[--top] + '0');
	}
	
	inline int getStr(char *s) {
	    char ch = getC();int len = 0;
	    while(!isalpha(ch)) ch = getC();
	    while(isalpha(ch)) {
	        s[len++] = ch;
	        ch = getC();
	    }
	    s[len] = '\0';
	    return len;
	}
}
using IO::init_IO;
using IO::end_IO;
using IO::write;
using IO::getStr;
using IO::putC;

char s[N];
char t[N];
int nxt[N];

void prefixfunc(int *pi,char *s,int len) {
	pi[0] = pi[1] = 0;
	int j = 0;
	rep(i,2,len) {
		while(j && s[i] != s[j + 1]) j = pi[j];
		pi[i] = s[i] == s[j + 1] ? ++j : j;
	}
}

void KMP(char *s,char *t,int lens,int lent) {
	prefixfunc(nxt,s,lens);
	int j = 0;
	rep(i,1,lent) {
		while(j && t[i] != s[j + 1]) j = nxt[j];
		j += (t[i] == s[j + 1]);
        if(j == lens) 
        	write(i - lens + 1),enter;
	}
}

int main() {
	init_IO();
	int lent = getStr(t + 1);
	int lens = getStr(s + 1);
	KMP(s,t,lens,lent);
	rep(i,1,lens)
		write(nxt[i]),space;
	end_IO();
	return 0;
}