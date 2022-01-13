/*
Luogu P3834 Dividing Tree
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

constexpr int N = 200005;
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
}
using IO::init_IO;
using IO::end_IO;
using IO::read;
using IO::write;
using IO::putC;

int rnk[N];

struct DividingTree {
    int T[20][N];
    int siz[20][N];
    
    void build(int d,int l,int r) {
        if(l == r) return ;
        int mid = (l + r) >> 1,div = mid - l + 1;
        rep(i,l,r) if(T[d][i] < rnk[mid]) --div;
        int pl = l,pr = mid + 1;
        rep(i,l,r) {
            if(i == l) siz[d][i] = 0;
            else siz[d][i] = siz[d][i - 1];
            if(T[d][i] < rnk[mid] || (T[d][i] == rnk[mid] && div > 0)) {
                T[d + 1][pl++] = T[d][i];
                ++siz[d][i];
                if(T[d][i] == rnk[mid]) --div;
            }
            else T[d + 1][pr++] = T[d][i];
        }
        build(d + 1,l,mid),build(d + 1,mid + 1,r);
    }
    
    int query(int d,int pl,int pr,int l,int r,int k) {
        if(pl == pr) return T[d][pl];
        int mid = (pl + pr) >> 1,nl;
        if(l == pl) nl = 0;
        else nl = siz[d][l - 1];
        int tolef = siz[d][r] - nl;
        if(tolef >= k) return query(d + 1,pl,mid,pl + nl,pl + siz[d][r] - 1,k);
        else {
            int nr = mid + 1 + (l - pl - nl);
            return query(d + 1,mid + 1,pr,nr,nr + r - l + 1 - tolef - 1, k - tolef);
        }
    }
}T;

int main() {
	init_IO();
	int n = read(),m = read();
	rep(i,1,n)
	    rnk[i] = T.T[0][i] = read();
	std::sort(rnk + 1,rnk + n + 1);
	T.build(0,1,n);
	while(m--) {
	    int l = read(),r = read(),k = read();
	    write(T.query(0,1,n,l,r,k)),enter;
	}
	end_IO();
	return 0;
}