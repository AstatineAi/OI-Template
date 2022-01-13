/*
Luogu P3378 Binary Heap
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

struct BinaryHeap {
	int siz;
	int T[N];
	
	inline void down(int p) {
		for(int ch;(p << 1) <= siz;p = ch) {
			ch = p << 1;
			ch += (ch < siz && T[ch | 1] < T[ch]);
			if(T[ch] < T[p]) std::swap(T[p],T[ch]);
			else break;
		}
	}
	
	inline void up(int p) {
		for(;p;p >>= 1) {
			if(T[p] < T[p >> 1])
				std::swap(T[p],T[p >> 1]);
			else break;
		}
	}
	
	inline void push(int x) {
		T[++siz] = x;
		up(siz);
	}
	
	inline int top() {
		return T[1];
	}
	
	inline void pop() {
		T[1] = T[siz--];
		down(1);
	}
	
	inline void init(int n,int* val) {
		siz = n;
		memcpy(val,T,sizeof(int) * (n + 1));
		repb(i,n,1) down(i);
	}
}q;

int main() {
	init_IO();
	int n = read();
	rep(i,1,n) {
		int op = read();
		switch(op) {
			case 1 : q.push(read());break;
			case 2 : write(q.top()),enter;break;
			case 3 : q.pop();break;
		}
	}
	end_IO();
	return 0;
}