#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<cctype>
#include<algorithm>
#include<iostream>
#include<utility>
#include <chrono>
#include <random>

#define space putC(' ')
#define enter putC('\n')
#define mian main

#define ff(a,b,c) for(register int a = (b);a <= (c);++a)
#define fb(a,b,c) for(register int a = (b);a >= (c);--a)
#define fe(a,b) for(register int a = head[b]; ~a ; a = e[a].nxt)
#define mems(a,b) memset(a,b,sizeof(a))

#define O(a) std::cerr<<#a<<':'<<a<<std::endl;

typedef long long ll;
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
	}
	
	inline void putC(char ch) {
		if(_o == obuf + IOLIM) {
			fwrite(obuf,_o - obuf,sizeof(char),OS);
			_o = obuf;
		}
		*_o++ = ch;
	}
	
	inline ll read() {
		ll res = 0;char ch = getC();bool m = 0;
		while(!isdigit(ch)) {
			if(ch == '-') m = 1;
			ch = getC();
		}
		while(isdigit(ch)) {
			res = res * 10 + (ch ^ 48);
			ch = getC();
		}
		return m ? -res : res;
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
using namespace IO;

int a[N];

bool check(const int &n) {
    ff(i,2,n) if(a[i - 1] > a[i])
        return 0;
    return 1;
}

int mian() {
	init_IO();
	int n = read();
	unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937 rand_num(seed);
	std::uniform_int_distribution<int> bogo(1,n);
	ff(i,1,n) a[i] = read();
	while(!check(n)) {
	    int u = bogo(rand_num),v = bogo(rand_num);
	    std::swap(a[u],a[v]);
	}
	ff(i,1,n) write(a[i]),space;
	end_IO();
	return 0;
}