/*
Luogu P2324 骑士精神
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
    
	inline void getStr(char *s) {
	    char ch = getC();int len = 0;
	    while(!isdigit(ch) && ch != '*')
	        ch = getC();
	    while(isdigit(ch) || ch == '*') {
	        s[len++] = ch;
	        ch = getC();
	    }
	    s[len] = '\0';
	}
}
using IO::init_IO;
using IO::end_IO;
using IO::read;
using IO::write;
using IO::getStr;
using IO::putC;

bool flag = 0;

constexpr int movx[]={0,1,1,-1,-1,2,2,-2,-2};
constexpr int movy[]={0,2,-2,2,-2,1,-1,1,-1};

constexpr int dpos[7][7] = {
	{0,0,0,0,0,0,0},
	{0,1,1,1,1,1,0},
	{0,2,1,1,1,1,0},
	{0,2,2,0,1,1,0},
	{0,2,2,2,2,1,0},
	{0,2,2,2,2,2,0},
	{0,0,0,0,0,0,0}
};

int mp[10][10];
char s[10];

inline bool mov(int x,int y) {
	if(x < 1 || x > 5) return 0;
	if(y < 1 || y > 5) return 0;
	return 1;
}

inline int h() {
	int cnt = 0;
    cnt += (mp[1][1] != dpos[1][1]);
    cnt += (mp[1][2] != dpos[1][2]);
    cnt += (mp[1][3] != dpos[1][3]);
    cnt += (mp[1][4] != dpos[1][4]);
    cnt += (mp[1][5] != dpos[1][5]);
    
    cnt += (mp[2][1] != dpos[2][1]);
    cnt += (mp[2][2] != dpos[2][2]);
    cnt += (mp[2][3] != dpos[2][3]);
    cnt += (mp[2][4] != dpos[2][4]);
    cnt += (mp[2][5] != dpos[2][5]);
    
    cnt += (mp[3][1] != dpos[3][1]);
    cnt += (mp[3][2] != dpos[3][2]);
    cnt += (mp[3][3] != dpos[3][3]);
    cnt += (mp[3][4] != dpos[3][4]);
    cnt += (mp[3][5] != dpos[3][5]);
    
    cnt += (mp[4][1] != dpos[4][1]);
    cnt += (mp[4][2] != dpos[4][2]);
    cnt += (mp[4][3] != dpos[4][3]);
    cnt += (mp[4][4] != dpos[4][4]);
    cnt += (mp[4][5] != dpos[4][5]);
    
    cnt += (mp[5][1] != dpos[5][1]);
    cnt += (mp[5][2] != dpos[5][2]);
    cnt += (mp[5][3] != dpos[5][3]);
    cnt += (mp[5][4] != dpos[5][4]);
    cnt += (mp[5][5] != dpos[5][5]);
	return cnt;
}

void dfs(int dep,int lim,int x,int y) {
	if(dep == lim) {
		if(!h()) flag = 1;
		return ;
	}
	rep(i,1,8) {
		int tx = x + movx[i];
		int ty = y + movy[i];
		if(!mov(tx,ty)) {
			continue;
		}
		std::swap(mp[x][y],mp[tx][ty]);
		int p = h();
		if(dep + p <= lim)
			dfs(dep + 1,lim,tx,ty);
		std::swap(mp[x][y],mp[tx][ty]);
		if(flag) return ;
	}
}

void solve() {
	flag = 0;
	int sx,sy;
	rep(i,1,5) {
		getStr(s + 1);
		rep(j,1,5) {
    		switch(s[j]) {
    			case '1' : {
    				mp[i][j] = 1;
    				break;
    			}
    			case '0' : {
    				mp[i][j] = 2;
    				break;
    			}
    			case '*' : {
    				sx = i,sy = j;
    				mp[i][j] = 0;
    				break;
    			}
    		}
		}
	}
	if(!h()) {
		putC('-'),putC('1');
		enter;
		return ;
	}
	rep(i,1,15) {
		dfs(0,i,sx,sy);
		if(flag) {
			write(i),enter;
			break;
		}
	}
	if(!flag) {
	    putC('-'),putC('1');
	    enter;
	}
}

int main() {
	init_IO();
	int T = read();
	while(T--) solve();
	end_IO();
	return 0;
}