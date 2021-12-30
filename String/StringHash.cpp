/*
Luogu P3370 字符串哈希
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
constexpr int B = 133;
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
	
	inline void write(ll x) {
		static int sta[20];int top = 0;
		do
			sta[top++] = x % 10,x /= 10;
		while(x);
		while(top) putC(sta[--top] + '0');
	}

	inline int getStr(char *s) {
	    char ch = getC();int len = 0;
	    while(!isalnum(ch)) ch = getC();
	    while(isalnum(ch)) {
	        s[len++] = ch;
	        ch = getC();
	    }
	    s[len] = '\0';
	    return len;
	}
}
using IO::init_IO;
using IO::end_IO;
using IO::read;
using IO::write;
using IO::getStr;
using IO::putC;

ll base[N],H[N];
inline void InitHash(char *s,int n) {
	base[0] = 1;
	rep(i,1,n) base[i] = base[i - 1] * B % MOD;
	rep(i,1,n) H[i] = (H[i - 1] * B % MOD + s[i]) % MOD;
}

inline int GetHash(int l,int r) {
	return (H[r] - H[l - 1] * base[r - l + 1] % MOD + MOD) % MOD;
}

inline int HashStr(char *s,int n) {
	ll res = 0;
	rep(i,1,n)
		res = (res * B % MOD + s[i]) % MOD;
	return res;
}

int res[N];
char s[N];

int main() {
	init_IO();
	int n = read();
	rep(i,1,n) {
		int l = getStr(s + 1);
		res[i] = HashStr(s,l);
	}
	std::sort(res + 1,res + n + 1);
	int siz = std::unique(res + 1,res + n + 1) - res - 1;
	write(siz),enter;
	end_IO();
	return 0;
}