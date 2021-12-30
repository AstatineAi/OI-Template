/*
Luogu P3809 Suffix Array
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
using IO::write;
using IO::getStr;
using IO::putC;

char s[N];
int sa[N],rk[N];
int mrk[N << 1];
int id[N],buc[N];
int rad[N];

inline bool cmp(int x,int y,int w) {
    return mrk[x] == mrk[y] && mrk[x + w] == mrk[y + w];
}

void build_SA(int n) {
    int m = 122;
    rep(i,1,n) ++buc[rk[i] = s[i]];
    rep(i,1,m) buc[i] += buc[i - 1];
    repb(i,n,1) sa[buc[rk[i]]--] = i;
    
    for(int w = 1,p;;w <<= 1,m = p) {
        p = 0;
        for(int i = n;i > n - w;--i)
            id[++p] = i;
        rep(i,1,n) if(sa[i] > w)
            id[++p] = sa[i] - w;
        mems(buc,0);
        rep(i,1,n) ++buc[rad[i] = rk[id[i]]];
        rep(i,1,m) buc[i] += buc[i - 1];
        repb(i,n,1) sa[buc[rad[i]]--] = id[i];
        memcpy(mrk,rk,sizeof(rk));
        p = 0;
        rep(i,1,n)
            rk[sa[i]] = cmp(sa[i],sa[i - 1],w) ? p : ++p;
        if(p == n) {
            rep(i,1,n) sa[rk[i]] = i;
            break;
        }
    }
}

int h[N];
inline void build_height(int n) {
    for(int i = 1,k = 0;i <= n;++i) {
        if(k) --k;
        while(s[i + k] == s[sa[rk[i] - 1] + k])
            ++k;
        h[rk[i]] = k;
    }
}

int main() {
	init_IO();
	int n = getStr(s + 1);
	build_SA(n);
	rep(i,1,n)
		write(sa[i]),space;
	end_IO();
	return 0;
}