/*
Luogu P3803 Aho-Corasick Automaton
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
#include <queue>

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
	    while(!isalpha(ch)) ch = getC();
	    while(isalpha(ch)) {
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

class AhoCorasickAutomaton {
	// vars
	public : 
	
	private : 
		int tot;
		struct Node {
			int val,fail;
			int ch[26];
		}st[N];
		
	// funcs
	public : 
		AhoCorasickAutomaton() : tot(0) {}
		
		inline void insert(char *s) {
			int p = 0;
			for(int i = 0;s[i];++i) {
				if(!st[p].ch[s[i] - 'a'])
					st[p].ch[s[i] - 'a'] = ++tot;
				p = st[p].ch[s[i] - 'a'];
			}
			++st[p].val;
		}
		
		inline void build() {
			std::queue<int> q;
			rep(i,0,25) if(st[0].ch[i])
				q.push(st[0].ch[i]);
			while(!q.empty()) {
				int p = q.front();q.pop();
				rep(i,0,25) if(st[p].ch[i]) {
					st[st[p].ch[i]].fail = st[st[p].fail].ch[i];
					q.push(st[p].ch[i]);
				}
				else st[p].ch[i] = st[st[p].fail].ch[i];
			}
		}
		
		inline int query(char *s) {
			int p = 0,res = 0;
			for(int i = 0;s[i];++i) {
				p = st[p].ch[s[i] - 'a'];
				for(int j = p;j && ~st[j].val;j = st[j].fail)
					res += st[j].val,st[j].val = -1;
			}
			return res;
		}
		
	private :
	
}AC;

char s[N];

int main() {
	init_IO();
	int n = read();
	rep(i,1,n) {
		getStr(s);
		AC.insert(s);
	}
	getStr(s);
	AC.build();
	write(AC.query(s)),enter;
	end_IO();
	return 0;
}