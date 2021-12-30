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
using IO::putStr;
using IO::putC;

#define repl(a,X,b) for(int a = X[b];a != b;a = X[a])

int cnt;
int ans[N];
class DLX {
    // vars
    private : 
        int n,m,tot;
        int L[N],R[N],U[N],D[N];
        int head[N],siz[N];
        int col[N],row[N];
    
    // funcs
    private : 
        void remove(const int &c) {
            L[R[c]] = L[c],R[L[c]] = R[c];
            repl(i,D,c) repl(j,R,i)
                U[D[j]] = U[j],D[U[j]] = D[j],--siz[col[j]];
        }
        
        void recover(const int &c) {
            repl(i,U,c) repl(j,L,i)
                U[D[j]] = D[U[j]] = j,++siz[col[j]];
            L[R[c]] = R[L[c]] = c;
        }
    
    public : 
        void build(const int &r,const int &c) {
            n = r,m = c;
            rep(i,0,m) {
                L[i] = i -  1,R[i] = i + 1;
                U[i] = D[i] = i;
            }
            L[0] = m,R[m] = 0,tot = m;
        }
        
        void insert(const int &r,const int &c) {
            col[++tot] = c,row[tot] = r,++siz[c];
            U[tot] = c,D[tot] = D[c],U[D[c]] = tot,D[c] = tot;
            if(!head[r])
                head[r] = L[tot] = R[tot] = tot;
            else {
                L[tot] = head[r],R[tot] = R[head[r]];
                L[R[head[r]]] = tot,R[head[r]] = tot;
            }
        }
        
        bool dance(int dep) {
            int c = R[0];
            if(!R[0]) {
                cnt = dep - 1;
                return 1;
            }
            repl(i,R,0) if(siz[i] < siz[c])
                c = i;
            remove(c);
            repl(i,D,c) {
                ans[dep] = row[i];
                repl(j,R,i) remove(col[j]);
                if(dance(dep + 1)) return 1;
                repl(j,L,i) recover(col[j]);
            }
            recover(c);
            return 0;
        }
}solver;

int main() {
	init_IO();
	int n = read(),m = read();
	solver.build(n,m);
	rep(i,1,n) rep(j,1,m) {
	    int p = read();
	    if(p) solver.insert(i,j);
	}
	if(solver.dance(1))
	    rep(i,1,cnt) write(ans[i]),space;
	else putStr("No Solution!");
	end_IO();
	return 0;
}