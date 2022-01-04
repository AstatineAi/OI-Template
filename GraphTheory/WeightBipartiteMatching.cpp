/*
Luogu P6577 : Maximum Weight Bipartite Matching
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
#include <vector>

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

constexpr int N = 505;
constexpr ll INF = 1e18;
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
}
using IO::init_IO;
using IO::end_IO;
using IO::read;
using IO::write;
using IO::putC;

int n,m;

int match[N];
ll slack[N],lx[N],ly[N];
ll mp[N][N];
int pre[N];
bool visx[N],visy[N];

void argument(int u) {
	memset(slack,63,sizeof(ll) * (n + 1));
	memset(pre,0,sizeof(int) * (n + 1));
	match[0] = u;int x,y = 0,tmpy = 0;ll a;
	while(1) {
		x = match[y];a = INF;visy[y] = 1;
		rep(i,1,n) {
			if(visy[i]) continue;
			if(slack[i] > lx[x] + ly[i] - mp[x][i]) {
				slack[i] = lx[x] + ly[i] - mp[x][i];
				pre[i] = y;
			}
			if(slack[i] < a) {
				a = slack[i];
				tmpy = i;
			}
		}
		rep(i,0,n) if(visy[i])
			lx[match[i]] -= a,ly[i] += a;
		else
			slack[i] -= a;
		y = tmpy;
		if(match[y] == -1) break;
	}
	while(y) {
		match[y] = match[pre[y]];
		y = pre[y];
	}
}

ll KM() {
	memset(match,-1,sizeof(int) * (n + 1));
	memset(ly,0,sizeof(ll) * (n + 1));
	memset(lx,0,sizeof(ll) * (n + 1));
	rep(i,1,n) {
		memset(visy,0,sizeof(bool) * (n + 1));
		argument(i);
	}
	ll res = 0;
	rep(i,1,n) if(~match[i])
		res += mp[match[i]][i];
	return res;
}

int main() {
	init_IO();
	n = read(),m = read();
	mems(mp,192);
	rep(i,1,m) {
		int st = read(),ed = read(),w = read();
		mp[st][ed] = w;
	}
	write(KM()),enter;
	rep(i,1,n) write(match[i]),space;
	enter;
	end_IO();
	return 0;
}