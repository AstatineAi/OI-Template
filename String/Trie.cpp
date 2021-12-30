/*
Luogu P2580 于是他错误的点名开始了
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
	
	inline int read() {
		int res = 0;char ch = getC();
		while(!isdigit(ch)) ch = getC();
		while(isdigit(ch)) {
			res = res * 10 + (ch ^ 48);
			ch = getC();
		}
		return res;
	}
	
	inline void getStr(char *s) {
	    char ch = getC();int len = 0;
	    while(!isalpha(ch)) ch = getC();
	    while(isalpha(ch)) {
	        s[len++] = ch;
	        ch = getC();
	    }
	    s[len] = '\0';
	}
	
	inline void putStr(const char *s) {
	    int len = strlen(s);
	    rep(i,0,len - 1)
	        putC(s[i]);
	    enter;
	}
}
using IO::init_IO;
using IO::end_IO;
using IO::read;
using IO::getStr;
using IO::putStr;
using IO::putC;

class Trie {
	// vars
	public : 
	
	private : 
		int tot;
		int ty[N];
		int tr[N][26];
	
	// funcs
	public : 
	
		Trie() : tot(1) {}
	
		inline void insert(char *s) {
			int p = 1;
			for(int i = 0;s[i];++i) {
				if(!tr[p][s[i] - 'a'])
					tr[p][s[i] - 'a'] = ++tot;
				p = tr[p][s[i] - 'a'];
			}
			ty[p] = 1;
		}
		
		inline int query(char *s) {
			int p = 1;
			for(int i = 0;s[i];++i) {
				if(!tr[p][s[i] - 'a'])
					return 2;
				p = tr[p][s[i] - 'a'];
			}
			if(ty[p] == 1) {
				ty[p] = 2;
				return 1;
			}
			else return 3;
		}
		
	private : 
	
}T;

char s[55];

int main() {
	init_IO();
	int n = read();
	rep(i,1,n) {
		getStr(s);
		T.insert(s);
	}
	int m = read();
	rep(i,1,m) {
		getStr(s);
		int r = T.query(s);
		switch(r) {
			case 1 : putStr("OK");break;
			case 2 : putStr("WRONG");break;
			case 3 : putStr("REPEAT");break;
		}
	}
	end_IO();
	return 0;
}