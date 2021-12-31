/*
Luogu P3384 Heavy Light Decomposition
Author : Astatine Ai
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
	}
	
	inline void putC(char ch) {
		if(_o == obuf + IOLIM) {
			fwrite(obuf,_o - obuf,sizeof(char),OS);
			_o = obuf;
		}
		*_o++ = ch;
	}
	
	inline int read() {
		int res = 0;char ch = getC();bool m = 1;
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

int head[N],ecnt = -1;
struct Edge {
	int nxt,to;
}e[N << 1];
inline void AddEdge(int st,int ed) {
	e[++ecnt] = (Edge) {head[st],ed},head[st] = ecnt;
	e[++ecnt] = (Edge) {head[ed],st},head[ed] = ecnt;
}

struct Barrett_Reduction {
    ull b,m;
    Barrett_Reduction(ull _b) : b(_b),m(ull((I128(1) << 64) / b)) {}
    friend inline ull operator % (const ull &x,const Barrett_Reduction &p) {
        ull red = x - (I128(p.m) * x >> 64) * p.b;
        return red >= p.b ? red - p.b : red;
    }
}p(2);

int dep[N],fa[N];
int siz[N],hson[N];
void HLD1(int u,int _f) {
	dep[u] = dep[_f] + 1,fa[u] = _f;
	siz[u] = 1;
	repg(i,u) {
		int v = e[i].to;
		if(v == _f) continue;
		HLD1(v,u);
		siz[u] += siz[v];
		if(siz[hson[u]] < siz[v])
			hson[u] = v;
	}
}

int dfs_clock;
int top[N],dfn[N],rnk[N];
void HLD2(int u,int _f) {
	top[u] = _f;
	dfn[++dfs_clock] = u;
	rnk[u] = dfs_clock;
	if(hson[u]) HLD2(hson[u],_f);
	repg(i,u) {
		int v = e[i].to;
		if(v == fa[u] || v == hson[u])
			continue;
		HLD2(v,v);
	}
}

int n;
int val[N];
#define lb(x) (x & (-x))
class BIT {
	// vars
	public : 
	
	private : 
		ll T1[N];
		ll T2[N];
	
	// funcs
	private : 
		inline void M(int p,ll v) {
			ll vt = p * v;
			for(;p <= n;p += lb(p))
				T1[p] += v,T2[p] += vt;
		}
		
		inline ll Q(ll *T,int p) {
			ll res = 0;
			for(;p;p -= lb(p))
				res += T[p];
			return res;
		}
	
	public : 
		inline void init() {
			rep(i,1,n) {
				ll vt = val[dfn[i]] - val[dfn[i - 1]];
				T1[i] += vt;
				T2[i] += vt * i;
				if(i + lb(i) <= n) {
					T1[i + lb(i)] += T1[i];
					T2[i + lb(i)] += T2[i];
				}
			}
		}
		
		inline void modify(int l,int r,ll v) {
			M(l,v),M(r + 1,-v);
		}
		
		inline ll query(int l,int r) {
			return Q(T1,r) * (r + 1ll) - Q(T2,r) - Q(T1,l - 1) * l + Q(T2,l - 1);
		}
}T;

void ModifyChain(int u,int v,ll vt) {
    while(top[u] != top[v]) {
        if(dep[top[u]] < dep[top[v]])
        	std::swap(u,v);
        T.modify(rnk[top[u]],rnk[u],vt); 
        u = fa[top[u]];
    }
    if(dep[u] > dep[v]) std::swap(u,v);
    T.modify(rnk[u],rnk[v],vt);
}

ll QueryChain(int u,int v) {
    ll res = 0;
    while(top[u] != top[v]) {
        if(dep[top[u]] < dep[top[v]])
        	std::swap(u,v);
        res += T.query(rnk[top[u]],rnk[u]); 
        u = fa[top[u]];
    }
    if(dep[u] > dep[v]) std::swap(u,v);
    res += T.query(rnk[u],rnk[v]);
    return res;
}

inline void ModifyTree(int u,ll vt) {
    T.modify(rnk[u],rnk[u] + siz[u] - 1,vt);
}

inline ll QueryTree(int u) {
    return T.query(rnk[u],rnk[u] + siz[u] - 1);
}

int main() {
	init_IO();
	mems(head,-1);
	n = read();int m = read(),r = read(),M = read();
	p = Barrett_Reduction(M);
	rep(i,1,n) val[i] = read();
	rep(i,1,n - 1) AddEdge(read(),read());
	HLD1(r,r),HLD2(r,r);
	T.init();
	while(m--) {
		int op = read(),x = read();
		switch(op) {
    		case 1: {
    			int y = read(),z = read();
    			ModifyChain(x,y,z);
    			break;
    		}
    		case 2: {
    			int y = read();
    			write(QueryChain(x,y) % p),enter;
    			break;
    		}
    		case 3: {
    			int y = read();
    			ModifyTree(x,y);
    			break;
    		}
    		case 4: {
    			write(QueryTree(x) % p),enter;
    			break;
    		}
    	}
	}
	end_IO();
	return 0;
}