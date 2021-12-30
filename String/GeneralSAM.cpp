/*
Luogu P6139 General Suffix Automaton
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
	
	inline void write(ll x) {
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
using IO::read;
using IO::write;
using IO::getStr;
using IO::putC;

struct GeneralSuffixAutomaton {
    int tot;
    struct Node {
        int len,link;
        int ch[26];
    }st[N << 2];
    
    GeneralSuffixAutomaton() : tot(1) {}
    
    inline int extend(int ch,int p) {
        int cur = st[p].ch[ch];
        if(st[cur].len) return cur;
        st[cur].len = st[p].len + 1;p = st[p].link;
        for(;p && !st[p].ch[ch];p = st[p].link)
            st[p].ch[ch] = cur;
        if(!p) st[cur].link = 1;
        else {
            int q = st[p].ch[ch];
            if(st[q].len == st[p].len + 1)
                st[cur].link = q;
            else {
                int pp = ++tot;
                rep(i,0,25)
                    st[pp].ch[i] = (st[st[q].ch[i]].len ? st[q].ch[i] : 0);
                st[pp].len = st[p].len + 1;
                st[pp].link = st[q].link,st[q].link = st[cur].link = pp;
                for(;p && st[p].ch[ch] == q;p = st[p].link)
                    st[p].ch[ch] = pp;
            }
        }
        return cur;
    }
    
    inline void insert(char *s) {
        int p = 1;
        for(int i = 0;s[i];++i) {
            if(!st[p].ch[s[i] - 'a'])
                st[p].ch[s[i] - 'a'] = ++tot;
            p = st[p].ch[s[i] - 'a'];
        }
    }
    
    inline void build() {
        std::queue<pii> q;
        rep(i,0,25) if(st[1].ch[i])
            q.push(std::make_pair(i,1));
        while(!q.empty()) {
            pii u = q.front();q.pop();
            int lst = extend(u.first,u.second);
            rep(i,0,25) if(st[lst].ch[i])
                q.push(std::make_pair(i,lst));
        }
    }
    
    inline void solve() {
        ll ans = 0;
        rep(i,2,tot)
            ans += st[i].len - st[st[i].link].len;
        write(ans),enter;
    }
}SAM;

char s[N];

int main() {
	init_IO();
	int n = read();
	rep(i,1,n) {
		getStr(s);
		SAM.insert(s);
	}
	SAM.build();
	SAM.solve();
	end_IO();
	return 0;
}