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
constexpr int MOD = 998244353;

namespace IO {
	#define IS stdin
	#define OS stdout
	FILE *is,*os;
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
	
	inline ll read() {
		ll res = 0;char ch = getC();bool m = 1;
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
	
	inline db read_db() {
        db res = 0,m = 1;char ch = getC();
        while(!isdigit(ch)) {
            if(ch == '-') m = -1;
            ch = getC();
        }
        while(isdigit(ch)) {
            res = (res * 10) + (ch ^ 48);
            ch = getC();
        }
        if(ch == '.') {
            double frac = 1;
            ch = getC();
            while(isdigit(ch)) {
                frac /= 10;
                res += (ch - 48) * frac;
                ch = getC();
            }
        }
        return m * res;
    }
	
	inline void write_db(db x,int p = 6) {
        db fac = 1.0;int len = 0,tmp = p;
        if(x < 0.0) putC('-'),x = -x;
        while(tmp--) fac /= 10.0;
        x += 0.5 * fac;
        while (x >= 1.0)
            x /= 10.0,++len;
        if(len == 0) putC('0');
        while (len--) {
            x *= 10.0;
            putC((int)x + '0');
            x -= (int)x;
        }
        putC('.');
        while (p--) {
            x *= 10.0;
            putC((int)x + '0');
            x -= (int)x;
        }
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
using IO::write;
using IO::read_db;
using IO::write_db;
using IO::getStr;
using IO::putStr;
using IO::putC;

int main() {
	init_IO();
	
	end_IO();
	return 0;
}
