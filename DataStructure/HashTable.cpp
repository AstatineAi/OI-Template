/*
Luogu P3370 Hash Table
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

constexpr int N = 10005;
constexpr int B = 133;
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

constexpr int M = 100007;
struct HashTable {
	int cnt;
	int head[M];
	struct Node {
		int nxt,val;
		ll key;
	}p[N];
	
	HashTable() : cnt(0) {}
	
	inline int HashHead(const ull x) {
		return x % M;
	}
	
	inline int& operator [] (const ll x) {
		int h = HashHead(x);
		for(int i = head[h];i;i = p[i].nxt)
			if(p[i].key == x) return p[i].val;
		p[++cnt] = (Node) {head[h],0,x},head[h] = cnt;
		return p[cnt].val;
	}
}mp;

char s[N];

int main() {
	init_IO();
	int T = read(),ans = 0;
	while(T--) {
		int n = getStr(s + 1);
		ll val = 0;
		rep(i,1,n)
			val = (val * B + s[i]) % MOD;
		if(++mp[val] == 1) ++ans;
	}
	write(ans),enter;
	end_IO();
	return 0;
}