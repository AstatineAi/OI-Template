/*
Luogu P7771 Eulerian Trail
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
#include <stack>

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

int ind[N],outd[N];
std::vector<int> e[N];
std::stack<int> stk;

void dfs(int u) {
	while (!e[u].empty()) {
		int len = e[u].size() - 1;
		int v = e[u][len];
		e[u].pop_back();
		dfs(v);
	}
	stk.push(u);
}

int main() {
	init_IO();
	int n = read(),m = read();
	rep(i,1,m) {
		int st = read(),ed = read();
		++ind[ed],++outd[st];
		e[st].push_back(ed);
	}
	int cnt = 0,s = 0;
	rep(i,1,n) {
		std::sort(e[i].begin(),e[i].end(),std::greater<int>());
		if(std::abs(ind[i] - outd[i]) > 1) {
			putC('N'),putC('o'),enter;
			goto NoSol;
		}
		else if(outd[i] == ind[i] + 1)
			s = i;
		cnt += ind[i] != outd[i];
	}
	
	if(cnt != 0 && cnt != 2) {
		putC('N'),putC('o'),enter;
		goto NoSol;
	}
	
	dfs(s ? s : 1);
	
	while(!stk.empty()) {
		write(stk.top()),space;
		stk.pop();
	}
	enter;
	
	NoSol : end_IO();
	return 0;
}