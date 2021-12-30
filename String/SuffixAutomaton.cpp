/*
Luogu P3804 Suffix Automaton
Author : AstaitneAi
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
	
	inline void write(int x) {
		static int sta[20];int top = 0;
		do
			sta[top++] = x % 10,x /= 10;
		while(x);
		while(top) putC(sta[--top] + '0');
	}
	
	inline int getStr(char *s) {
	    char ch = getC();int len = 0;
	    while(!isalpha(ch)) ch = getC();
	    while(isalpha(ch)) {
	        s[len++] = ch;
	        ch = getC();
	    }
	    s[len] = '\0';
	    return len;
	}
}
using IO::init_IO;
using IO::end_IO;
using IO::write;
using IO::getStr;
using IO::putC;

struct SuffixAutomaton {
	int tot,lst;
	int siz[N << 1];
	int buc[N],id[N << 1];
	struct Node {
		int len,link;
		int ch[26];
	}st[N << 1];
	
	SuffixAutomaton() : tot(1),lst(1) {}
	
	inline void extend(int ch) {
		int cur = ++tot,p = lst;lst = cur;
		siz[cur] = 1,st[cur].len = st[p].len + 1;
		for(;p && !st[p].ch[ch];p = st[p].link)
			st[p].ch[ch] = cur;
		if(!p) st[cur].link = 1;
		else {
			int q = st[p].ch[ch];
			if(st[q].len == st[p].len + 1)
				st[cur].link = q;
			else {
				int pp = ++tot;st[pp] = st[q];
				st[pp].len = st[p].len + 1;
				st[cur].link = st[q].link = pp;
				for(;p && st[p].ch[ch] == q;p = st[p].link)
					st[p].ch[ch] = pp;
			}
		}
	}
	
	inline void solve(int n) {
		rep(i,1,tot) ++buc[st[i].len];
		rep(i,1,n) buc[i] += buc[i - 1];
		repb(i,tot,1) id[buc[st[i].len]--] = i;
		repb(i,tot,1) siz[st[id[i]].link] += siz[id[i]];
		int ans = 0;
		rep(i,1,tot) if(siz[i] > 1)
			ans = std::max(ans,siz[i] * st[i].len);
		write(ans),enter;
	}
}SAM;

char s[N];

int main() {
	init_IO();
	int n = getStr(s + 1);
	rep(i,1,n) SAM.extend(s[i] - 'a');
	SAM.solve(n);
	end_IO();
	return 0;
}