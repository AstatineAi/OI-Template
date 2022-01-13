/*
Luogu P3856 Cat Tree
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

#define l2(x) (31 - __builtin_clz(x))

struct CatTree {
    int mx[20][N << 1];
    int pos[N << 1];
    
    void build(int p,int pl,int pr,int d,int *val) {
        if(pl == pr) {
            pos[pr] = p;
            return ;
        }
        int mid = (pl + pr) >> 1;
        build(p << 1,pl,mid,d + 1,val);
        build(p << 1 | 1,mid + 1,pr,d + 1,val);
        mx[d][mid] = val[mid];
        repb(i,mid - 1,pl)
            mx[d][i] = std::max(mx[d][i + 1],val[i]);
        mx[d][mid + 1] = val[mid + 1];
        rep(i,mid + 2,pr)
            mx[d][i] = std::max(mx[d][i - 1],val[i]);
    }
    
    inline int query(int l,int r) {
        int k = l2(pos[r]) - l2(pos[l] ^ pos[r]) - 1;
        return std::max(mx[k][l],mx[k][r]);
    }
}T;

int val[N];

int main() {
	init_IO();
	int n = read(),m = read();
	rep(i,1,n) val[i] = read();
	int k = l2(n);
	if((1 << k) < n) ++k;
	T.build(1,1,(1 << k),0,val);
    while(m--) {
        int l = read(),r = read();
        if(l == r) write(val[l]);
        else write(T.query(l,r));
        enter;
    }
	end_IO();
	return 0;
}